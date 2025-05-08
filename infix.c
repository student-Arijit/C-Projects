#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#define MAX 100

typedef struct node {
    char data;
    struct node* next;
}node;

typedef struct {
    node* top;
} stack;

bool isCharacter(char);
bool isoperator(char);
bool ignorable(char);
void init(stack*);
bool isEmptyStack(stack*);
void push(stack*, char);
void pop(stack*);
void display(stack*);

/*main*/

int main(void) {
    char* input = (char*)malloc(sizeof(char) * MAX);
    
    return 0;
}

/*funtions*/

bool isCharacter(char c) {
    return (c > 64 && c < 91) || (c > 96 && c < 123);
}

bool isoperator(char c){
    return (c == '+' || c=='-'|| c=='*'|| c=='/' || c=='^');
}

bool ignorable(char c) {
    return c == ' ' || c == '\t';
}

void init(stack* s) {
    s->top = NULL;
}

bool isEmptyStack(stack* s) {
    return s->top == NULL;
}

void push(stack* s, char c) {
    node* newNode = (node*)malloc(sizeof(node));

    newNode->data = c;
    newNode->next = s->top;
    s->top = newNode;
}

void pop(stack* s) {
    if (isEmptyStack(s)) {
        printf("Empty Stack");
    }

    node* temp = s->top;
    s->top = temp->next;
    free(temp);
}

void display(stack* s) {
    if(isEmpty(s)) {
        printf("empty");
        return;
    }
    node* temp = s->top;
    while(temp) {
        printf("%d\n", temp ->data);
        temp = temp->next;
    }
}
