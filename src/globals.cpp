#include <stdio.h>
#include <assert.h>

#include "globals.h"
#include "mathDump.h"
#include "mathematicalCalculator.h"

informationWithMathOperators arrayWithMathInfo[] = {
{ ADD   , "ADD"     , "+"       , printCenterFunctionInLatex    , "+"           ,   doAdd   , differentiationAdd    ,   TWO_ARG    },
{ SUB   , "SUB"     , "-"       , printCenterFunctionInLatex    , "-"           ,   doSub   , differentiationSub    ,   TWO_ARG    },
{ MUL   , "MUL"     , "*"       , printCenterFunctionInLatex    , "\\cdot "     ,   doMul   , differentiationMul    ,   TWO_ARG    },
{ DIV   , "DIV"     , "/"       , printFunctionOfTwoArguments   , "\\frac{"     ,   doDiv   , differentiationDiv    ,   TWO_ARG    },
{ LN    , "LN"      , "ln"      , printFunctionOfOneArguments   , "ln"          ,   doAdd   , differentiationLn     ,   ONE_ARG    },
{ LOG   , "LOG"     , "log"     , printFunctionOfTwoArguments   , "\\log_{"     ,   doAdd   , differentiationLog    ,   TWO_ARG    },
{ POW   , "POW"     , "^"       , printFunctionWithOneStaples   , "^{"          ,   doAdd   , differentiationPow    ,   TWO_ARG    },
{ SIN   , "SIN"     , "sin"     , printFunctionOfOneArguments   , "sin "        ,   doAdd   , differentiationSin    ,   TRIG       },
{ COS   , "COS"     , "cos"     , printFunctionOfOneArguments   , "cos "        ,   doAdd   , differentiationCos    ,   TRIG       },
{ TG    , "TG"      , "tg"      , printFunctionOfOneArguments   , "tg "         ,   doAdd   , differentiationTg     ,   TRIG       },
{ CTG   , "CTG"     , "ctg"     , printFunctionOfOneArguments   , "ctg "        ,   doAdd   , differentiationCtg    ,   TRIG       },
{ ARCSIN, "ARCSIN"  , "arcsin"  , printFunctionOfOneArguments   , "arcsin "     ,   doAdd   , differentiationArcsin ,   TRIG       },
{ ARCCOS, "ARCCOS"  , "arccos"  , printFunctionOfOneArguments   , "arccos "     ,   doAdd   , differentiationArccos ,   TRIG       },
{ ARCTG , "ARCTG"   , "arctg"   , printFunctionOfOneArguments   , "arctg "      ,   doAdd   , differentiationArctg  ,   TRIG       },
{ ARCCTG, "ARCCTG"  , "arcctg"  , printFunctionOfOneArguments   , "arcctg "     ,   doAdd   , differentiationArcctg ,   TRIG       },
{ SH    , "SH"      , "sh"      , printFunctionOfOneArguments   , "sh "         ,   doAdd   , differentiationSh     ,   TRIG       },
{ CH    , "CH"      , "ch"      , printFunctionOfOneArguments   , "ch "         ,   doAdd   , differentiationCh     ,   TRIG       },
{ TH    , "TH"      , "th"      , printFunctionOfOneArguments   , "th "         ,   doAdd   , differentiationTh     ,   TRIG       },
{ CTH   , "CTH"     , "cth"     , printFunctionOfOneArguments   , "cth "        ,   doAdd   , differentiationCth    ,   TRIG       },
{ EXP   , "EXP"     , "exp"     , printFunctionWithOneStaples   , "e^{"         ,   doAdd   , differentiationExp    ,   ONE_ARG    },
{ SQRT  , "SQRT"    , "sqrt"    , printFunctionWithOneStaples   , "\\sqrt{"     ,   doAdd   , differentiationSqrt   ,   ONE_ARG    }
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
