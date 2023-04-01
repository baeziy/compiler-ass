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
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool isIDorKey(char);
void lexemesMaker(const char *);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        perror("Invalid arguments\n");
        exit(1);
    }

    FILE *fpIn;
    fpIn = fopen(argv[1], "r");
    if (fpIn == NULL)
    {
        perror("Can't open file");
        exit(1);
    }

    char *buffer = (char *)malloc(20000);
    

    int i = 0;
    while (true)
    {
        char c = fgetc(fpIn);

        if (feof(fpIn))
            break;

        if (!(c == '\n'))
        {
            buffer[i++] = c;
        }
    }

    fclose(fpIn);
    lexemesMaker(buffer);


    return 0;
}
void lexemesMaker(const char *buffer)
{
    const char *bp = buffer;
    const char *fp = buffer;

    while (*fp != '$')
    {
        // for different operators (++, <=, !=, etc.)
        if (*fp == '=' && *(fp + 1) == '=') {
            printf("Lexeme: ==\n");
            fp += 2;
            bp += 2;
        } else if (*fp == '<' && *(fp + 1) == '=') {
            printf("Lexeme: <=\n");
            fp += 2;
            bp += 2;
        }else if (*fp == '+' && *(fp + 1) == '+') {
            printf("Lexeme: ++\n");
            fp += 2;
            bp += 2;
        }else if (*fp == '-' && *(fp + 1) == '-') {
            printf("Lexeme: <=\n");
            fp += 2;
            bp += 2;
        }else if (*fp == '>' && *(fp + 1) == '=') {
            printf("Lexeme: >=\n");
            fp += 2;
            bp += 2;
        } else if (*fp == '!' && *(fp + 1) == '=') {
            printf("Lexeme: !=\n");
            fp += 2;
            bp += 2;
        } else if (*fp == '&' && *(fp + 1) == '&') {
            printf("Lexeme: &&\n");
            fp += 2;
            bp += 2;
        } else if (*fp == '|' && *(fp + 1) == '|') {
            printf("Lexeme: ||\n");
            fp += 2;
            bp += 2;
        }
        // if any other char is found (seperate lexeme)
        else if (strchr("=+-*{};/%%^()<>!,&|", *fp) != NULL)
        {
            printf("Lexeme: %c\n", *fp);
            fp++;
            bp++;
        }
        
        // strings are to be considered as a single lexeme.
        else if (*fp == '\"')
        {
            fp++;
            while (*fp != '\"')
                fp++;
            fp++;
            bp++;

            printf("Lexeme: ");
            for (; bp < fp;)
                fputc(*bp++, stdout);
            fputc('\n', stdout);
        }

        // identifiers or keywords
        else if (isIDorKey(*fp))
        {
            while (isIDorKey(*(fp++)));
            fp--;
            printf("Lexeme: ");
            for (; bp < fp;)
                fputc(*bp++, stdout);
            fputc('\n', stdout);
        }
        // other chars if any
        else
        {
            fp++;
            bp++;
        }
    }
}

// function checking if a char is an identifier or a part of any keyword
bool isIDorKey(char c)
{
    return isalnum(c) || c == '_';
}