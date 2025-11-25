#ifndef H_GLOBALS
#define H_GLOBALS

#include <stdio.h>

#include "tree.h"

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
struct informationWithValueType {
    typeOfDataInNode typeOfData;
    const char* nameOfType;
};

extern informationWithValueType arrayWithValueType[];
extern const size_t sizeOfArrayWithValueType;

struct informationWithMathOperators {
    typeOfMathOperation mathOperation;
    const char* nameOfMathOperation;
    const char* viewOfMathOperationInFile;
    void(*printInLatex)( FILE* fileForLatex, node_t* node );
    const char* viewInLatex;
    double(*doMathOperation)( double firstNumber, double doubleSecondNumber );
    node_t*(*differentiationFunc)( const node_t* node, variablesAndTheyIndex variable );
};

extern informationWithMathOperators arrayWithMathInfo[];
extern const size_t sizeOfMathArray;

struct informationWithVariables {
    variablesAndTheyIndex variable;
    const char* nameOfVariable;
};

extern informationWithVariables arrayWithVariables[];
extern const size_t sizeOfArrayWithVariables;


#endif
