#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "mathDump.h"
#include "treeDump.h"
#include "myStringFunction.h"
#include "paint.h"

informationOfMathOperations arrayWithMathOperation[] = {
    { ADD   , " + "         },
    { SUB   , " - "         },
    { MUL   , " \\cdot "    },
    { LN    , " ln "        },
    { SIN   , " sin "       },
    { COS   ,  " cos "      },
    { TG    ,  " tg "       },
    { CTG   ,  " ctg "      },
    { ARCSIN,  " arcsin "   },
    { ARCCOS,  " arccos "   },
    { ARCTG ,  " arctg "    },
    { ARCCTG,  " arcctg"    },
    { SH    ,  " sh "       },
    { TH    ,  " th "       },
    { CTH   ,  " cth "      },
};
size_t sizeOfArrayWithMathOperation = sizeof( arrayWithMathOperation ) / sizeof( arrayWithMathOperation[ 0 ] );

informationOfPrefixFunctions arrayWithPrefixFunc[] = {
    { DIV,  printFracInLatex },
    { SQRT, printSqrtInLatex },
    { EXP,  printExpInLatex  },
    { POW,  printPowInLatex  },
    { LOG,  printLogInLatex  }
};
size_t sizeOfArrayWithPrefixFunc = sizeof( arrayWithPrefixFunc ) / sizeof( arrayWithPrefixFunc[ 0 ] );

treeErrors dumpMathTree( tree_t* tree ){
    assert( tree );

    colorPrintf( NOMODE, YELLOW, "Enter the name of file, where i will save latex dump: " );

    char* nameOfFileForLatexDump = NULL;
    size_t sizeOfAllocationMemory = 0;
    ssize_t sizeOfLine = getlineWrapper( &nameOfFileForLatexDump, &sizeOfAllocationMemory, stdin );

    if( sizeOfLine == -1 ){
        return ERROR_OF_GET_NAME_OF_FILE;
    }

    FILE* fileForLatex = fopen( nameOfFileForLatexDump, "w" );
    if( fileForLatex == NULL ){
        free( nameOfFileForLatexDump );
        return ERROR_OF_OPEN_FILE;
    }

    fprintf( fileForLatex, "\\documentclass[12pt, litterpaper]{article}\n"
                            "\\usepackage{graphicx}\n"
                            "\\usepackage{mathtext}\n"
                            "\\usepackage[utf8]{inputenc}\n"
                            "\\usepackage[english, russian]{babel}\n"
                            "\\usepackage{float}\n"
                            "\\usepackage{tabularx}\n"
                            "\\begin{document}\n"

    );

    fprintf( fileForLatex, "\\textb{визуализация математический формул в LaTeX:}\n"
                            "\\newline\n\\newline\n"
    );

    fprintf( fileForLatex, "\\[ " );

    printMathematicalFormulas( fileForLatex, tree->rootTree );

    fprintf( fileForLatex, " \\]\n" );

    fprintf( fileForLatex, "\\end{document}" );

    fclose( fileForLatex );
    free( nameOfFileForLatexDump );

    return CORRECT_TREE;
}

void printMathematicalFormulas( FILE* fileForLatex, node_t* node ){
    assert( node );
    assert( fileForLatex );

    typeOfFunctions classificationOfFunction = getTypeOfDataInNode( node );

    if( classificationOfFunction == ROOT_FUNCTION || classificationOfFunction == NOT_FUNCTION ){
        printInOrderBypass( fileForLatex, node );
    }
    else if( classificationOfFunction == PREFIX_FUNCTION ){
        printPrefixBypass( fileForLatex, node );
    }

}

operationComparison compareTwoMathOperator( node_t* currentNode, node_t* parentNode ){
    if( currentNode == NULL ){
        return ERROR_OF_COMPARE;
    }
    if( parentNode == NULL || currentNode->nodeValueType != OPERATOR ){
        return MORE_BY_PRIORITY;
    }

    if( (currentNode->data.mathOperation == ADD || currentNode->data.mathOperation == SUB) &&
        ( parentNode->data.mathOperation == MUL || parentNode->data.mathOperation == DIV ) ){

        return LOWER_IN_PRIORITY;
    }
    else{
        return LOWER_IN_PRIORITY;
    }
}

