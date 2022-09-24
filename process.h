#ifndef PROCESS_DOT_H
#define PROCESS_DOT_H

struct recordStruct* readFile(char* filename, char* column, int* row, int* col);

char*** getByUniqueValue(struct recordStruct *recordArray, char* column, char* uniqueValue, int row, int col, int *count);

char*** getRecordsByUniqueValue(char* filename, char* column, char* uniqueValue, int *row_, int *col_);

#endif