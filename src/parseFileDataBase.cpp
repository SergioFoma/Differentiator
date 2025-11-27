#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

#include "parseFileDataBase.h"
#include "treeDump.h"
#include "myStringFunction.h"
#include "paint.h"
#include "globals.h"
#include "mathematicalCalculator.h"

const size_t maxLenOfTrigonometryFunction = 6;

expertSystemErrors writeInformationInFile( tree_t* tree ){
    if( tree == NULL ){
        return TREE_NULL_PTR;
    }

    colorPrintf( NOMODE, YELLOW, "\nEnter the name of file were do you want save data base: " );

    char* fileNameForWrite = NULL;
    size_t sizeOfAllocationMemory = 0;
    ssize_t sizeOfLine = getlineWrapper( &fileNameForWrite, &sizeOfAllocationMemory, stdin );
    if( sizeOfLine == -1 ){
        return ERROR_WITH_GETLINE;
    }

    FILE* fileForTree = fopen( fileNameForWrite, "w" );
    if( fileForTree == NULL ){
        colorPrintf( NOMODE, RED, "\nError with write data base in file\n" );
        return ERROR_WITH_FILE;
    }

    dumpTreeInFile( tree, fileForTree );

    free( fileNameForWrite );

    fclose( fileForTree );
    return CORRECT_WORK;
}

errorCode initBufferInformation( bufferInformation *bufferFromFile, FILE* myFile, const char* nameOfFile ){
    assert( bufferFromFile );
    assert( nameOfFile );

    if( myFile == NULL ){
        return fileOpenErr;
    }

    getFileSize( bufferFromFile, nameOfFile );
    bufferFromFile->buffer = (char*)calloc( bufferFromFile->fileSize + 1, sizeof( char ) );
    if( bufferFromFile->buffer == NULL ){
        return memoryErr;
    }
    bufferFromFile->bufferSize = fread( bufferFromFile->buffer, sizeof( char ), bufferFromFile->fileSize, myFile );
    if( bufferFromFile->bufferSize == 0 ){
        return fileOpenErr;
    }

    (bufferFromFile->buffer)[ bufferFromFile->fileSize ]= '\0';
    (bufferFromFile->buffer)[ bufferFromFile->bufferSize ] = '\0';

    return correct;
}

void getFileSize( bufferInformation* bufferFromFile, const char* nameOfFile ){
    assert( bufferFromFile != NULL );
    assert( nameOfFile != NULL );

    struct stat fileText;
    int status = stat( nameOfFile, &fileText );
    if( status == -1 ){
        colorPrintf( NOMODE, RED, "\nError of get information from file\n" );
        return ;
    }

    bufferFromFile->fileSize = fileText.st_size;
}



expertSystemErrors createTreeFromFile( tree_t* tree ){
    if( tree == NULL ){
        return TREE_NULL_PTR;
    }

    colorPrintf( NOMODE, YELLOW, "Enter the name of file, where i will find information for my data base: " );

    char* nameOfFileForDataBase = NULL;
    size_t sizeOfAllocationMemory = 0;
    ssize_t sizeOfLine = getlineWrapper( &nameOfFileForDataBase, &sizeOfAllocationMemory, stdin );

    if( sizeOfLine == -1 ){
        return ERROR_WITH_GETLINE;
    }

    FILE* fileForDataBase = fopen( nameOfFileForDataBase, "r" );
    if( fileForDataBase == NULL ){
        colorPrintf( NOMODE, RED, "\ncan not open file:%s %s %d\n", __FILE__, __func__, __LINE__ );
        free( nameOfFileForDataBase );
        return ERROR_WITH_FILE;
    }

    bufferInformation dataBaseFromFile = {};
    errorCode statusOfReadFromFile = initBufferInformation( &dataBaseFromFile, fileForDataBase, nameOfFileForDataBase);
    if( statusOfReadFromFile != correct ){
        return ERROR_WITH_FILE;
    }

    char* ptrOnBuffer = dataBaseFromFile.buffer;
    tree->rootTree = createNodeFromFile( &ptrOnBuffer );

    fclose( fileForDataBase );
    free( nameOfFileForDataBase );
    destroyBufferInformation( &dataBaseFromFile );

    colorPrintf( NOMODE, GREEN, "Expert system successful get data from your file\n" );
    return CORRECT_WORK;
}


node_t* createNodeFromFile( char** ptrOnSymbolInPosition ){
    if( ptrOnSymbolInPosition == NULL || *( ptrOnSymbolInPosition) == NULL ){
        return NULL;
    }

    if( **ptrOnSymbolInPosition == '(' ){
        ++(*ptrOnSymbolInPosition);
        char* nodeName = readNodeNameFromFile( ptrOnSymbolInPosition );
        node_t* newNode = NULL;
        buildNewNode( &newNode, nodeName );
        newNode->left = createNodeFromFile( ptrOnSymbolInPosition );
        if( newNode->left ){
            newNode->left->parent = newNode;
        }
        newNode->right = createNodeFromFile( ptrOnSymbolInPosition );
        if( newNode->right ){
            newNode->right->parent = newNode;
        }
        ++(*ptrOnSymbolInPosition);
        free( nodeName );
        return newNode;
    }
    else if( **ptrOnSymbolInPosition == 'n' ){
        *ptrOnSymbolInPosition += strlen( "nil" );
        return NULL;
    }

    return NULL;
}

