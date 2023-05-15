#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>
#define MAX_MACROS 50
#define MAX_MACRO_LEN 50
void stripOffComments(char *input_filename, char *output_filename);
void macroExpansion(char *input_filename, char *output_filename);
void includeHeaderFiles(char *input_filename, char *output_filename);
bool isEmptyLine(const char*);
void refine(const char*, char*);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Arugments not correct!");
        exit(0);
    }

    char *input_file = argv[1];

    stripOffComments(input_file, "out1.c");
    macroExpansion("out1.c", "out2.c");
    // includeHeaderFiles("out2.c", "final.c");

    // FILE *final = fopen("final.c", "r");
    // if (final == NULL) {
    //     perror("Error opening final.c");
    //     return 1;
    // }

    // char eachLine[2000];
    // while (fgets(eachLine, sizeof(eachLine), final)) {
    //     printf("%s", eachLine);
    // }

    // fclose(final);
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
    bool inLineComment = false, Blockcomment = false;
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
        } else {
            if (input[i] == '/' && input[i + 1] == '*') {
                Blockcomment = true;
                i += 2;
            } else if (input[i] == '/' && input[i + 1] == '/') {
                inLineComment = true;
                i += 2;
            } else {
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

void stripOffComments(char *input_filename, char *output_filename){
    FILE *fpIn;
    fpIn = fopen(input_filename,"r");
    if (fpIn == NULL){
        perror("Can't open file");
        exit(1);
    }
    FILE *fpOut = fopen(output_filename, "w");
    if (fpOut == NULL) {
        perror("Error creating output file");
        fclose(fpIn);
        exit(1);
    }
    char* lineIn = (char*) malloc(200);
    char* lineOut = (char*) malloc(200);

    while(fgets(lineIn, 200, fpIn)){
        if(!isEmptyLine(lineIn)){
            refine(lineIn, lineOut);
            fputs(lineOut, fpOut);
        }
    }

    fclose(fpIn);
    fclose(fpOut);
    free(lineIn);
    free(lineOut);
}



void macroExpansion(char *input_filename, char *output_filename) {
    char line[200], macros[MAX_MACROS][MAX_MACRO_LEN], replacements[MAX_MACROS][MAX_MACRO_LEN];
    int num_macros = 0;
    FILE *input_file, *output_file;

    // Open the input and output files
    input_file = fopen(input_filename, "r");
    output_file = fopen(output_filename, "w");

    if (!input_file || !output_file) {
        perror("Error opening file.");
        return;
    }

    // Read each line of the input file
    while (fgets(line, sizeof(line), input_file)) {
        // Check if the line starts with "#define"
        if (strncmp(line, "#define", 7) == 0) {
            // Parse the macro and its replacement from the line
            sscanf(line, "#define %s %s", macros[num_macros], replacements[num_macros]);
            num_macros++;
            continue;
        }

        // For each macro
        for (int i = 0; i < num_macros; i++) {
            char *macro_start;

            // While there are occurrences of the macro in the line
            while ((macro_start = strstr(line, macros[i]))) {
                // Temporary string for constructing the new line
                char temp[200] = "";

                // Copy part of line before macro to temp
                strncpy(temp, line, macro_start - line);
                temp[macro_start - line] = '\0';

                // Append replacement and part of line after macro
                strcat(temp, replacements[i]);
                strcat(temp, macro_start + strlen(macros[i]));

                // Copy the temp string back to line
                strcpy(line, temp);
            }
        }

        // Write the line to the output file
        fputs(line, output_file);
    }

    // Close the files
    fclose(input_file);
    fclose(output_file);
}


void includeHeaderFiles(char *input_filename, char *output_filename) {
    // Your implementation here
}
