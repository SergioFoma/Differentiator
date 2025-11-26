#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "treeDump.h"
#include "mathDump.h"
#include "parseFileDataBase.h"
#include "mathematicalCalculator.h"

int main(){

    /*tree_t tree = {};

    char* nameOfFileForLatex = askInformationAboutMathDump();
    FILE* fileForLatex = beginMathDump( nameOfFileForLatex );

    createTreeFromFile( &tree );

    tree_t differentiationTree ={};

    dumpMathTree( &tree, fileForLatex );
    differentiationOfTheFunction( &tree, &differentiationTree );

    endMathDump( fileForLatex, nameOfFileForLatex );

    summaryOfConstants( &tree );

    dumpTree(&tree);

    destroyTree( &differentiationTree );

    destroyTree( &tree );*/

    double result = createTreeByRecursiveDescent();

    printf( "result = %lg\n", result );

    return 0;
}



