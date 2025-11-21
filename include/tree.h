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
    DIV     = 3,
    LOG     = 4,
    LN      = 5,
    POW     = 6,
    SIN     = 7,
    COS     = 8,
    SQRT    = 9,
    TG      = 10,
    CTG     = 11,
    ARCSIN  = 12,
    ARCCOS  = 13,
    ARCTG   = 14,
    ARCCTG  = 15,
    SH      = 16,
    TH      = 17,
    CTH     = 18,
    EXP     = 19
};

enum variablesAndTheyIndex {
    X       = 0,
    Y       = 1,
    I       = 2,
    J       = 3,
    K       = 4,
    L       = 5,
    M       = 6,
    N       = 7,
    O       = 8,
    P       = 9,
    Q       = 10,
    R       = 11,
    S       = 12,
    A       = 13,
    B       = 14,
    C       = 15,
    Z       = 16,
    W       = 17,
    D       = 18,
    E       = 19,
    F       = 20,
    T       = 21,
    U       = 22,
    V       = 23,
    G       = 24,
    H       = 25
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
