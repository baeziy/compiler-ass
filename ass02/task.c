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
void refine(const char*, char*, bool*);

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
void refine(const char *input, char *output, bool *block_comment){
    bool inLineComment = false;
    int i = 0, j = 0;

    for (;input[i] != '\0';) {
        if (*block_comment) {
            if (input[i] == '*' && input[i + 1] == '/') {
                *block_comment = false;
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
                *block_comment = true;
                i += 2;
            } else if (input[i] == '/' && input[i + 1] == '/') {
                inLineComment = true;
                i += 2;
            } else {
                output[j++] = input[i];
                i++;
            }
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
    bool block_comment = false;

    while(fgets(lineIn, 200, fpIn)){
        refine(lineIn, lineOut, &block_comment);
        if(!isEmptyLine(lineOut)){
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
    FILE *input_file, *output_file;
    char line[200];

    // Open the input and output files
    input_file = fopen(input_filename, "r");
    output_file = fopen(output_filename, "w");

    if (!input_file || !output_file) {
        perror("Error opening file.");
        return;
    }

    // Read each line of the input file
    while (fgets(line, sizeof(line), input_file)) {
        // Check if the line is an include statement
        if (strncmp(line, "#include", 8) == 0) {
            char header_filename[50];
            FILE *header_file;
            char header_line[200];

            // Parse the header filename from the include statement
            sscanf(line, "#include <%[^>]> ", header_filename);

            // Map the standard names to the custom names
            if (strcmp(header_filename, "stdio.h") == 0) {
                strcpy(header_filename, "pa2_stdio.h");
            } else if (strcmp(header_filename, "stdlib.h") == 0) {
                strcpy(header_filename, "pa2_stdlib.h");
            } else if (strcmp(header_filename, "string.h") == 0) {
                strcpy(header_filename, "pa2_string.h");
            }

            // Open the header file
            header_file = fopen(header_filename, "r");

            if (!header_file) {
                perror("Error opening header file.");
                continue;
            }

            // Read each line of the header file and write it to the output file
            while (fgets(header_line, sizeof(header_line), header_file)) {
                fputs(header_line, output_file);
            }

            // Close the header file
            fclose(header_file);
        } else {
            // Write the line to the output file
            fputs(line, output_file);
        }
    }

    // Close the files
    fclose(input_file);
    fclose(output_file);
}
