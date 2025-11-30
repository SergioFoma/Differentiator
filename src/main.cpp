#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "treeDump.h"
#include "mathDump.h"
#include "parseFileDataBase.h"
#include "mathematicalCalculator.h"

int main(){

    tree_t tree = {};

    char* nameOfFileForLatex = askInformationAboutMathDump();
    FILE* fileForLatex = beginMathDump( nameOfFileForLatex );

    createTreeByRecursiveDescent( &tree );

    tree_t differentiationTree = {};
    differentiationOfTheFunction( &tree, &differentiationTree, fileForLatex );

    dumpMathTree( &tree, fileForLatex );
    endMathDump( fileForLatex, nameOfFileForLatex );

    dumpTree( &tree );
    destroyTree( &tree );
    destroyTree( &differentiationTree );

    return 0;
}



