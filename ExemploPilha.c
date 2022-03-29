#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct celula* ptrCelula;

typedef struct celula {
    float elem;
    ptrCelula prox;
} TipoCelula;

typedef struct pilha {
    ptrCelula topo;
} TipoPilhaLE;

ptrCelula criarNovaCelula(int elem);
TipoPilhaLE* criarPilhaVazia();

float calcular(float operando1,float operando2, char simbolo);
float pop(TipoPilhaLE *s);
void push(TipoPilhaLE *s, float e);
float analisaExpressao(TipoPilhaLE* s,char* expr);

int main(){
    char x[51];
    TipoPilhaLE* Pilha = criarPilhaVazia();
    scanf("%s", x);

    printf("%s = %.0f", x, analisaExpressao(Pilha, x));

    return 0;
}


float analisaExpressao(TipoPilhaLE* s,char *expr){

 float operando1 = 0, operando2 = 0;
 char sim = expr[0];
 int i;
 for(i = 1; sim != '\0'; i++){
     if(isdigit(sim)){
         push(s, sim - '0');
     }else{
        operando2 = pop(s);
        operando1 = pop(s);
        push(s, calcular(operando1, operando2, sim));
     }
     sim = expr[i];
 }
 return pop(s);
}
TipoPilhaLE* criarPilhaVazia() {
    TipoPilhaLE* novaPilha = (TipoPilhaLE*) malloc(sizeof(TipoPilhaLE));

    if (novaPilha) {
        novaPilha->topo = NULL;
    }
    return novaPilha;
}
ptrCelula criarNovaCelula(int elem) {
    ptrCelula novaCelula = (ptrCelula) malloc(sizeof(TipoCelula));
    if (novaCelula) {
        novaCelula->elem = elem;
        novaCelula->prox = NULL;
    }
    return novaCelula;
}

float calcular(float operando1,float operando2, char simbolo){

    switch (simbolo){
        case '+':
            return (operando1 + operando2);
            break;
        case '-':
            return (operando1 - operando2);
            break;
        case '*':
            return (operando1 * operando2);
            break;
        case '/':
            return (operando1 / operando2);
            break;        
        default:
            return 0;
            break;
    }
}

void push(TipoPilhaLE *s, float e){
    ptrCelula novaCelula = criarNovaCelula(e);
    if (novaCelula) {
        novaCelula->prox = s->topo;
        s->topo = novaCelula;
    }
    return;
}    

float pop(TipoPilhaLE *s){
    float ret = 0;
    ptrCelula aux = NULL;
    
    if (s->topo != NULL) {
        ret = s->topo->elem;
        aux = s->topo;
        s->topo = aux->prox;
        free(aux);
    }

    return ret;
}