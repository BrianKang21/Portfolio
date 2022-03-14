/******************************************************************************
 * @file: latin_square_functions.c
 *
 * mkang88
 * MIN JAE KANG
 * 9078060952
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Brian Kang (mkang88@wisc.edu)
 * @modified: 11/13/2021
 *****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "latin_square_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
#define dbgprint_latin_square(n, LS) if (DEBUG) { Print_Latin_Square(n, LS); }

/******************************************************************************
 * Data Types and Structures
 *****************************************************************************/

// ADD ANY ADDITIONAL DATA TYPES OR STRUCTSvHERE 

/******************************************************************************
 * Globals
 *****************************************************************************/
extern void Print_Latin_Square(const size_t n, char **latin_square);
#define NUMSYMBOLS 94
/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 

/******************************************************************************
 * Verificaiton functions
 *****************************************************************************/

/* 
 * This function takes the name of the file containing the latin square
 * and reads in the data to the the latin_square parameter.  
 *
 * There are many approaches that will work to read in the latin square data.
 * In any approach you choose, you will need to do at least the following:
 *     1) open the file 
 *     2) read in the text from the file
 *     3) figure out the dimensions of the latin square (n)
 *     4) reserve memory for the latin_square. This requires 2 steps
 *         4a) reserve an array of pointers to the rows
 *         4b) reserve an array of characters for each row
 *     5) fill in the latin_square data structure 
 *     6) close the file
 *
 * @param filename The name of the file to read in
 * @param latin_square_in A pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 */
void Read_Latin_Square_File(const char *filename, 
                            char ***latin_square_in, 
                            size_t *n) {
    // Opening the file to read
    FILE *latin_square_file;
    char *firstLine;
    latin_square_file = fopen(filename, "r");
    
    //Need to find out the dimension of latin square
    //Create a random array to only hold first line and read till "/n" to find out dimension
    // copied from https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
    fseek(latin_square_file, 0, SEEK_END);
    int sizeofFile = ftell(latin_square_file);
    rewind(latin_square_file);

    //Create a array to store first line of file
    //use strlen to find length of file but -1 since we dont want to count "/n"
    firstLine = malloc(sizeofFile*sizeof(char));
    fgets(firstLine, sizeofFile, latin_square_file);
    *n = strlen(firstLine) - 1; 

    //Reserve memeory for the latin_square
    *latin_square_in = malloc((*n)*sizeof(char*));
    //Reserve memory for array of characters for each row
    for (int i = 0; i < *n; i++) {          
        *(*latin_square_in + i) = malloc((*n)*sizeof(char)); }
        

    //fill in the latin_square data structure
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
           *(*(*latin_square_in + i) + j) = *(firstLine + j); }
    
    //fgets until the last row
    fgets(firstLine,sizeofFile, latin_square_file);  }                         
    
    free(firstLine);
    fclose(latin_square_file);
    
}

/* 
 * This function checks to see that exactly n symbols are used and that 
 * each symbol is used exactly n times.
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
int Verify_Alphabet(const size_t n, char **latin_square) {
    if (latin_square == NULL) {
        printf("Verify_Alphabet - latin_square is NULL\n"); 
        return 0;
    }
    //All valid characters include all printable symbols hence there is a total of 94
    //So we can create an array of 94 spots, and increment them by 1 depending on what value is on the latin square
    //In the end, if it is a valid square, all the incrememented values should be the SAME 
    int *frequency;
    int valueofSymbol = 0;
    frequency = malloc(NUMSYMBOLS * sizeof(int));
        for (int i = 0; i < NUMSYMBOLS; i++) {
            *(frequency + i) = 0; }
            
    // ASCII CODE 33 is lowest (!) and 126 is highest (~)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // -33 because the lowest ASCII is 33, hence we want "!" to be on the first index of the frequency array
            valueofSymbol = (*(*(latin_square + i) + j)) - 33;
            *(frequency + valueofSymbol) = *(frequency + valueofSymbol) + 1; } }

    //Now we have to find out if the "n" character used in the latin square is thewas used exactly "n" times
    for (int i = 0; i < NUMSYMBOLS; i++) {
        if (!(*(frequency + i) == 0 || *(frequency + i) == n)) {
         free(frequency);   
         return 0; } } 
    //free memory 
    free(frequency);
    return 1;
}

/* 
 * This function verifies that no symbol is used twice in a row or column.
 * It prints an error message alerting the user which rows or columns have 
 * duplicate symbols. This means that you will have at most n row error prints
 * and n column error prints.
 * 
 * Note: Test all rows first then test all columns.
 * 
 * Error messages have been included for you. Do not change the format out the 
 * print statements, as our grading scripts will use exact string matching. You
 * change the variable passed as the formatting argument to printf.
 * 
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
 int Verify_Rows_and_Columns(const size_t n, char **latin_square){
    if (latin_square == NULL) {
        printf("Verify_Rows_and_Columns - latin_square is NULL\n"); 
        return 0;
    }
    //94 total characters that can be printable
    int duplicates = 0;   
    int row = 0;
    int col = 0;
    int error = 0;
    
    //Make a copy of the latin_square
    char **test = malloc(n*sizeof(char *));
    for (int i = 0; i < n; i++) {
        *(test + i) = malloc(n * sizeof(char)); }   
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(*(test + i) + j) = *(*(latin_square + i) + j); }} 
    
    //Compare all the rows values together with the latin_square and the copy
    //This ensures all combination of the row values
    //Parts copied from https://stackoverflow.com/questions/8199403/how-to-check-if-an-array-has-any-duplicates
    //Made some adjustments to fit my needs for the program 
    for (row = 0; row < n; row++) {
    duplicates = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (*(*(test + row) + i) == *(*(latin_square + row) + j) && duplicates == 0) { 
               printf("Error in row %d\n", row); 
               duplicates++; 
               error++; }}}}     

    
    //Do the same for the columns instead 
    for (col = 0; col < n; col++) {
     duplicates = 0;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (*(*(test + i) + col) == *(*(latin_square + j) + col) && duplicates == 0){ 
                    printf("Error in column %d\n", col); 
                    duplicates++; 
                    error++;}}}}


    if (error != 0) {
        for (int i = 0; i < n; i++) {
            free(*(test + i)); }

    free(test);

    return 0; }
    
    //free the copy of square
    for (int i = 0; i < n; i++) {
        free(*(test + i)); }
        
    free(test);

    return 1;
}

/* 
 * This function calls free to allow all memory used by the latin_square 
 * verification program to be reclaimed.
 *
 * Note: you will have n+1 calls to free
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 */ 
void Free_Memory(const size_t n, char **latin_square) {
    for (int i = 0; i < n; i++) {
        free(*(latin_square + i)); } 

    free(latin_square);
}