char* readNodeNameFromFile( char** ptrOnSymbolInPosition ){
    if( ptrOnSymbolInPosition == NULL || *(ptrOnSymbolInPosition) == NULL ){
        return NULL;
    }

    char* startOfLineWithNodeName = strchr( *ptrOnSymbolInPosition, ' ' ) + 1;
    char* endOfLineWithNodeName = strchr( startOfLineWithNodeName, ' ' );

    char* nodeName = (char*)calloc( (size_t)(endOfLineWithNodeName - startOfLineWithNodeName) + 1, sizeof( char ) );
    if( nodeName == NULL ){
        return NULL;
    }
    sscanf( startOfLineWithNodeName, "%[^ ]", nodeName );
    *ptrOnSymbolInPosition = endOfLineWithNodeName + 1;

    return nodeName;
}

void destroyBufferInformation( bufferInformation *bufferFromFile ){
    if( bufferFromFile == NULL ){
        return ;
    }

    free( bufferFromFile->buffer );
    bufferFromFile->bufferSize = 0;
    bufferFromFile->fileSize = 0;
    bufferFromFile = NULL;
}

expertSystemErrors buildNewNode( node_t** node, char* nodeName ){
    if( nodeName == NULL ){
        return NULL_PTR_IN_FUNC;
    }

    treeElem_t data = {};

    for( size_t mathIndex = 0; mathIndex < sizeOfMathArray; mathIndex++ ){
        if( strcmp( nodeName, arrayWithMathInfo[ mathIndex ].viewOfMathOperationInFile ) == 0){
            data.mathOperation = arrayWithMathInfo[ mathIndex ].mathOperation;
            initNode( node, OPERATOR, data );
            return CORRECT_WORK;
        }
    }

    for( size_t variableIndex = 0; variableIndex < sizeOfArrayWithVariables; variableIndex++ ){
        if( strcmp( nodeName, arrayWithVariables[ variableIndex ].nameOfVariable ) == 0 ){
            data.variableInArray = arrayWithVariables[ variableIndex ].variable;
            initNode( node, VARIABLE, data );
            return CORRECT_WORK;
        }
    }

    data.number = atof( nodeName );
    initNode( node, NUMBER, data );

    return CORRECT_WORK;
}

expertSystemErrors createTreeByRecursiveDescent( tree_t* tree ){
    colorPrintf( NOMODE, YELLOW, "Enter the name of file, where i will find mathematical statement: " );

    char* nameOfFileForMathStatement = NULL;
    size_t sizeOfAllocationMemory = 0;
    ssize_t sizeOfLine = getlineWrapper( &nameOfFileForMathStatement, &sizeOfAllocationMemory, stdin );

    if( sizeOfLine == -1 ){
        return ERROR_WITH_GETLINE;
    }

    FILE* fileForMathStatement = fopen( nameOfFileForMathStatement, "r" );
    if( fileForMathStatement == NULL ){
        colorPrintf( NOMODE, RED, "\ncan not open file:%s %s %d\n", __FILE__, __func__, __LINE__ );
        free( nameOfFileForMathStatement );
        return ERROR_WITH_FILE;
    }

    bufferInformation dataBaseFromFile = {};
    errorCode statusOfReadFromFile = initBufferInformation( &dataBaseFromFile, fileForMathStatement, nameOfFileForMathStatement);
    if( statusOfReadFromFile != correct ){
        return ERROR_WITH_FILE;
    }

    char* ptrOnSymbolInPosition = dataBaseFromFile.buffer;
    tree->rootTree = getGeneral( &ptrOnSymbolInPosition );

    free( nameOfFileForMathStatement );
    fclose( fileForMathStatement );
    destroyBufferInformation( &dataBaseFromFile );

    colorPrintf( NOMODE, GREEN, "\nSuccessfully reading an expression from a file\n");
    return CORRECT_WORK;
}

node_t* getGeneral( char** ptrOnSymbolInPosition ){
    assert( ptrOnSymbolInPosition );
    assert( *ptrOnSymbolInPosition );

    node_t* expression = getExpression( ptrOnSymbolInPosition );

    if( **ptrOnSymbolInPosition != '$' ){
        colorPrintf( NOMODE, RED, "\nError of getGeneral:%s %s %d\n", __FILE__, __func__, __LINE__ );
        exit( 0 );
    }

    ++(*ptrOnSymbolInPosition);
    return expression;
}

