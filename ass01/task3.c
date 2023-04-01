#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool is_identifier_char(char c) {
    return isalnum(c) || c == '_';
}

void identify_lexemes(const char *buffer) {
    const char *bp = buffer;
    const char *fp = buffer;

    while (*fp != '$') {
        if (is_identifier_char(*fp)) {
            bp = fp;
            while (is_identifier_char(*fp)) {
                fp++;
            }
            printf("Lexeme: ");
            for (const char *i = bp; i < fp; i++) {
                putchar(*i);
            }
            putchar('\n');
        } else if (*fp == '\"') {
            bp = fp;
            fp++;
            while (*fp != '\"') {
                fp++;
            }
            fp++; // To skip the ending double quote
            printf("Lexeme: ");
            for (const char *i = bp; i < fp; i++) {
                putchar(*i);
            }
            putchar('\n');
        } else if (strchr("(){};=+-*/%%&|^<>!,", *fp) != NULL) {
            printf("Lexeme: %c\n", *fp);
            fp++;
        } else {
            fp++;
        }
    }
}

int main() {
    const char *buffer = "void main(){printf(\"Hello Class\");}$";
    
    identify_lexemes(buffer);
    return 0;
}
