#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "mathematicalCalculator.h"
#include "paint.h"
#include "myStringFunction.h"
#include "globals.h"
#include "mathDump.h"

const double epsilon = 1e-5;

extern FILE* differentiationDump;

const size_t sizeOfArrayWithVariable = 1;
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
#define CH_( rightNode ) newNode( OPERATOR, CH, NULL, rightNode )
#define SH_( rightNode ) newNode( OPERATOR, SH, NULL, rightNode )
#define EXP_( rightNode ) newNode( OPERATOR, EXP, NULL, rightNode )

#define dR( variable ) differentiation( node->right, variable )
#define dL( variable ) differentiation( node->left, variable )

mathErrors calculateTheFunctionValue( tree_t* tree ){
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

    for( size_t functionIndex = 0; functionIndex < sizeOfMathArray; functionIndex++ ){
        if( node->data.mathOperation == arrayWithMathInfo[ functionIndex ].mathOperation ){
            return arrayWithMathInfo[ functionIndex ].doMathOperation( firstNumber, secondNumber );
        }
    }

    return 0;
}

double doAdd( double firstNumber, double secondNumber ){
    return firstNumber + secondNumber;
}
double doSub( double firstNumber, double secondNumber ){
    return firstNumber - secondNumber;
}
double doMul( double firstNumber, double secondNumber ){
    return firstNumber * secondNumber;
}
double doDiv( double firstNumber, double secondNumber ){
    return firstNumber / secondNumber;
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
            node_t* newNode = NULL;
            newNode = arrayWithMathInfo[ diffIndex ].differentiationFunc( node, variable );
            printResultOfDifferentiation( differentiationDump, (node_t*)node, newNode );
            return newNode;
        }
    }

    return NULL;
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

    return ADD_( dL( variable ),
                 dR( variable )
                );
}

node_t* differentiationSub( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return SUB_( dL( variable ),
                 dR( variable )
                );
}

node_t* differentiationMul( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return ADD_(MUL_( dL( variable ),
                      copyNode( node->right )
                    ),
                MUL_( copyNode( node->left ),
                      dR( variable )
                    )
                );
}

node_t* differentiationDiv( const node_t* node, variablesAndTheyIndex variable){
    assert( node );
    return DIV_(
                SUB_(
                    MUL_( dL( variable ),
                          copyNode( node->right )
                        ),
                    MUL_( copyNode( node->left ),
                          dR( variable )
                        )
                    ),
                POW_( copyNode( node->right ),
                      makeConstNode( 2 )
                    )
                );
}

node_t* differentiationLn( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( dR( variable ), copyNode( node->right ) );
}

node_t* differentiationLog( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( dR( variable ),
                 MUL_( copyNode( node->right ), LN_( copyNode( node->left) ) )
                );
}

node_t* differentiationSin( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return MUL_( COS_( copyNode( node->right ) ), dR( variable ) ) ;
}

node_t* differentiationCos( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return MUL_( makeConstNode( -1 ), MUL_( SIN_( copyNode( node->right ) ), dR( variable ) ) );
}

node_t* differentiationTg( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( dR( variable ),
                 POW_( COS_( copyNode( node->right ) ),
                       makeConstNode( 2 )
                     )
                );
}

node_t* differentiationCtg( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( MUL_( makeConstNode( -1 ),
                       dR( variable )
                     ),
                 POW_( SIN_( copyNode( node->right ) ),
                       makeConstNode( 2 )
                     )
                );
}

node_t* differentiationArcsin( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( dR( variable ),
                 SQRT_( SUB_( makeConstNode( 1 ),
                              POW_( copyNode( node->right ), makeConstNode( 2 ) )
                            )
                      )
                );

}

node_t* differentiationArccos( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return  DIV_( MUL_( makeConstNode( -1 ),
                        dR( variable )
                      ),
                  SQRT_( SUB_( makeConstNode( 1 ),
                                POW_( copyNode( node->right ), makeConstNode( 2 ) )
                             )
                        )
                );
}

