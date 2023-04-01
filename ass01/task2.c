/*
              DATA DICTIONARY
              COMP 451 Section X
              Spring 2023
              Assignment 1
              Group Members: Muhammad Mustafa Kamal Malik
                             Mahnoor
              Roll Number:   241610047
                             231450813
              Date of Submission: April 02, 2023
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{

// checking no of arguments
    if (argc != 2)
    {
        perror("Invalid arguments\n");
        exit(1);
    }
// opening input file
    FILE *fpIn;
    fpIn = fopen(argv[1], "r");
    if (fpIn == NULL)
    {
        perror("Can't open file");
        exit(1);
    }
// opening output file
    FILE *fpOut = fopen("out2.txt", "w");
    if (fpOut == NULL)
    {
        perror("Error creating output file");
        fclose(fpIn);
        exit(1);
    }
// creating buffer
    char *buffer = (char *)malloc(20000);
    while (true)
    {
        char c = fgetc(fpIn);

        if (feof(fpIn))
            break;

    // newline ignore, chars stored from buffer to file within a single loop
        if (!(c == '\n'))
        {
            *(buffer++) = c;
            fputc(*(buffer-1), fpOut);
        }
    }
    // putting a sentinel value both in the buffer and the file
    *(buffer) = '$';
    fputc(*buffer, fpOut);

    
    fclose(fpIn);
    fclose(fpOut);

// opening file and then printing the whole file
    fpOut = fopen("out2.txt", "r");
    if (fpOut == NULL)
    {
        perror("Error creating output file");
        fclose(fpIn);
        exit(1);
    }

    printf("Output File contents:-\n");
    while (true)
    {
        char c = fgetc(fpOut);

        if (feof(fpOut))
            break;

        fputc(c, stdout);
        
    }
    
    fclose(fpOut);
    return 0;
}