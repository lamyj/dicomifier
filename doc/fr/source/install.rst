Compilation et Installation
===========================

Prérequis
---------

TODO

Compilation (UNIX)
------------------

Les sources du projet sont disponibles à l'adresse suivante : https://medipy.u-strasbg.fr/scm/hg/fli-iam/dicomifier

Avant de commencer il faut récupérer l'ensemble des fichiers sources à l'aide d'un logiciel de gestion de versions comme par exemple Mercurial ou SVN.
Nous supposerons dans la suite que les sources du projet sont dans le répertoire "dicomifier".

 - Se placer dans le répertoire dicomifier (cd dicomifier/)
 - Créer un répertoire build (mkdir build)
 - Se placer dans le répertoire build (cd build/)
 - Générer le Makefile (cmake -G Ninja -D CMAKE_CXX_FLAGS="-std=c++0x" ../)
 - Compiler le projet (ninja)
 - Vérifier qu'aucune erreur n'est survenue lors de la compilation
 
Un exécutable 'dicomifier' est maintenant disponible dans le répertoire 'dicomifier/build/src/appli/'.

Installation
------------

TODO