void viewMathFormula( FILE* fileForLatex, node_t* node ){
    if( fileForLatex == NULL || node == NULL ){
        return ;
    }

    for( size_t mathIndex = 0; mathIndex < sizeOfArrayWithMathOperation; mathIndex++ ){
        if( node->data.mathOperation == arrayWithMathOperation[ mathIndex ].typeOp ){
            fprintf( fileForLatex, "%s", arrayWithMathOperation[ mathIndex ].stringMathOp );
            break;
        }
    }
}

void printNumberInLatex( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    if( node->data.number < 0 ){
        fprintf( fileForLatex, " (%lg) ", node->data.number );
    }
    else{
        fprintf( fileForLatex, " %lg ", node->data.number );
    }
}

typeOfFunctions getTypeOfDataInNode( node_t* node ){
    assert( node );

    if( node->nodeValueType != OPERATOR ){
        return NOT_FUNCTION;
    }
    switch( node->data.mathOperation ){
        case ADD: case SUB: case MUL:
            return ROOT_FUNCTION;
            break;
        case DIV: case EXP: case SQRT: case LOG: case POW:
            return PREFIX_FUNCTION;
            break;
        default:
            return NOT_FUNCTION;
    }
}

void printPrefixBypass( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    operationComparison statusOfCompare = compareTwoMathOperator( node, node->parent );
    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\left(" );
    }

    for( size_t prefixFunc = 0; prefixFunc < sizeOfArrayWithPrefixFunc; prefixFunc++ ){
        if( node->data.mathOperation == arrayWithPrefixFunc[ prefixFunc ].typeOp ){
            arrayWithPrefixFunc[ prefixFunc ].func( fileForLatex, node );
            break;
        }
    }

    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\right)" );
    }
}

void printInOrderBypass( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    operationComparison statusOfCompare = compareTwoMathOperator( node, node->parent );
    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\left(" );
    }

    if( node->left ){
        printMathematicalFormulas( fileForLatex, node->left );
    }

    if( node->nodeValueType == NUMBER ){
        printNumberInLatex( fileForLatex, node );
    }
    else if( node->nodeValueType == VARIABLE ){
        fprintf( fileForLatex, " %s ", getStringOfVariable( node ) );
    }
    else if( node->nodeValueType == OPERATOR ){
        viewMathFormula( fileForLatex, node );
    }

    if( node->right ){
        printMathematicalFormulas( fileForLatex, node->right );
    }

    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "\\right)" );
    }
}

void printFracInLatex( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    fprintf( fileForLatex, "\\frac{" );
    if( node->left ){
        printMathematicalFormulas( fileForLatex, node->left );
    }
    fprintf( fileForLatex, "}{" );
    if( node->right ){
        printMathematicalFormulas( fileForLatex, node->right );
    }
    fprintf( fileForLatex, "}" );
}

void printSqrtInLatex( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    fprintf( fileForLatex, "\\sqrt{" );
    if( node->left ){
        printMathematicalFormulas( fileForLatex, node->left );
    }
    fprintf( fileForLatex, "}{" );
    if( node->right ){
        printMathematicalFormulas( fileForLatex, node->right );
    }
    fprintf( fileForLatex, "}" );
}

void printExpInLatex( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    fprintf( fileForLatex, "e^{" );
    if( node->left ){
        printMathematicalFormulas( fileForLatex, node->left );
    }
    if( node->right ){
        printMathematicalFormulas( fileForLatex, node->right );
    }
    fprintf( fileForLatex, "}" );
}

void printLogInLatex( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    fprintf( fileForLatex, "\\log_{" );
    if( node->left ){
        printMathematicalFormulas( fileForLatex, node->left );
    }
    fprintf( fileForLatex, "}{" );
    if( node->right ){
        printMathematicalFormulas( fileForLatex, node->right );
    }
    fprintf( fileForLatex, "}" );
}

void printPowInLatex( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    if( node->left ){
        printMathematicalFormulas( fileForLatex, node->left );
    }

    fprintf( fileForLatex, "^{" );

    if( node->right ){
        printMathematicalFormulas( fileForLatex, node->right );
    }
    fprintf( fileForLatex, "}" );
}
