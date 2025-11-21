#include <stdio.h>
#include <assert.h>

#include "mathDump.h"
#include "treeDump.h"

treeErrors dumpMathTree( tree_t* tree ){
    assert( tree );

    FILE* fileForLatex = fopen( "latexDump.tex", "w" );
    if( fileForLatex == NULL ){
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
        return MORE_BY_PRIORITY;
    }
}

void viewMathFormula( FILE* fileForLatex, node_t* node ){
    if( fileForLatex == NULL || node == NULL ){
        return ;
    }

    switch( node->data.mathOperation ){
        case ADD:
            fprintf( fileForLatex, " + " );
            break;
        case SUB:
            fprintf( fileForLatex, " - " );
            break;
        case MUL:
            fprintf( fileForLatex, " \\cdot " );
            break;
        default:
            return ;
            break;
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
        case DIV:
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
        fprintf( fileForLatex, "(" );
    }

    switch( node->data.mathOperation ){
        case DIV:
            printFracInLatex( fileForLatex, node );
            break;
        default:
            break;
    }

    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, ")" );
    }
}

void printInOrderBypass( FILE* fileForLatex, node_t* node ){
    assert( fileForLatex );
    assert( node );

    operationComparison statusOfCompare = compareTwoMathOperator( node, node->parent );
    if( statusOfCompare == LOWER_IN_PRIORITY ){
        fprintf( fileForLatex, "(" );
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
        fprintf( fileForLatex, ")" );
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
