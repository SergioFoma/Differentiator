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

double createTreeByRecursiveDescent( ){
    colorPrintf( NOMODE, YELLOW, "Enter the name of file, where i will find mathematical statement: " );

    char* nameOfFileForMathStatement = NULL;
    size_t sizeOfAllocationMemory = 0;
    ssize_t sizeOfLine = getlineWrapper( &nameOfFileForMathStatement, &sizeOfAllocationMemory, stdin );

    if( sizeOfLine == -1 ){
        return -1;
    }

    FILE* fileForMathStatement = fopen( nameOfFileForMathStatement, "r" );
    if( fileForMathStatement == NULL ){
        colorPrintf( NOMODE, RED, "\ncan not open file:%s %s %d\n", __FILE__, __func__, __LINE__ );
        free( nameOfFileForMathStatement );
        return -1;
    }

    bufferInformation dataBaseFromFile = {};
    errorCode statusOfReadFromFile = initBufferInformation( &dataBaseFromFile, fileForMathStatement, nameOfFileForMathStatement);
    if( statusOfReadFromFile != correct ){
        return -1;
    }

    char* ptrOnSymbolInPosition = dataBaseFromFile.buffer;
    double value = getGeneral( &ptrOnSymbolInPosition );

    free( nameOfFileForMathStatement );
    fclose( fileForMathStatement );
    destroyBufferInformation( &dataBaseFromFile );
    return value;
}

double getGeneral( char** ptrOnSymbolInPosition ){
    assert( ptrOnSymbolInPosition );
    assert( *ptrOnSymbolInPosition );

    double value = getExpression( ptrOnSymbolInPosition );

    if( **ptrOnSymbolInPosition != '$' ){
        colorPrintf( NOMODE, RED, "\nError of getGeneral:%s %s %d\n", __FILE__, __func__, __LINE__ );
        exit( 0 );
    }

    ++(*ptrOnSymbolInPosition);
    return value;
}

double getTerm( char** ptrOnSymbolInPosition ){
    assert( ptrOnSymbolInPosition );
    assert( *ptrOnSymbolInPosition );

    double value = getPrimaryExpression( ptrOnSymbolInPosition );

    while( **ptrOnSymbolInPosition == '*' || **ptrOnSymbolInPosition == '/' ){
        char operation = **ptrOnSymbolInPosition;
        ++(*ptrOnSymbolInPosition);

        double secondValue = getPrimaryExpression( ptrOnSymbolInPosition );

        if( operation == '*' ){
            value *= secondValue;
        }
        else if( operation == '/' && secondValue != 0 ){
            value /= secondValue;
        }
    }

    return value;
}

double getExpression( char** ptrOnSymbolInPosition ){
    assert( ptrOnSymbolInPosition );
    assert( *ptrOnSymbolInPosition );

    double value = getTerm( ptrOnSymbolInPosition );

    while( **ptrOnSymbolInPosition == '+' || **ptrOnSymbolInPosition == '-' ){
        char operation = **ptrOnSymbolInPosition;
        ++(*ptrOnSymbolInPosition);

        double secondValue = getTerm( ptrOnSymbolInPosition );

        if( operation == '+' ){
            value += secondValue;
        }
        else{
            value -= secondValue;
        }
    }

    return value;

}

double getPrimaryExpression( char** ptrOnSymbolInPosition ){
    assert( ptrOnSymbolInPosition );
    assert( *ptrOnSymbolInPosition );

    if( **ptrOnSymbolInPosition == '(' ){
        ++(*ptrOnSymbolInPosition);

        double value = getExpression( ptrOnSymbolInPosition );

        if( **ptrOnSymbolInPosition == ')' ){
            ++(*ptrOnSymbolInPosition);
        }
        return value;
    }
    else{
        return getNumber( ptrOnSymbolInPosition );
    }

}

double getNumber( char** ptrOnSymbolInPosition ){
    assert( ptrOnSymbolInPosition );
    assert( *ptrOnSymbolInPosition );

    double value = 0;
    bool statusOfReadNumber = false;

    while( '0' <= (**ptrOnSymbolInPosition) &&
                  (**ptrOnSymbolInPosition) <= '9' ){

        value = value * 10 + ( (**ptrOnSymbolInPosition) - '0' );
        ++(*ptrOnSymbolInPosition);
        statusOfReadNumber = true;
    }

    if( statusOfReadNumber == false ){
        colorPrintf( NOMODE, RED, "\nError of getNumber:%s %s %d\n", __FILE__, __func__, __LINE__ );
        exit( 0 );
    }

    return value;
}
