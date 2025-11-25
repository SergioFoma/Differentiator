#ifndef H_MATHEMATICAL_CALCULATOR
#define H_MATHEMATICAL_CALCULATOR

#include "tree.h"

enum mathErrors {
    CORRECT_CALCULATE           = 0,
    CORRECT_DIFFERENTIATION     = 1,
    NULL_PTR                    = 2
};

enum statusOfFind {
    DETECTED_VAR        = 0,
    NOT_DETECTED_VAR    = 1,
    ERROR_OF_FIND_VAR   = 2
};

mathErrors calculateTheFunctionValue( tree_t* tree );

double calculateValue( node_t* node );

double doMathOperations( node_t* node, double firstNumber, double secondNumber );


mathErrors differentiationOfTheFunction( tree_t* tree, tree_t* differentiationTree );

node_t* differentiation( const node_t* node, variablesAndTheyIndex variable );

node_t* copyNode( node_t* node );

node_t* makeConstNode( double value );

node_t* newNode( typeOfDataInNode nodeType, typeOfMathOperation mathOperator, node_t* leftNode, node_t* rightNode );

node_t* differentiationAdd( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationSub( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationMul( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationDiv( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationLn( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationLog( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationSin( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationCos( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationTg( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationCtg( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationArcsin( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationArccos( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationArctg( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationArcctg( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationSh( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationCh( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationTh( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationCth( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationExp( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationSqrt( const node_t* node, variablesAndTheyIndex variable);
node_t* differentiationPow( const node_t* node, variablesAndTheyIndex variable );

statusOfFind variableSearching( const node_t* node, variablesAndTheyIndex variable );


double doAdd( double firstNumber, double secondNumber );

#endif
