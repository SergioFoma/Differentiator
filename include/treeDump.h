#ifndef H_TREEDUMP
#define H_TREEDUMP

#include "tree.h"

struct informationWithValueType {
    typeOfDataInNode typeOfData;
    const char* nameOfType;
};

struct informationWithMathOperators {
    typeOfMathOperation mathOperation;
    const char* nameOfMathOperation;
    const char* viewOfMathOperation;
};

struct informationWithVariables {
    variablesAndTheyIndex variable;
    const char* nameOfVariable;
};

void dumpNode( node_t* node, int rank, FILE* treeFile );

const char* getStringOfValueType( const node_t* node );

const char* getStringOfMathOperator( const node_t* node );

const char* getStringOfVariable( const node_t* node );

const char* getViewOfMathOperation( const node_t* node );

treeErrors dumpTree( tree_t* tree );

void dumpNodeInFile( const node_t* node, FILE* fileForWrite );

void dumpTreeInFile( const tree_t* tree, FILE* fileForWrite );

#endif
