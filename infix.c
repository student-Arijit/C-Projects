#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#define MAX 100

bool isCharacter(char);
bool isoperator(char);
bool ignorable(char);

int main(void) {
    char* input = malloc(sizeof(char) * MAX);
    
    return 0;
}

bool isCharacter(char c) {
    return (c > 64 && c < 91) || (c > 96 && c < 123);
}

bool isoperator(char c){
    return (c == '+' || c=='-'|| c=='*'|| c=='/' || c=='^');
}

bool ignorable(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}
