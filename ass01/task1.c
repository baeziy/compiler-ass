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
#include <ctype.h>
bool isEmptyLine(const char*);
void refine(const char*, char*);

int main(int argc, char *argv[]){

// checking no of arguments
    if (argc != 2){
        perror("Invalid arguments\n");
        exit(1);
    }

// opening input file
    FILE *fpIn;
    fpIn = fopen(argv[1],"r");
    if (fpIn == NULL){
        perror("Can't open file");
        exit(1);
    }
// opening output file
    FILE *fpOut = fopen("out1.txt", "w");
    if (fpOut == NULL) {
        perror("Error creating output file");
        fclose(fpIn);
        exit(1);
    }
// creating char arrays to store each line
    char* lineIn = (char*) malloc(200);
    char* lineOut = (char*) malloc(200);

// getting file contents
    while(fgets(lineIn, 200, fpIn)){
        if(!isEmptyLine(lineIn)){
            refine(lineIn, lineOut);
            fputs(lineOut, fpOut);
        }
    }

    fclose(fpIn);
    fclose(fpOut);


    fpOut = fopen("out1.txt", "r");
    if (fpOut == NULL) {
        perror("Error creating output file");
        fclose(fpIn);
        exit(1);
    }

    printf("Output File contents:-\n");
    while (fgets(lineIn, 200, fpOut)) {
        fputs(lineIn, stdout);
    }

    fclose(fpOut);


    return 0;
}

bool isEmptyLine(const char* line){
    for(int i = 0; line[i] != '\0'; i++){
        if (line[i] != ' ' && line[i] != '\n')
            return false;
    }
    return true;
}

void refine(const char *input, char *output){

    // for(int i = 0; in[i] != '\0'; i++){

    // }
 bool inLineComment = false, Blockcomment = false, preprocessorDirective = false;
    int i = 0, j = 0;

    for (;input[i] != '\0';) {
        if (Blockcomment) {
            if (input[i] == '*' && input[i + 1] == '/') {
                Blockcomment = false;
                i += 2;
            } else {
                i++;
            }
        } else if (inLineComment) {
            if (input[i] == '\n') {
                inLineComment = false;
            }
            i++;
        }else if (preprocessorDirective) {
            if (input[i] == '\n') {
                preprocessorDirective = false;
            }
            i++;
        } 
        else {
            if (input[i] == '/' && input[i + 1] == '*') {
                Blockcomment = true;
                i += 2;
            } else if (input[i] == '/' && input[i + 1] == '/') {
                inLineComment = true;
                i += 2;
            } else if (input[i] == '#') {
                preprocessorDirective = true;
                i++;
            }
            else {
                if (input[i] == ';' && isspace((unsigned char)output[j - 1])) {
                    j--;
                }

                if ((!isspace((unsigned char)input[i]) && input[i] != '\n') || 
                (j > 0 && input[i] == '\n' && output[j - 1] != '\n') || 
                (j > 0 && isspace((unsigned char)input[i]) && !isspace((unsigned char)output[j - 1]))) {
                    output[j++] = input[i];
                }
                i++;
            }
        }
    }
    for(int i = 0; output[i]!= '\0';i++){
        if(output[i] == '\n' && isspace((unsigned char)output[i-1])){
            output[i-1] = '\n';
            output[i] = '\0';
        }
    }
    output[j] = '\0';
}