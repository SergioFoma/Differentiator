#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "mathematicalCalculator.h"
#include "paint.h"
#include "myStringFunction.h"
#include "globals.h"

const double epsilon = 1e-5;

const size_t sizeOfArrayWithVariable = 24;
double arrayWithVariableValue[ sizeOfArrayWithVariable] = {};

/*mathErrors calculateTheFunctionValue( tree_t* tree ){
    if( tree == NULL ){
        return NULL_PTR;
    }

    for( size_t variableIndex = 0; variableIndex < sizeOfArrayWithVariable; variableIndex++ ){
        colorPrintf( NOMODE, BLUE, "Enter the value of variable : " );
        scanf( "%lg", arrayWithVariableValue + variableIndex  );
        cleanBuffer();
    }

    double resultOfCalculate = calculateValue( tree->rootTree );

    printf( "\n\nResult of calculate = %lg\n", resultOfCalculate );

    return CORRECT_CALCULATE;
}

double calculateValue( node_t* node ){
    if( node == NULL ){
        return 0;
    }

    if( node->nodeValueType == NUMBER ){
        return node->data.number;
    }
    else if( node->nodeValueType == VARIABLE ){
        return arrayWithVariableValue[ node->data.variableInArray ];
    }

    double firstNumber = calculateValue( node->left );
    double secondNumber = calculateValue( node->right );

    return doMathOperations( node, firstNumber, secondNumber );
}

double doMathOperations( node_t* node, double firstNumber, double secondNumber ){
    assert( node );

    for( size_t functionIndex = 0; functionIndex < sizeOfArrayWithMathFunctions; functionIndex++ ){
        if( node->data.mathOperation == arrayWithMathFunctions[ functionIndex ].mathClass ){
            return arrayWithMathFunctions[ functionIndex ].func( firstNumber, secondNumber );
        }
    }

    return 0;
}

*/

mathErrors differentiationOfTheFunction( tree_t* tree, tree_t* differentiationTree ){
    if( tree == NULL ){
        return NULL_PTR;
    }

    differentiationTree->rootTree = differentiation( tree->rootTree, X );

    return CORRECT_DIFFERENTIATION;
}

node_t* differentiation( const node_t* node, variablesAndTheyIndex variable ){
    if( node == NULL ){
        return NULL;
    }

    node_t* nodeAfterDifferentiation = {};
    treeElem_t data = {};

    if( node->nodeValueType == NUMBER || ( node->nodeValueType == VARIABLE && node->data.variableInArray != variable ) ){
        data.number = 0;
        initNode( &nodeAfterDifferentiation, NUMBER, data );
        nodeAfterDifferentiation->parent = node->parent;
        return nodeAfterDifferentiation;
    }

    if( node->nodeValueType == VARIABLE && node->data.variableInArray == variable ){
        data.number = 1;
        initNode( &nodeAfterDifferentiation, NUMBER, data );
        nodeAfterDifferentiation->parent = node->parent;
        return nodeAfterDifferentiation;
    }



    for( size_t diffIndex = 0; diffIndex < sizeOfMathArray; diffIndex++ ){
        if( node->data.mathOperation == arrayWithMathInfo[ diffIndex ].mathOperation ){
            return arrayWithMathInfo[ diffIndex ].differentiationFunc( node, variable );
        }
    }
}

node_t* copyNode( node_t* node ){
    if( node == NULL ){
        return NULL;
    }
    node_t* newNode = NULL;
    initNode( &newNode, node->nodeValueType, node->data );

    newNode->left = copyNode( node->left );
    newNode->right = copyNode( node->right );

    if( newNode->left ){
        newNode->left->parent = newNode;
    }
    if( newNode->right ){
        newNode->right->parent = newNode;
    }

    return newNode;
}

node_t* makeConstNode( double value ){
    node_t* newNode = NULL;
    treeElem_t data = {};
    data.number = value;
    initNode( &newNode, NUMBER, data );
    return newNode;
}

node_t* newNode( typeOfDataInNode nodeType, typeOfMathOperation mathOperator, node_t* leftNode, node_t* rightNode ){

    node_t* newNode = NULL;
    treeElem_t data = {};
    data.mathOperation = mathOperator;

    initNode( &newNode, nodeType, data );
    newNode->left = leftNode;
    newNode->right = rightNode;
    if( newNode->left ){
        newNode->left->parent = newNode;
    }
    if( newNode->right ){
        newNode->right->parent = newNode;
    }

    return newNode;
}
