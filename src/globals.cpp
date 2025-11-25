#include <stdio.h>
#include <assert.h>

#include "globals.h"
#include "mathDump.h"
#include "mathematicalCalculator.h"

#define ADD_( leftNode, rightNode ) newNode( OPERATOR, ADD, leftNode, rightNode )
#define SUB_( leftNode, rightNode ) newNode( OPERATOR, SUB, leftNode, rightNode )
#define MUL_( leftNode, rightNode ) newNode( OPERATOR, MUL, leftNode, rightNode )
#define DIV_( leftNode, rightNode ) newNode( OPERATOR, DIV, leftNode, rightNode )


#define COS_( rightNode ) newNode( OPERATOR, COS, NULL, rightNode )
#define SIN_( rightNode ) newNode( OPERATOR, SIN, NULL, rightNode )
#define LN_( rightNode ) newNode( OPERATOR, LN, NULL, rightNode )
#define POW_( leftNode, rightNode ) newNode( OPERATOR, POW, leftNode, rightNode )

informationWithMathOperators arrayWithMathInfo[] = {
    { ADD   , "ADD"     , "+"       , printCenterFunctionInLatex    , "+"           ,   doAdd   , differentiationAdd    },
    { SUB   , "SUB"     , "-"       , printCenterFunctionInLatex    , "-"           ,   doAdd   , differentiationSub    },
    { MUL   , "MUL"     , "*"       , printCenterFunctionInLatex    , "\\cdot "      ,   doAdd  , differentiationMul    },
    { DIV   , "DIV"     , "/"       , printFunctionOfTwoArguments   , "\\frac{"     ,   doAdd   , differentiationDiv    },
    { LN    , "LN"      , "ln"      , printFunctionOfOneArguments   , "ln"          ,   doAdd   , differentiationLn     },
    { LOG   , "LOG"     , "log"     , printFunctionOfTwoArguments   , "\\log_{"     ,   doAdd   , differentiationLog    },
    { POW   , "POW"     , "^"       , printFunctionWithOneStaples   , "^{"          ,   doAdd   , differentiationAdd    },
    { SIN   , "SIN"     , "sin"     , printFunctionOfOneArguments   , "sin"         ,   doAdd   , differentiationSin    },
    { COS   , "COS"     , "cos"     , printFunctionOfOneArguments   , "cos"         ,   doAdd   , differentiationCos    },
    { TG    , "TG"      , "tg"      , printFunctionOfOneArguments   , "tg"          ,   doAdd   , differentiationAdd    },
    { CTG   , "CTG"     , "ctg"     , printFunctionOfOneArguments   , "ctg"         ,   doAdd   , differentiationAdd    },
    { ARCSIN, "ARCSIN"  , "arcsin"  , printFunctionOfOneArguments   , "arcsin"      ,   doAdd   , differentiationAdd    },
    { ARCCOS, "ARCCOS"  , "arccos"  , printFunctionOfOneArguments   , "arccos"      ,   doAdd   , differentiationAdd    },
    { ARCTG , "ARCTG"   , "arctg"   , printFunctionOfOneArguments   , "arctg"       ,   doAdd   , differentiationAdd    },
    { ARCCTG, "ARCCTG"  , "arcctg"  , printFunctionOfOneArguments   , "arcctg"      ,   doAdd   , differentiationAdd    },
    { SH    , "SH"      , "sh"      , printFunctionOfOneArguments   , "sh"          ,   doAdd   , differentiationAdd    },
    { TH    , "TH"      , "th"      , printFunctionOfOneArguments   , "th"          ,   doAdd   , differentiationAdd    },
    { CTH   , "CTH"     , "cth"     , printFunctionOfOneArguments   , "cth"         ,   doAdd   , differentiationAdd    },
    { EXP   , "EXP"     , "exp"     , printFunctionWithOneStaples   , "e^{"         ,   doAdd   , differentiationAdd    },
    { SQRT  , "SQRT"    , "sqrt"    , printFunctionOfTwoArguments   , "\\sqrt{"     ,   doAdd   , differentiationAdd    }
};
const size_t sizeOfMathArray = sizeof( arrayWithMathInfo ) / sizeof( arrayWithMathInfo[ 0 ] );

informationWithVariables arrayWithVariables[] = {
    { X, "x" },
    { Y, "y" },
    { I, "i" },
    { J, "j" },
    { K, "k" },
    { L, "l" },
    { M, "m" },
    { N, "n" },
    { O, "o" },
    { P, "p" },
    { Q, "q" },
    { R, "r" },
    { S, "s" },
    { A, "a" },
    { B, "b" },
    { C, "c" },
    { Z, "z" },
    { W, "w" },
    { D, "d" },
    { E, "e" },
    { F, "f" },
    { T, "t" },
    { U, "u" },
    { V, "v" },
    { G, "g" },
    { H, "h" }
};
const size_t sizeOfArrayWithVariables = sizeof( arrayWithVariables ) / sizeof( arrayWithVariables[ 0 ] );

