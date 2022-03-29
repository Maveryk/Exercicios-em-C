#include <stdio.h>
#include <string.h>

typedef struct s {
    int top;
    char items[100];
} Stack;

int isEmpty(Stack *s);
int push(Stack *s, int elem);
int pop(Stack *s);
void printStack(Stack *s);
void stackInit(Stack* s);
void line_processing(Stack* s, char *line);

int main () {
    char x[256]; 
    scanf("%[^\n]", x);
    int i = strlen(x);
    if(i > 99){
        printf("A linha nao pode possuir mais de 100 caracteres.");
        return 1;
    }

    Stack s;
    stackInit(&s);
    line_processing(&s, x);
    printStack(&s);

    return 1;

}

void line_processing(Stack* s, char *line){
    int i;

     for (i = 0; line[i] != '\0'; i++){

         if(line[i] == '#'){
            s->top = pop(s);
         }else{
            push(s, line[i]);
         }
     }
     push(s, '\0');

}

void stackInit(Stack* s){
    s->top = -1;
}

int isEmpty(Stack *s){
    return (s->top == -1);
}

int push(Stack *s, int elem){ //adiciona
    if (s->top != 99){
        s->items[++s->top] = elem;
    }
    else{
        return -1;
    }
    return s->top;
}

int pop(Stack *s){ // retira
    int elem = -1;
    if (!isEmpty(s))
    {
        elem += s->top;
        s->items[s->top--] = ' ';   
    }
    return elem;
}
    

void printStack(Stack *s){ //printa
    if (isEmpty(s)){
        printf("Pilha vazia!\n");
        return;
    }
    else{
        int i;
        for (i = 0; i < s->top; i++){
            printf("%c", s->items[i]);
        }
    }
}