node_t* getExpression( char** ptrOnSymbolInPosition ){
    assert( ptrOnSymbolInPosition );
    assert( *ptrOnSymbolInPosition );

    node_t* left = getTerm( ptrOnSymbolInPosition );

    printf( "%c ", **ptrOnSymbolInPosition );
    while( **ptrOnSymbolInPosition == '+' || **ptrOnSymbolInPosition == '-' ){
        char operation = **ptrOnSymbolInPosition;
        ++(*ptrOnSymbolInPosition);

        node_t* right = getTerm( ptrOnSymbolInPosition );

        if( operation == '+' ){
            return newNode( OPERATOR, ADD, left, right );
        }
        else{
            return newNode( OPERATOR, SUB, left, right );
        }
    }

    printf( "%c ", **ptrOnSymbolInPosition );

    return left;
}

node_t* getTerm( char** ptrOnSymbolInPosition ){
    assert( ptrOnSymbolInPosition );
    assert( *ptrOnSymbolInPosition );

    node_t* left = getTrigonometry( ptrOnSymbolInPosition );

    printf( "%c ", **ptrOnSymbolInPosition );
    while( **ptrOnSymbolInPosition == '*' || **ptrOnSymbolInPosition == '/' ){
        char operation = **ptrOnSymbolInPosition;
        ++(*ptrOnSymbolInPosition);

        node_t* right = getTrigonometry( ptrOnSymbolInPosition );

        if( operation == '*' ){
            return newNode( OPERATOR, MUL, left, right );
        }
        else if( operation == '/' ){
            return newNode( OPERATOR, DIV, left, right );
        }
    }
    printf( "%c ", **ptrOnSymbolInPosition );
    return left;
}

node_t* getTrigonometry( char** ptrOnSymbolInPosition ){
    assert( ptrOnSymbolInPosition );
    assert( *ptrOnSymbolInPosition );

    size_t lineIndex = 0;
    char* lineForTrigonometryFunc = (char*)calloc( maxLenOfTrigonometryFunction + 1, sizeof( char ) );
    printf( "%c ", **ptrOnSymbolInPosition );
    while( islower( (*ptrOnSymbolInPosition)[ lineIndex ] ) && lineIndex < maxLenOfTrigonometryFunction ){
            lineForTrigonometryFunc[ lineIndex ] = (*ptrOnSymbolInPosition)[ lineIndex ];
            ++lineIndex;
    }
    lineForTrigonometryFunc[ maxLenOfTrigonometryFunction ] = '\0';
    printf( "%c ", **ptrOnSymbolInPosition );
    printf( " len = %lu, ", lineIndex );
    printf( "\n line = %s\n", lineForTrigonometryFunc );
    for( size_t indexOfMathFunc = 0; indexOfMathFunc < sizeOfMathArray; indexOfMathFunc++ ){
        if( strcmp( lineForTrigonometryFunc, arrayWithMathInfo[ indexOfMathFunc ].viewOfMathOperationInFile ) == 0 ){
            *ptrOnSymbolInPosition += lineIndex;
            printf( "\n in while = %c ", **ptrOnSymbolInPosition );
            node_t* trigNode = getPrimaryExpression( ptrOnSymbolInPosition );
            free( lineForTrigonometryFunc );
            return newNode( OPERATOR, arrayWithMathInfo[ indexOfMathFunc ].mathOperation, NULL, trigNode );
        }
    }
    printf( "%c ", **ptrOnSymbolInPosition );
    free( lineForTrigonometryFunc );
    return getPrimaryExpression( ptrOnSymbolInPosition );

}

node_t* getPrimaryExpression( char** ptrOnSymbolInPosition ){
    assert( ptrOnSymbolInPosition );
    assert( *ptrOnSymbolInPosition );

    printf( "%c ", **ptrOnSymbolInPosition );
    if( **ptrOnSymbolInPosition == '(' ){
        ++(*ptrOnSymbolInPosition);

        node_t* nodeFromExpression = getExpression( ptrOnSymbolInPosition );

        if( **ptrOnSymbolInPosition == ')' ){
            ++(*ptrOnSymbolInPosition);
        }
        return nodeFromExpression;
    }
    else{
        return getNumber( ptrOnSymbolInPosition );
    }

}

node_t* getNumber( char** ptrOnSymbolInPosition ){
    assert( ptrOnSymbolInPosition );
    assert( *ptrOnSymbolInPosition );

    double value = 0;
    bool statusOfReadNumber = false;
    printf( "%c ", **ptrOnSymbolInPosition );
    while( '0' <= (**ptrOnSymbolInPosition) &&
                  (**ptrOnSymbolInPosition) <= '9' ){

        value = value * 10 + ( (**ptrOnSymbolInPosition) - '0' );
        ++(*ptrOnSymbolInPosition);
        statusOfReadNumber = true;
    }
    printf( "%c ", **ptrOnSymbolInPosition );
    if( statusOfReadNumber == false ){
        colorPrintf( NOMODE, RED, "\nError of getNumber:%s %s %d\n", __FILE__, __func__, __LINE__ );
        exit( 0 );
    }
    printf( "%c ", **ptrOnSymbolInPosition );
    return makeConstNode( value );
}
