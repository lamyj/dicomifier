import argparse
import inspect
import logging
import pathlib
import re
import sys

import dicomifier
    
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--verbosity", "-v", dest="verbosity",
        choices=["warning", "info", "debug"], default="warning")
    arguments = vars(parser.parse_args())
    
    verbosity = getattr(logging, arguments.pop("verbosity").upper())
    logging.basicConfig(
        level=verbosity, 
        format="%(levelname)s - %(name)s: %(message)s")
    
    here = pathlib.Path(__file__).parent
    docs = here/"docs"
    for template in sorted(docs.rglob("*rst.in")):
        data = template.read_text()
        parts = re.split(r"(@[^@]+@)", data)
        for index in range(1, len(parts), 2):
            parts[index] = eval(parts[index][1:-1])
        data = "".join(parts)
        
        destination = template.parent/template.stem
        destination.write_text(data)

def autodoc(module, name=None):
    visitor = DocumentationVisitor(module)
    doc = visitor.visit(getattr(module, name) if name else module)
    return "\n".join(doc)

class DocumentationVisitor(object):
    def __init__(self, module, indent="", next_indent="  "):
        self.module = module
        self.indent = indent
        self.next_indent = next_indent
    
    def visit(self, root):
        result = []
        
        docstring = inspect.getdoc(root) or ""
        docstring = [
            "{}{}".format(self.indent, line) for line in docstring.splitlines()]
        
        if inspect.isclass(root):
            role = "class"
            signature = "{}.{}{}".format(
                self.module.__name__, root.__name__, 
                str(inspect.signature(root)))
        elif inspect.isfunction(root):
            role = "function"
            if "." in root.__qualname__:
                parent = getattr(
                    self.module, root.__qualname__.rsplit(".", 1)[0])
                if inspect.isclass(parent):
                    role = "method"
            if role == "function":
                signature = "{}.{}{}".format(
                    self.module.__name__, root.__qualname__, 
                    str(inspect.signature(root)))
            else:
                signature = inspect.signature(root)
                parameters = []
                for name, value in signature.parameters.items():
                    if name != "self":
                        parameters.append(value)
                signature = signature.replace(parameters=parameters)
                signature = "{}{}".format(root.__name__, str(signature))
        elif inspect.ismodule(root):
            role = None
        else:
            raise Exception("Unknown role for {}".format(type(root)))
        
        if role:
            result.extend([
                "{}.. py:{}:: {}".format(self.indent, role, signature),
                self.indent+self.next_indent])
            result.extend([
                "{}{}".format(self.next_indent, line) for line in docstring])
        else:
            result.extend(docstring)
        
        for name, object_ in inspect.getmembers(root):
            if name.startswith("__"):
                logging.debug("Skipping special member {}".format(name))
                continue
            if name.startswith("_"):
                logging.debug("Skipping private member {}".format(name))
                continue
            if inspect.ismodule(object_):
                logging.debug("Skipping module {}".format(name))
                continue
            module_name = getattr(object_, "__module__", None)
            if module_name and module_name != self.module.__name__:
                logging.info("Skipping object {} outside module".format(name))
                continue
            elif not module_name:
                logging.info("Skipping object {} with no module information".format(name))
                continue
            
            child_indent = (
                self.indent if inspect.ismodule(root)
                else self.indent+self.next_indent)
            visitor = DocumentationVisitor(
                self.module, child_indent, self.next_indent)
            result.extend([self.indent]+visitor.visit(object_))
        
        return result

if __name__ == "__main__":
    main()
