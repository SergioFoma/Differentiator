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

#define ADD_( leftNode, rightNode ) newNode( OPERATOR, ADD, leftNode, rightNode )
#define SUB_( leftNode, rightNode ) newNode( OPERATOR, SUB, leftNode, rightNode )
#define MUL_( leftNode, rightNode ) newNode( OPERATOR, MUL, leftNode, rightNode )
#define DIV_( leftNode, rightNode ) newNode( OPERATOR, DIV, leftNode, rightNode )


#define COS_( rightNode ) newNode( OPERATOR, COS, NULL, rightNode )
#define SIN_( rightNode ) newNode( OPERATOR, SIN, NULL, rightNode )
#define LN_( rightNode ) newNode( OPERATOR, LN, NULL, rightNode )
#define POW_( leftNode, rightNode ) newNode( OPERATOR, POW, leftNode, rightNode )
#define SQRT_( rightNode ) newNode( OPERATOR, SQRT, NULL, rightNode )

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
}*/

double doAdd( double firstNumber, double secondNumber ){
    return firstNumber + secondNumber;
}


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

node_t* differentiationAdd( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return ADD_( differentiation( node->left, variable ),
                 differentiation( node->right, variable )
                );
}

node_t* differentiationSub( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return SUB_( differentiation( node->left, variable ),
                 differentiation( node->right, variable )
                );
}

node_t* differentiationMul( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return ADD_(MUL_( differentiation( node->left, variable ),
                      copyNode( node->right )
                    ),
                MUL_( copyNode( node->left ),
                      differentiation( node->right, variable )
                    )
                );
}

node_t* differentiationDiv( const node_t* node, variablesAndTheyIndex variable){
    assert( node );
    return DIV_(
                SUB_(
                    MUL_( differentiation( node->left, variable ),
                          copyNode( node->right )
                        ),
                    MUL_( copyNode( node->left ),
                          differentiation( node->right, variable )
                        )
                    ),
                POW_( copyNode( node->right ),
                      makeConstNode( 2 )
                    )
                );
}

node_t* differentiationLn( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( differentiation( node->right, variable ), copyNode( node->right ) );
}

node_t* differentiationLog( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( differentiation( node->right, variable ),
                 MUL_( copyNode( node->right ), LN_( copyNode( node->left) ) )
                );
}

node_t* differentiationSin( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return MUL_( COS_( copyNode( node->right ) ), differentiation( node->right, variable) ) ;
}

node_t* differentiationCos( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return MUL_( makeConstNode( -1 ), MUL_( SIN_( copyNode( node->right ) ), differentiation( node->right, variable ) ) );
}

node_t* differentiationTg( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( differentiation( node->right, variable ),
                 POW_( COS_( copyNode( node->right ) ),
                       makeConstNode( 2 )
                     )
                );
}

node_t* differentiationCtg( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( MUL_( makeConstNode( -1 ),
                       differentiation( node->right, variable )
                     ),
                 POW_( SIN_( copyNode( node->right ) ),
                       makeConstNode( 2 )
                     )
                );
}

node_t* differentiationArcsin( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( differentiation( node->right, variable ),
                 SQRT_( SUB_( makeConstNode( 1 ),
                              POW_( copyNode( node->right ), makeConstNode( 2 ) )
                            )
                      )
                );

}

node_t* differentiationArccos( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return  DIV_( MUL_( makeConstNode( -1 ),
                        differentiation( node->right, variable )
                      ),
                  SQRT_( SUB_( makeConstNode( 1 ),
                                POW_( copyNode( node->right ), makeConstNode( 2 ) )
                             )
                        )
                );
}

node_t* differentiationArctg( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( differentiation( node->right, variable ),
                 ADD_( makeConstNode( 1 ),
                       POW_( copyNode( node->right ),
                             makeConstNode( 2 )
                            )
                     )
                );
}