node_t* differentiationArctg( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( dR( variable ),
                 ADD_( makeConstNode( 1 ),
                       POW_( copyNode( node->right ),
                             makeConstNode( 2 )
                            )
                     )
                );
}

node_t* differentiationArcctg( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( MUL_( makeConstNode( -1 ),
                       dR( variable )
                    ),
                 ADD_( makeConstNode( 1 ),
                       POW_( copyNode( node->right ),
                             makeConstNode( 2 )
                            )
                    )
                );
}

node_t* differentiationSh( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return MUL_( CH_( copyNode( node->right )),
                 dR( variable )
                );
}

node_t* differentiationCh( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return MUL_( SH_( copyNode( node->right ) ),
                 dR( variable )
                );
}

node_t* differentiationTh( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( dR( variable ),
                 POW_( CH_( copyNode( node->right ) ),
                        makeConstNode( 2 )
                     )
                );
}

node_t* differentiationCth( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( MUL_( makeConstNode( -1 ),
                       dR( variable )
                     ),
                POW_( SH_( copyNode( node->right ) ),
                      makeConstNode( 2 )
                    )
                );
}

node_t* differentiationExp( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return MUL_( EXP_( copyNode( node->right ) ),
                 dR( variable )
                );
}

node_t* differentiationSqrt( const node_t* node, variablesAndTheyIndex variable){
    assert( node );

    return DIV_( dR( variable ),
                MUL_( makeConstNode( 2 ),
                     SQRT_( copyNode( node->right ) )
                    )
                );
}

node_t* differentiationPow( const node_t* node, variablesAndTheyIndex variable ){
    assert( node );

    statusOfFind leftSearching = variableSearching( node->left, variable );
    statusOfFind rightSearching = variableSearching( node->right, variable );

    if( leftSearching == DETECTED_VAR && rightSearching == NOT_DETECTED_VAR ){
        return MUL_( makeConstNode( node->right->data.number ),
                     MUL_( POW_( copyNode( node->left ),
                                 makeConstNode( node->right->data.number - 1 )
                                ),
                           dL( variable )
                        )
                    );
    }

    if( leftSearching == NOT_DETECTED_VAR && rightSearching == DETECTED_VAR ){
        return MUL_( POW_( makeConstNode( node->left->data.number ),
                           copyNode( node->right )
                         ),
                     MUL_( dR( variable ),
                           LN_( makeConstNode( node->left->data.number ) )
                         )
                    );
    }

    if( leftSearching == DETECTED_VAR && rightSearching == DETECTED_VAR ){
        node_t*  degreeNode = MUL_( copyNode( node->right ),
                                   LN_( copyNode( node->left ) )
                                 );

        return MUL_( EXP_( degreeNode ),
                     differentiation( degreeNode, variable )
                    );
    }

    return NULL;
}

statusOfFind variableSearching( const node_t* node, variablesAndTheyIndex variable ){
    if( node == NULL ){
        return ERROR_OF_FIND_VAR;
    }

    if( node->nodeValueType == VARIABLE && node->data.variableInArray == variable ){
        return DETECTED_VAR;
    }

    statusOfFind leftSearching = variableSearching( node->left, variable );
    statusOfFind rightSearching = variableSearching( node->right, variable );

    if( leftSearching == DETECTED_VAR ){
        return leftSearching;
    }
    if( rightSearching == DETECTED_VAR ){
        return rightSearching;
    }

    return NOT_DETECTED_VAR;
}

void summaryOfConstants( tree_t* treeForOptimisation ){
    assert( treeForOptimisation );

    optimisationConsts( treeForOptimisation->rootTree );

}

