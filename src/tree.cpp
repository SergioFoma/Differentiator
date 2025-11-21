#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"

void printNode( const node_t* node ){
    assert( node );

    printf( "(\"" treeValueFormat "\" ", node->data );

    if( node->left ){
        printNode( node->left );
    }
    if( node->right ){
        printNode( node->right );
    }

    printf( ")" );
}

void printTree( const tree_t* tree ){
    assert( tree );

    printNode( tree->rootTree );
}

void printTheSortedNode( const node_t* node ){
    assert( node );

    if( node->left ){
        printTheSortedNode( node->left );
    }

    printf( treeValueFormat " ", node->data );

    if( node->right ){
        printTheSortedNode( node->right );
    }
}

void printTheSortedTree( const tree_t* tree ){
    assert( tree );

    printTheSortedNode( tree->rootTree );
}

treeErrors initNode( node_t** node, typeOfDataInNode typeOfData, treeElem_t element ){
    assert( node );

    *node = ( node_t* )calloc( oneStruct, sizeof( node_t ) );
    if( *node == NULL ){
        return NOT_ENOUGH_MEMORY;
    }

    initializationDataInNode( node, typeOfData, element );

    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->parent = NULL;

    return CORRECT_TREE;
}

treeErrors initTree( tree_t* tree ){
    assert( tree );

    treeElem_t data;
    data.number = maxTreeValue;
    treeErrors errorWithInitialization = initNode( &(tree->rootTree), typeOfRoot, data );

    if( errorWithInitialization != CORRECT_TREE ){
        return errorWithInitialization;
    }

    return CORRECT_TREE;
}

treeErrors initializationDataInNode( node_t** node, typeOfDataInNode typeOfData, treeElem_t element ){
    if( node == NULL ){
        return NODE_NULL_PTR;
    }
    switch( typeOfData ){
        case NUMBER:
            (*node)->nodeValueType = NUMBER;
            (*node)->data.number = element.number;
            break;
        case OPERATOR:
            (*node)->nodeValueType = OPERATOR;
            (*node)->data.mathOperation = element.mathOperation;
            break;
        case VARIABLE:
            (*node)->nodeValueType = VARIABLE;
            (*node)->data.variableInArray = element.variableInArray;
            break;
        default:
            return NOT_CORRECT_TYPE_OF_DATA;
            break;
    }

    return CORRECT_TREE;
}


void destroyNode( node_t* node ){
    if( node == NULL ){
        return ;
    }

    if( node->left  ){
        destroyNode( node->left );
    }

    if( node->right ){
        destroyNode( node->right );
    }

    free( node );
}

void destroyTree( tree_t* tree ){
    if( tree == NULL ){
        return ;
    }

    destroyNode( tree->rootTree );

    *tree = {};
}
