#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "treeDump.h"

static int firstRank = 1;

static void dumpTheSortedNodeInFile( const node_t* node, FILE* fileForWrite );

static void dumpTheSortedTreeInFile( const tree_t* tree, FILE* fileForWrite );

informationWithValueType arrayWithValueType[] = {
        { NUMBER, "NUMBER"},
        { VARIABLE, "VARIABLE"},
        { OPERATOR, "OPERATOR"}
};
size_t sizeOfArrayWithValueType = sizeof( arrayWithValueType ) / sizeof( arrayWithValueType[ 0 ] );

informationWithMathOperators arrayWithMathOperators[] = {
        { ADD   , "ADD"     , "+"      },
        { SUB   , "SUB"     , "-"      },
        { MUL   , "MUL"     , "*"      },
        { DIV   , "DIV"     , "/"      },
        { LN    , "LN"      , "ln"     },
        { LOG   , "LOG"     , "log"    },
        { POW   , "POW"     , "^"      },
        { SIN   , "SIN"     , "sin"    },
        { COS   ,  "COS"    , "cos"    },
        { TG    ,  "TG"     , "tg"     },
        { CTG   ,  "CTG"    , "ctg"    },
        { ARCSIN,  "ARCSIN" , "arcsin" },
        { ARCCOS,  "ARCCOS" , "arccos" },
        { ARCTG ,  "ARCTG"  , "arctg"  },
        { ARCCTG,  "ARCCTG" , "arcctg" },
        { SH    ,  "SH"     , "sh"     },
        { TH    ,  "TH"     , "th"     },
        { CTH   ,  "CTH"    , "cth"    },
        { EXP   ,  "EXP"    , "exp"    },
        { SQRT  , "SQRT"    , "sqrt"   }
};
size_t sizeOfArrayWithMathOperators = sizeof( arrayWithMathOperators ) / sizeof( arrayWithMathOperators[ 0 ] );

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
size_t sizeOfArrayWithVariables = sizeof( arrayWithVariables ) / sizeof( arrayWithVariables[ 0 ] );


void dumpNode( node_t* node, int rank, FILE* treeFile ){
    assert( node );
    assert( treeFile );


    const char* stringNodeValueType = getStringOfValueType( node );
    if( node->nodeValueType == NUMBER ){
        fprintf( treeFile, "\tnode%lx [shape=\"plain\"; style =\"filled\"; fillcolor =\"hotpink2\"; label = "
                            "<<table><tr><td colspan = \"2\" > %p </td></tr> <tr><td colspan = \"2\" > parent = %p </td></tr> <tr><td width = \"100\" colspan = \"2\" > type = %s </td></tr> <tr><td width = \"100\" colspan = \"2\" > val = %lg </td></tr> ",
                            ( unsigned long )node, node, node->parent, stringNodeValueType, node->data.number  );
    }
    else if( node->nodeValueType == OPERATOR ){
        fprintf( treeFile, "\tnode%lx [shape=\"plain\"; style =\"filled\"; fillcolor =\"orange\"; label = "
                            "<<table><tr><td colspan = \"2\" > %p </td></tr> <tr><td colspan = \"2\" > parent = %p </td></tr> <tr><td width = \"100\" colspan = \"2\" > type = %s </td></tr> <tr><td width = \"100\" colspan = \"2\" > val = %s </td></tr> ",
                            ( unsigned long )node, node, node->parent, stringNodeValueType, getStringOfMathOperator( node )  );
    }
    else if( node->nodeValueType == VARIABLE){
        fprintf( treeFile, "\tnode%lx [shape=\"plain\"; style =\"filled\"; fillcolor =\"lightskyblue2\"; label = "
                            "<<table><tr><td colspan = \"2\" > %p </td></tr> <tr><td colspan = \"2\" > parent = %p </td></tr> <tr><td width = \"100\" colspan = \"2\" > type = %s </td></tr> <tr><td width = \"100\" colspan = \"2\" > val = %d (%s) </td></tr> ",
                            ( unsigned long )node, node, node->parent, stringNodeValueType, node->data.variableInArray, getStringOfVariable( node )  );
    }

    if( node->left ){
        fprintf( treeFile, "<tr><td> %p </td>", node->left );
    }
    else{
        fprintf( treeFile, "<tr><td> NULL </td>" );
    }

    if( node->right ){
        fprintf( treeFile, "<td> %p </td></tr>", node->right );
    }
    else{
        fprintf( treeFile, "<td> NULL </td></tr>" );
    }

    fprintf( treeFile, "</table>>;];\n" );

    fprintf( treeFile, "\t{\n"
                       "\t\trank = %d;\n"
                       "\t\tnode%lx;\n"
                       "\t}\n",
                       rank, ( unsigned long )node );

    if( node->left ){
        fprintf( treeFile, "\t\tnode%lx;\n"
                            "\tnode%lx->node%lx[color = \"orange\"];\n",
                            ( unsigned long )node->left, ( unsigned long )node, ( unsigned long )node->left );
        dumpNode( node->left, rank + 1, treeFile );
    }
    if( node->right ){
        fprintf( treeFile, "\t\tnode%lx;\n"
                           "\tnode%lx->node%lx[color = \"orange\"];\n",
                           ( unsigned long )node->right, ( unsigned long )node, ( unsigned long )node->right );
        dumpNode( node->right, rank + 1, treeFile );
    }

}

