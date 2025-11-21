#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "treeDump.h"
#include "mathDump.h"
#include "parseFileDataBase.h"
#include "mathematicalCalculator.h"

int main(){

    treeElem_t typeOfDataValue = {};
    tree_t tree = {};

    /*initTree( &tree );

    node_t* node_1 = {};
    typeOfDataValue.mathOperation = DIV;
    initNode( &node_1, OPERATOR, typeOfDataValue );

    node_t* node_2 = {};
    typeOfDataValue.variableInArray = X;
    initNode( &node_2, VARIABLE, typeOfDataValue );

    node_t* node_3 = {};
    typeOfDataValue.mathOperation = ADD;
    initNode( &node_3, OPERATOR, typeOfDataValue );

    node_t* node_4 = {};
    typeOfDataValue.variableInArray = Y;
    initNode( &node_4, VARIABLE, typeOfDataValue );

    node_t* node_5 = {};
    typeOfDataValue.number = -6;
    initNode( &node_5, NUMBER, typeOfDataValue );

    node_t* node_6 = {};
    typeOfDataValue.mathOperation = ADD;
    initNode( &node_6, OPERATOR, typeOfDataValue );

    node_t* node_7 = {};
    typeOfDataValue.number = 12.7;
    initNode( &node_7, NUMBER, typeOfDataValue );


    (tree.rootTree)->left = node_1;
    node_1->left = node_6;
    node_1->right = node_3;
    node_1->parent = tree.rootTree;
    node_6->parent = node_1;
    node_6->left = node_7;
    node_6->right = node_2;
    node_2->parent = node_6;
    node_7->parent = node_6;
    node_3->left = node_4;
    node_3->right = node_5;
    node_3->parent = node_1;
    node_4->parent = node_3;
    node_5->parent = node_3;

    writeInformationInFile( &tree );*/

    createTreeFromFile( &tree );

    dumpMathTree( &tree );

    //calculateTheFunctionValue( &tree );

    //writeInformationInFile( &tree );

    tree_t differentiationTree ={};

    differentiationOfTheFunction( &tree, &differentiationTree );

    dumpMathTree( &differentiationTree );

    dumpTree( &tree );

    destroyTree( &differentiationTree );

    destroyTree( &tree );

    return 0;
}