informationWithValueType arrayWithValueType[] = {
        { NUMBER, "NUMBER"},
        { VARIABLE, "VARIABLE"},
        { OPERATOR, "OPERATOR"}
};
const size_t sizeOfArrayWithValueType = sizeof( arrayWithValueType ) / sizeof( arrayWithValueType[ 0 ] );

void printMathFunction( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    for( size_t functionIndex = 0; functionIndex < sizeOfMathArray; functionIndex++ ){
        if( node->data.mathOperation == arrayWithMathInfo[ functionIndex ].mathOperation ){
            arrayWithMathInfo[ functionIndex ].printInLatex( fileForLatex, node );
            break;
        }
    }
}

void printCenterFunctionInLatex( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    operationComparison statusOfCompare = compareTwoMathOperator( node, node->parent );
    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\left(" );
    }
    if( node->left ){
        printMathematicalFormulas( fileForLatex, node->left );
    }

    for( size_t centerFunctionInLatex = 0; centerFunctionInLatex < sizeOfMathArray; centerFunctionInLatex++ ){
        if( node->data.mathOperation == arrayWithMathInfo[ centerFunctionInLatex ].mathOperation ){
            fprintf( fileForLatex, "%s", arrayWithMathInfo[ centerFunctionInLatex ].viewInLatex );
            break;
        }
    }

    if( node->right ){
        printMathematicalFormulas( fileForLatex, node->right );
    }
    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\right)" );
    }
}

void printFunctionOfTwoArguments( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    operationComparison statusOfCompare = compareTwoMathOperator( node, node->parent );
    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\left(" );
    }

    for( size_t functionOfTwoArguments = 0; functionOfTwoArguments < sizeOfMathArray; functionOfTwoArguments++ ){
        if( node->data.mathOperation == arrayWithMathInfo[ functionOfTwoArguments ].mathOperation ){
            fprintf( fileForLatex, "%s", arrayWithMathInfo[ functionOfTwoArguments ].viewInLatex );
            break;
        }
    }

    if( node->left ){
        printMathematicalFormulas( fileForLatex, node->left );
    }
    fprintf( fileForLatex, "}{" );
    if( node->right ){
        printMathematicalFormulas( fileForLatex, node->right );
    }
    fprintf( fileForLatex, "}" );
    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\right)" );
    }
}

void printFunctionOfOneArguments( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    operationComparison statusOfCompare = compareTwoMathOperator( node, node->parent );
    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\left(" );
    }

    for( size_t functionOfOneArgument = 0; functionOfOneArgument < sizeOfMathArray; functionOfOneArgument++ ){
        if( node->data.mathOperation == arrayWithMathInfo[functionOfOneArgument  ].mathOperation ){
            fprintf( fileForLatex, "%s", arrayWithMathInfo[ functionOfOneArgument ].viewInLatex );
            break;
        }
    }

    if( node->right ){
        printMathematicalFormulas( fileForLatex, node->right );
    }
    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\right)" );
    }
}

void printFunctionWithOneStaples( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    operationComparison statusOfCompare = compareTwoMathOperator( node, node->parent );
    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\left(" );
    }
    if( node->left ){
        printMathematicalFormulas( fileForLatex, node->left );
    }

    for( size_t functionWithOneStaples = 0; functionWithOneStaples < sizeOfMathArray; functionWithOneStaples++ ){
        if( node->data.mathOperation == arrayWithMathInfo[ functionWithOneStaples ].mathOperation ){
            fprintf( fileForLatex, "%s", arrayWithMathInfo[ functionWithOneStaples ].viewInLatex );
            break;
        }
    }

    if( node->right ){
        printMathematicalFormulas( fileForLatex, node->right );
        fprintf( fileForLatex, "}" );
    }
    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\right)" );
    }

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

double doAdd( double firstNumber, double secondNumber ){
    return firstNumber + secondNumber;
}


/*
double doSub( double firstNumber, double secondNumber );
double doMul( double firstNumber, double secondNumber );
double doDiv( double firstNumber, double secondNumber );
double doLn( double firstNumber, double secondNumber );
double doLog( double firstNumber, double secondNumber );
double doPow( double firstNumber, double secondNumber );
double doSin( double firstNumber, double secondNumber );
double doCos( double firstNumber, double secondNumber );
double doTg( double firstNumber, double secondNumber );
double doCtg( double firstNumber, double secondNumber );
double doArcsin( double firstNumber, double secondNumber );
double doArccos( double firstNumber, double secondNumber );
double doArctg( double firstNumber, double secondNumber );
double doArcctg( double firstNumber, double secondNumber );
double doSh( double firstNumber, double secondNumber );
double doTh( double firstNumber, double secondNumber );
double doCth( double firstNumber, double secondNumber );
double doExp( double firstNumber, double secondNumber );
double doSqrt( double firstNumber, double secondNumber );

*/