treeErrors dumpTree( tree_t* tree ){
    assert( tree );
    if( tree->rootTree == NULL ){
        return NODE_NULL_PTR;
    }

    FILE* treeFile = fopen( "treeDump.txt", "w" );

    if( treeFile == NULL ){
        return ERROR_OF_OPEN_FILE;
        fclose( treeFile );
    }

    fprintf( treeFile,  "digraph G{\n"
                        "\trankdir = TB;\n"
                        "\tnode[shape = \"hexagon\", color = \"black\", fontsize = 14, shape = record ];\n"
                        "\tedge[color = \"red\", fontsize = 12];\n" );

    dumpNode( tree->rootTree, firstRank, treeFile );

    fprintf( treeFile, "}" );

    fclose( treeFile );

    system("dot treeDump.txt -Tpng -o treeDump.png");

    //HTML

    FILE* htmlDump = fopen( "treeDump.html", "w" );
    if( htmlDump == NULL ){
        return ERROR_OF_OPEN_FILE;
    }

    fprintf( htmlDump, "<pre>\n"
                       "<h1> <font color=red> TREE DUMP </font>  </h1>"
                       "\n\n"
                       "<h1> TREE { %s:%s:%d } </h1>\n\n", __FILE__, __func__, __LINE__ );

    fprintf( htmlDump, "<h2 style = \"color: green;\">tree: \n");
    dumpTreeInFile( tree, htmlDump );


    fprintf( htmlDump, "</h2>\n\n<h2 style = \"color: orange;\">sorted tree: \n" );
    dumpTheSortedTreeInFile( tree, htmlDump );

    fprintf( htmlDump, "</h2>\n\n<h1>Image:</h1>\n"
                       "<img src=treeDump.png width = 2000px>\n\n");

    fclose( htmlDump );

    return CORRECT_TREE;
}

void dumpNodeInFile( const node_t* node, FILE* fileForPrint ){
    assert( node );
    assert( fileForPrint );

    if( node->nodeValueType == NUMBER ){
        fprintf( fileForPrint, "( %lg ", node->data.number );
    }
    else if( node->nodeValueType == VARIABLE ){
        fprintf( fileForPrint, "( %s ", getStringOfVariable( node ) );
    }
    else if( node->nodeValueType == OPERATOR ){
        fprintf( fileForPrint, "( %s ", getViewOfMathOperation( node ) );
    }

    if( node->left ){
        dumpNodeInFile( node->left, fileForPrint);
    }
    else{
        fprintf( fileForPrint, "nil" );
    }
    if( node->right ){
        dumpNodeInFile( node->right, fileForPrint );
    }
    else{
        fprintf( fileForPrint, "nil" );
    }

    fprintf( fileForPrint, ")" );
}

void dumpTreeInFile( const tree_t* tree, FILE* fileForPrint ){
    assert( tree );
    assert( fileForPrint );

    dumpNodeInFile( tree->rootTree, fileForPrint );
}

static void dumpTheSortedNodeInFile( const node_t* node, FILE* fileForPrint ){
    assert( node );
    assert( fileForPrint );

    if( node->left ){
        dumpTheSortedNodeInFile( node->left, fileForPrint);
    }

    if( node->nodeValueType == NUMBER ){
        fprintf( fileForPrint, " %lg ", node->data.number );
    }
    else if( node->nodeValueType == VARIABLE ){
        fprintf( fileForPrint, " %s ", getStringOfVariable( node ) );
    }
    else if( node->nodeValueType == OPERATOR ){
        fprintf( fileForPrint, " %s ", getViewOfMathOperation( node ) );
    }

    if( node->right ){
        dumpTheSortedNodeInFile( node->right, fileForPrint);
    }
}

static void dumpTheSortedTreeInFile( const tree_t* tree, FILE* fileForPrint ){
    assert( tree );
    assert( fileForPrint );

    dumpTheSortedNodeInFile( tree->rootTree, fileForPrint );
}

const char* getStringOfValueType( const node_t* node ){
    if( node == NULL ){
        return NULL;
    }

    for( size_t typeIndex = 0; typeIndex < sizeOfArrayWithValueType; typeIndex++ ){
        if( node->nodeValueType == arrayWithValueType[ typeIndex ].typeOfData ){
            return arrayWithValueType[ typeIndex ].nameOfType;
        }
    }

    return NULL;
}

const char* getStringOfMathOperator( const node_t* node ){
    if( node == NULL ){
        return NULL;
    }

    for( size_t mathIndex = 0; mathIndex < sizeOfArrayWithMathOperators; mathIndex++ ){
        if( node->data.mathOperation == arrayWithMathOperators[ mathIndex ].mathOperation ){
            return arrayWithMathOperators[ mathIndex ].nameOfMathOperation;
        }
    }

    return NULL;
}

const char* getStringOfVariable( const node_t* node ){
    if( node == NULL ){
        return NULL;
    }

    for( size_t variableIndex = 0; variableIndex < sizeOfArrayWithVariables; variableIndex++ ){
        if( node->data.variableInArray == arrayWithVariables[ variableIndex ].variable ){
            return arrayWithVariables[ variableIndex ].nameOfVariable;
        }
    }

    return NULL;
}

const char* getViewOfMathOperation( const node_t* node ){
    if( node == NULL ){
        return NULL;
    }

    for( size_t mathIndex = 0; mathIndex < sizeOfArrayWithMathOperators; mathIndex++ ){
        if( node->data.mathOperation ==  arrayWithMathOperators[ mathIndex ].mathOperation ){
            return arrayWithMathOperators[ mathIndex ].viewOfMathOperation;
        }
    }

    return NULL;
}

