#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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

    FILE *fpOut = fopen("out2.txt", "w");
    if (fpOut == NULL)
    {
        perror("Error creating output file");
        fclose(fpIn);
        exit(1);
    }

    char *buffer = (char *)malloc(20000);
    while (true)
    {
        char c = fgetc(fpIn);

        if (feof(fpIn))
            break;

        if (!(c == '\n'))
        {
            *(buffer++) = c;
            fputc(*(buffer-1), fpOut);
        }
    }
    *(buffer) = '$';
    fputc(*buffer, fpOut);


    fclose(fpIn);
    fclose(fpOut);

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