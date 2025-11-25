#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "mathDump.h"
#include "treeDump.h"
#include "myStringFunction.h"
#include "paint.h"
#include "globals.h"

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

    if( node->nodeValueType == NUMBER ){
        printNumberInLatex( fileForLatex, node );
    }
    else if( node->nodeValueType == VARIABLE ){
        fprintf( fileForLatex, " %s ", getStringOfVariable( node ) );
    }
    else{
        printMathFunction( fileForLatex, node );
    }

}

operationComparison compareTwoMathOperator( node_t* currentNode, node_t* parentNode ){
    if( currentNode == NULL ){
        return ERROR_OF_COMPARE;
    }
    if( parentNode == NULL || currentNode->nodeValueType != OPERATOR ){
        return MORE_BY_PRIORITY;
    }

    if( ( currentNode->data.mathOperation == ADD || currentNode->data.mathOperation == SUB ) &&
        !( parentNode->data.mathOperation == ADD || parentNode->data.mathOperation == SUB ) &&
          parentNode->data.mathOperation != DIV ){

        return LOWER_IN_PRIORITY;
    }
    else if( (currentNode->data.mathOperation == MUL || currentNode->data.mathOperation == DIV ) &&
             ( parentNode->data.mathOperation == LOG || parentNode->data.mathOperation == LN ||
               parentNode->data.mathOperation == POW || parentNode->data.mathOperation == SIN ||
               parentNode->data.mathOperation == COS   ) ){
        return LOWER_IN_PRIORITY;
    }
    else{
        return MORE_BY_PRIORITY;
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


