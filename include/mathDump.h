#ifndef H_MATHDUMP
#define H_MATHDUMP

#include "tree.h"

enum operationComparison {
    MORE_BY_PRIORITY  = 0,
    LOWER_IN_PRIORITY = 1,
    ERROR_OF_COMPARE  = 2
};

enum typeOfFunctions {
    PREFIX_FUNCTION      = 0,
    ROOT_FUNCTION        = 1,
    NOT_FUNCTION         = 2
};

treeErrors dumpMathTree( tree_t* tree );

void printMathematicalFormulas( FILE* fileForPrint, node_t* node );

typeOfFunctions getTypeOfDataInNode( node_t* node );

void printPrefixBypass( FILE* fileForLatex, node_t* node );

void printInOrderBypass( FILE* fileForLatex, node_t* node );

void viewMathFormula( FILE* fileForLatex, node_t* node );

void printNumberInLatex( FILE* fileForLatex, node_t* node );

void printFracInLatex( FILE* fileForLatex, node_t* node );

operationComparison compareTwoMathOperator( node_t* currentNode, node_t* parentNode );

#endif