void optimisationConsts( node_t* node ){
    assert( node );

    if( node->nodeValueType == NUMBER || node->nodeValueType == VARIABLE ){
        return ;
    }

    if( node->left ){
        optimisationConsts( node->left );
    }
    if( node->right ){
        optimisationConsts( node->right );
    }

    if( node->left && node->right &&
        node->left->nodeValueType == NUMBER && node->right->nodeValueType == NUMBER ){

        for( size_t indexOfOperators = 0; indexOfOperators < sizeOfMathArray; indexOfOperators++ ){
            if( node->data.mathOperation == arrayWithMathInfo[ indexOfOperators ].mathOperation ){
                double resultOfOptimisation = arrayWithMathInfo[ indexOfOperators ].doMathOperation( node->left->data.number,
                                                                                                     node->right->data.number);
                node->nodeValueType = NUMBER;
                node->data.number = resultOfOptimisation;

                free( node->left );
                node->left = NULL;
                free( node->right );
                node->right = NULL;

                break;
            }
        }
    }
}

void removingNeutralElements( tree_t* treeForOptimisation ){
    assert( treeForOptimisation );

    optimisationNeutralElem( treeForOptimisation->rootTree );
}

void optimisationNeutralElem( node_t* node ){
    assert( node );

    if( node->nodeValueType == NUMBER || node->nodeValueType == VARIABLE ){
        return ;
    }

    if( node->left ){
        optimisationNeutralElem( node->left );
    }
    if( node->right ){
        optimisationNeutralElem( node->right );
    }

    if(node->data.mathOperation == MUL &&
      (node->left->nodeValueType == NUMBER && fabs( node->left->data.number ) < epsilon ||
       node->right->nodeValueType == NUMBER && fabs( node->right->data.number ) < epsilon )){


        node->nodeValueType = NUMBER;
        node->data.number = 0;

        destroyNode( node->left );
        node->left = NULL;
        destroyNode( node->right );
        node->right = NULL;

    }
    else if( node->data.mathOperation == MUL && node->left->nodeValueType == NUMBER &&
             fabs( node->left->data.number  - 1 ) < epsilon ){

            if( node->parent->right == node ){
                node->parent->right = copyNode( node->right );
                destroyNode( node );
                node = NULL;
            }
            else if( node->parent->left == node ){
                node->parent->left = copyNode( node->right );
                destroyNode( node );
                node = NULL;
            }
    }
    else if( node->data.mathOperation == MUL && node->right->nodeValueType == NUMBER &&
             fabs( node->right->data.number  - 1 ) < epsilon ){

            if( node->parent->right == node ){
                node->parent->right = copyNode( node->left );
                destroyNode( node );
                node = NULL;
            }
            else if( node->parent->left == node ){
                node->parent->left = copyNode( node->left );
                destroyNode( node );
                node = NULL;
            }
    }
    else if( node->data.mathOperation == DIV && node->left->nodeValueType == NUMBER &&
             fabs( node->left->data.number ) < epsilon ){

            node->nodeValueType = NUMBER;
            node->data.number = 0;

            destroyNode( node->left );
            node->left = NULL;
            destroyNode( node->right );
            node->right = NULL;
    }
    else if( node->data.mathOperation == ADD && node->left->nodeValueType == NUMBER &&
            fabs( node->left->data.number ) < epsilon ){

            if( node->parent->right == node ){
                node->parent->right = copyNode( node->right );
                destroyNode( node );
                node = NULL;
            }
            else if( node->parent->left == node ){
                node->parent->left = copyNode( node->right );
                destroyNode( node );
                node = NULL;
            }
    }
    else if( node->data.mathOperation == ADD && node->right->nodeValueType == NUMBER &&
             fabs( node->right->data.number ) < epsilon ){

            if( node->parent->right == node ){
                node->parent->right = copyNode( node->left );
                destroyNode( node );
                node = NULL;
            }
            else if( node->parent->left == node ){
                node->parent->left = copyNode( node->left );
                destroyNode( node );
                node = NULL;
            }
    }
}

