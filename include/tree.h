#ifndef H_TREE
#define H_TREE

#include <limits.h>
#include <float.h>

#define treeValueFormat "%s"
#define nodeValueFormatForPrint( valueFormat ) valueFormat;
#define maxTreeValue DBL_MAX

const size_t oneStruct = 1;

enum treeErrors {
    CORRECT_TREE                = 0,
    NODE_NULL_PTR               = 1,
    NOT_ENOUGH_MEMORY           = 2,
    ERROR_OF_OPEN_FILE          = 3,
    NOT_CORRECT_TYPE_OF_DATA    = 4,
    ERROR_OF_GET_NAME_OF_FILE   = 5
};

enum typeOfDataInNode {
    NUMBER      = 0,
    OPERATOR    = 1,
    VARIABLE    = 2
};

#define typeOfRoot NUMBER

enum typeOfMathOperation {
    ADD     = 0,
    SUB     = 1,
    MUL     = 2,
    DIV     = 3
};

enum variablesAndTheyIndex {
    X       = 0,
    Y       = 1
};

union treeElem_t {
    double number;
    variablesAndTheyIndex variableInArray;
    typeOfMathOperation mathOperation;
};

struct node_t {
    typeOfDataInNode nodeValueType;
    treeElem_t data;
    node_t* left;
    node_t* right;
    node_t* parent;
};

struct tree_t{
    node_t* rootTree;
};

void printNode( const node_t* tree );

void printTree( const tree_t* tree );

void printTheSortedNode( const node_t* tree );

void printTheSortedTree( const tree_t* tree );

treeErrors initTree( tree_t* tree );

treeErrors initNode( node_t** node, typeOfDataInNode typeOfData, treeElem_t element );

treeErrors initializationDataInNode( node_t** node, typeOfDataInNode typeOfData, treeElem_t element  );

treeErrors insertNode( tree_t* root, treeElem_t element );

void destroyNode( node_t* node );

void destroyTree( tree_t* node );

#endif
