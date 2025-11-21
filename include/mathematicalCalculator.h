#ifndef H_MATHEMATICAL_CALCULATOR
#define H_MATHEMATICAL_CALCULATOR

#include "tree.h"

enum mathErrors{
    CORRECT_CALCULATE           = 0,
    CORRECT_DIFFERENTIATION     = 1,
    NULL_PTR                    = 2
};

struct mathsOperators {
    typeOfMathOperation mathClass;
    double (*func)( double firstNumber, double doubleSecondNumber );
};

mathErrors calculateTheFunctionValue( tree_t* tree );

double calculateValue( node_t* node );

double doMathOperations( node_t* node, double firstNumber, double secondNumber );

double addNumbers( double firstNumber, double secondNumber );

double subNumbers( double firstNumber, double secondNumber );

double mulNumbers( double firstNumber, double secondNumber );

double divNumbers( double firstNumber, double secondNumber );

mathErrors differentiationOfTheFunction( tree_t* tree, tree_t* differentiationTree );

node_t* differentiation( const node_t* node, variablesAndTheyIndex variable );

node_t* copyNode( node_t* node );

node_t* newNode( typeOfDataInNode nodeType, typeOfMathOperation mathOperator, node_t* leftNode, node_t* rightNode );

#endif
