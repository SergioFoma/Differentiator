#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "treeDump.h"
#include "expertSystem.h"
#include "paint.h"
#include "parseFileDataBase.h"

int main(){

    treeElem_t typeOfDataValue = {};
    tree_t tree = {};

    /*initTree( &tree );

    node_t* node_1 = {};
    typeOfDataValue.mathOperation = MUL;
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
    typeOfDataValue.number = 6;
    initNode( &node_5, NUMBER, typeOfDataValue );

    (tree.rootTree)->left = node_1;
    node_1->left = node_2;
    node_1->right = node_3;
    node_3->left = node_4;
    node_3->right = node_5;

    writeInformationInFile( &tree );*/

    createTreeFromFile( &tree );

    dumpTree( &tree );

    destroyTree( &tree );


    return 0;
}



