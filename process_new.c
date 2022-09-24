#include "record_struct.h"
#include "process.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct uniqueRecordStruct {
    int sizeOfVal;
    char* uniqueValue;
    char** field;
    char*** values;
};

extern struct uniqueRecordStruct* uniqueRecordArray;

int row = 0;
int col = 0;

int main() {

    char *filename = "bookInfo1.txt";
    char *column = "Stock";
    char *uniqueValue = "In stock";

    char ***recordArray = readFileByUniqueValue(filename, column, uniqueValue, &row, &col);

    int count = 0;
    // char*** uniqueRecordArray_ = getByUniqueValue(recordArray, column, "Out of stock", row, col, &count);


    // char uniqueValues[2][20] = {"In stock", "Out of stock"};
    // createProcesses(2, uniqueValues, recordArray, column, row, col);
}

char ***readFileByUniqueValue(char* filename, char* column, char* uniqueValue, int* row_, int* col_) {

    int nRows = 705;
    int nCols = 5;
    int nValues = 300;

    if (strcmp(filename, "amazonBestsellers.txt") == 0) {
        nRows = 555;
        nCols = 6;
    }

    char*** recordArray = (char***)malloc(nRows * sizeof(char**));

    for (int i = 0; i < nRows; i++) {
        recordArray[i] = (char**)malloc(nCols * sizeof(char*));

        for (int j = 0; j < nCols; j++) {
            recordArray[i][j] = (char*)malloc(nValues * sizeof(char));
        }
    }


    FILE *inFile = fopen(filename, "r");
    if (!inFile) {
        perror("fopen for reading");
        exit(EXIT_FAILURE);
    }

    char *line = (char*)malloc(sizeof(char));
    int row = 0;
    int col = 0;

    int columnIndex = 0;

    while (fscanf(inFile, "%[^\n] ", line) != EOF) {

        char *pt = strtok(line, ",");
        
        col = 0;

        int i = 0;
        while (pt != NULL) {

            if (row == 0 && strcmp(pt, column) == 0) {
                columnIndex = i;
            }

            
            if (columnIndex != i) {
                // printf("columnIndex = %d, col = %d, column = %s, uniqueValue = %s, pt = %s\n", columnIndex, cols, column, uniqueValue, pt);
                
                // for (int k = 0; k < strlen(pt); k++) {
                //     recordArray[row][col][k] = pt[k];
                // }

                // printf("recordArray[%d][%d] = %s\n", row, col, recordArray[row][col]);
                printf("recordArray[%d][%d] = %s\n", row, col, pt);
                col++;
            }

            
            pt = strtok (NULL, ",");
            i++;
        }

        row++;
    }

    // fclose(inFile);

    *row_ = row;
    *col_ = col;
    return recordArray;

}

/*
char*** getRecordsByUniqueValue(char* filename, char* column, char* uniqueValue, int *row_, int *col_) {
    int count = 0;
    if (recordArray == NULL) {
        recordArray = readFile(filename, column, &row, &col);
    }

    char*** recordsByUniqueValue = getByUniqueValue(recordArray, column, uniqueValue, row, col, &count);
    *row_ = count;
    *col_ = col-1;

    return recordsByUniqueValue;
}

*/