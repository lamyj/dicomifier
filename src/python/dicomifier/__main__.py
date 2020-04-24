#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import argparse
import logging
import sys

from . import commands

def main():
    parser = argparse.ArgumentParser(description="Dicomifier")
    
    parser.add_argument(
        "--verbosity", "-v",
        choices=["warning", "info", "debug"], default="warning")
    
    subparsers = parser.add_subparsers(help="Available commands")
    command_parsers = {}
    for name in dir(commands):
        if name.startswith("__"):
            continue
        command = getattr(commands, name)
        subparser = command.setup(subparsers)
        subparser.add_argument(
            "--verbosity", "-v",
            choices=["warning", "info", "debug"], default="warning")
        subparser.set_defaults(action=command.action)
        command_parsers[command.action] = subparser
    
    arguments = vars(parser.parse_args())
    if "action" not in arguments:
        parser.print_help()
        return 1
    
    verbosity = arguments.pop("verbosity")
    logging.basicConfig(
        level=verbosity.upper(), 
        format="%(levelname)s - %(name)s: %(message)s")
    
    action = arguments.pop("action")
    try:
        action(**arguments)
    except Exception as e:
        if verbosity == "debug":
            raise
        else:
            command_parsers[action].error(e)

if __name__ == "__main__":
    sys.exit(main())
