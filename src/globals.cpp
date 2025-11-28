#include <stdio.h>
#include <assert.h>

#include "globals.h"
#include "mathDump.h"
#include "mathematicalCalculator.h"

informationWithMathOperators arrayWithMathInfo[] = {
{ ADD   , "ADD"     , "+"       , printCenterFunctionInLatex    , "+"           ,   doAdd   , differentiationAdd    ,   TWO_ARG    }, //complete
{ SUB   , "SUB"     , "-"       , printCenterFunctionInLatex    , "-"           ,   doSub   , differentiationSub    ,   TWO_ARG    }, //complete
{ MUL   , "MUL"     , "*"       , printCenterFunctionInLatex    , "\\cdot "     ,   doMul   , differentiationMul    ,   TWO_ARG    }, //complete
{ DIV   , "DIV"     , "/"       , printFunctionOfTwoArguments   , "\\frac{"     ,   doDiv   , differentiationDiv    ,   TWO_ARG    }, //complete
{ LN    , "LN"      , "ln"      , printFunctionOfOneArguments   , "ln"          ,   doAdd   , differentiationLn     ,   ONE_ARG    },
{ LOG   , "LOG"     , "log"     , printFunctionOfTwoArguments   , "\\log_{"     ,   doAdd   , differentiationLog    ,   TWO_ARG    },
{ POW   , "POW"     , "^"       , printFunctionWithOneStaples   , "^{"          ,   doAdd   , differentiationPow    ,   TWO_ARG    }, //complete
{ SIN   , "SIN"     , "sin"     , printFunctionOfOneArguments   , "sin "        ,   doAdd   , differentiationSin    ,   TRIG       }, //complete
{ COS   , "COS"     , "cos"     , printFunctionOfOneArguments   , "cos "        ,   doAdd   , differentiationCos    ,   TRIG       }, //complete
{ TG    , "TG"      , "tg"      , printFunctionOfOneArguments   , "tg "         ,   doAdd   , differentiationTg     ,   TRIG       }, //complete
{ CTG   , "CTG"     , "ctg"     , printFunctionOfOneArguments   , "ctg "        ,   doAdd   , differentiationCtg    ,   TRIG       }, //complete
{ ARCSIN, "ARCSIN"  , "arcsin"  , printFunctionOfOneArguments   , "arcsin "     ,   doAdd   , differentiationArcsin ,   TRIG       }, //complete
{ ARCCOS, "ARCCOS"  , "arccos"  , printFunctionOfOneArguments   , "arccos "     ,   doAdd   , differentiationArccos ,   TRIG       }, //complete
{ ARCTG , "ARCTG"   , "arctg"   , printFunctionOfOneArguments   , "arctg "      ,   doAdd   , differentiationArctg  ,   TRIG       }, //complete
{ ARCCTG, "ARCCTG"  , "arcctg"  , printFunctionOfOneArguments   , "arcctg "     ,   doAdd   , differentiationArcctg ,   TRIG       }, //complete
{ SH    , "SH"      , "sh"      , printFunctionOfOneArguments   , "sh "         ,   doAdd   , differentiationSh     ,   TRIG       }, //complete
{ CH    , "CH"      , "ch"      , printFunctionOfOneArguments   , "ch "         ,   doAdd   , differentiationCh     ,   TRIG       }, //complete
{ TH    , "TH"      , "th"      , printFunctionOfOneArguments   , "th "         ,   doAdd   , differentiationTh     ,   TRIG       }, //complete
{ CTH   , "CTH"     , "cth"     , printFunctionOfOneArguments   , "cth "        ,   doAdd   , differentiationCth    ,   TRIG       }, //complete
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
