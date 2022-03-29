#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Mov{
    int tipo;
    int idClienteDest;
    float valor;
    struct Mov* prox;
}Mov;

typedef struct Conta{
    int numero;
    float saldo;
    float saldoIni;
    struct Mov* mov;
}Conta;

typedef struct Cliente{
    int id;
    struct Conta* conta;
    struct Cliente* prox;
}Cliente;

typedef struct {
    char nome[9];
    struct Cliente* cliente;
}Banco;


FILE* openFile(char *path, char *mode) {
    return fopen(path, mode);
}

void readFile(FILE *ptr, Banco *banco);
Banco* criarBanco();
Cliente* criarNovoCliente(int idCliente, int numConta, float saldo);
Cliente* buscarCliente(Banco *b, int idCliente);
void adicionarCliente(Banco *b, Cliente *c);
Mov* criarNovaMovimentacao(short int tipo, float valor, int idClienteDest);
void realizarDeposito(Cliente *c, Mov* dep);
float realizarSaque(Cliente *c, Mov* saque);
void realizarTransferencia(Cliente *clienteOrig, Cliente *clienteDest, float valor);
void mostrarClientes(Banco *b);

int main(/*int argc, char *argv[]*/){
    char path[10];
    char *mode = "r";
    FILE *filePtr = NULL;
    Banco *bomBanco = NULL;

    scanf("%s", path);
    filePtr = openFile(path, mode);
    
    if (filePtr) {
        
        bomBanco = criarBanco();
        
        readFile(filePtr, bomBanco);
        fclose(filePtr);
        
    } else {
        printf("Falha ao tentar abrir o arquivo\n");
        exit(1);
    }
    mostrarClientes(bomBanco);
    return 0;
}

void readFile(FILE *ptr, Banco *banco){
    char c1[4], c3[8];
    int c2;
    int tipoMov, idCliente, idClienteOrig, idClienteDest, numConta;
    float c4, valor;

    // Iterando nas linhas do arquivo
    while (fscanf(ptr, "%s\t%d\t%s\t%f\n", c1, &c2, c3, &c4) != EOF) {
        valor = c4;

        if (strcmp("add", c1) == 0) { //adicionar cliente
            idCliente = c2;
            numConta = atoi(c3);
            adicionarCliente(banco, criarNovoCliente(idCliente, numConta, valor));
        } 
        else if (strcmp("mov", c1) == 0) { //realizar movimentacoes
            tipoMov = c2;
            switch(c2) {

                case 0: // deposito
                    idCliente = atoi(c3);
                    realizarDeposito(buscarCliente(banco, idCliente), criarNovaMovimentacao(tipoMov, valor, 0));
                break;

                case 1: // saque
                    idCliente = atoi(c3);
                    Cliente *cliente = buscarCliente(banco, idCliente);
                    cliente->conta->saldo -= realizarSaque(cliente, criarNovaMovimentacao(tipoMov, valor, 0));
                break;

                case 2: // transferencia
                    idClienteOrig = atoi(strtok(c3, "-"));
                    idClienteDest = atoi(strtok(NULL, "-"));
                    realizarTransferencia(buscarCliente(banco, idClienteOrig), buscarCliente(banco, idClienteDest), valor);
                break;
                default:
                    printf("ERRO - movimentacao desconhecida.\n");
                    fclose(ptr);
                    exit(1);
                break;
            }
        }
    }
}


Cliente* buscarCliente(Banco *b, int idCliente){
    Cliente* aux;
    aux = b->cliente;
    while(aux->prox != NULL && aux->id !=  idCliente){
        aux = aux->prox;
    }//colocar a verificação para cliente nulo
    if(aux->id != idCliente) aux = NULL;
    return aux;
}
Banco* criarBanco(){
    Banco* banco;
    banco = (Banco*) malloc(sizeof(Banco));
    Cliente* cliente = (Cliente*) malloc(sizeof(Cliente));
    cliente->id = 0;
    *banco->nome = 'b';
    banco->cliente = cliente;
    return banco;
}
Cliente* criarNovoCliente(int idCliente, int numConta, float saldo){
    Cliente* c = (Cliente*) malloc(sizeof(Cliente));
    Conta* conta = (Conta*) malloc(sizeof(Conta));
    conta->numero = numConta;
    conta->saldo = saldo;
    conta->saldoIni = saldo;
    c->id = idCliente;
    c->conta = conta;
    c->prox = NULL;


    conta->mov = (Mov*) malloc(sizeof(Mov));
    conta->mov->tipo = 5;
    return c;
}
void adicionarCliente(Banco *b, Cliente *c){
    Cliente* aux;
    Cliente* aux2 = NULL;
    if(b->cliente->id == 0) {
        b->cliente = c;
        return;
    }    
    aux = b->cliente;
    if (c->id < aux->id){
        while(aux != NULL){       
            if(c->id < aux->id){
                if(aux2 == NULL){
                    c->prox = aux;
                    b->cliente = c;
                    return;
                }
                c->prox = aux;
                aux2->prox = c;            
            }
            if (c->id < aux->prox->id){
                c->prox = aux->prox;
                aux->prox = c;
                return;
            }
            aux2 = aux;
            aux = aux->prox;
        }
    }
    while(aux->prox != NULL){       
        if(c->id < aux->id){
            if(aux2 == NULL){
                c->prox = aux;
                b->cliente = c;
                return;
            }
            c->prox = aux;
            aux2->prox = c;            
        }    

        if (c->id < aux->prox->id){
            c->prox = aux->prox;
            aux->prox = c;
            return;
        }
        aux2 = aux;
        aux = aux->prox;       
    }
    aux->prox = c;
}
Mov* criarNovaMovimentacao(short int tipo, float valor, int idClienteDest){
    Mov* mov = (Mov*) malloc(sizeof(Mov));
    mov->tipo = tipo;
    mov->idClienteDest = idClienteDest;
    mov->valor = valor;
    mov->prox = NULL;
    return mov;
}
void realizarDeposito(Cliente *c, Mov* dep){
    Conta* conta;
    conta = c->conta;
    Mov* aux;
    if (conta->mov->tipo == 5){
        conta->mov = dep;
        c->conta->saldo += dep->valor;
        return;
    }    
    aux = conta->mov;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = dep;
    c->conta->saldo += dep->valor;
}
float realizarSaque(Cliente *c, Mov* saque){
    Conta* conta;
    conta = c->conta;
    Mov* aux;
    if (conta->mov->tipo == 5){
        conta->mov = saque;
        return saque->valor;
    }   
    aux = conta->mov;
    while(aux->prox != NULL ){
        aux = aux->prox;
    }
    aux->prox = saque;
    return saque->valor;
}
void realizarTransferencia(Cliente *clienteOrig, Cliente *clienteDest, float valor){
    Mov* f = criarNovaMovimentacao(2, valor, clienteDest->id);
    Mov* f2 = criarNovaMovimentacao(2, valor, 0);
    
    //refatorar usar as funções de saque é deposito para terminar a transferencia
    clienteOrig->conta->saldo -= realizarSaque(clienteOrig,f);
    realizarDeposito(clienteDest, f2);
    //clienteDest->conta->saldo += valor;//2
    /*
    if (clienteOrig->conta->mov == NULL){
        clienteOrig->conta->mov = f;
        return;
    }  
    if (clienteDest->conta->mov == NULL){
        clienteDest->conta->mov = f2;
        return;
    }  

    aux = clienteOrig->conta->mov;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux2 = clienteDest->conta->mov;
    while(aux2->prox != NULL){
        aux2 = aux2->prox;
    }

    aux->prox = f;
    aux2->prox = f2;*/

    //clienteOrig->conta->saldo -= valor;
    //clienteDest->conta->saldo += valor;


}
void mostrarClientes(Banco *b){
    Cliente* aux;
    aux = b->cliente;
    Mov* auxM;
    Conta* conta;
    while(aux != NULL){
        //codigo para mostar os valores
        conta = aux->conta;
        printf("=====================================================\n");
        printf("Id. Cliente  :    %d\n", aux->id);
        printf("Numero Conta :    %d\n", conta->numero);
        printf("Saldo inicial:    %.2f\n", conta->saldoIni);
        printf("------------------- Movimentacoes -------------------\n");

        auxM = aux->conta->mov;
        
        do{

            if(auxM->tipo == 5){
                printf("Sem movimentacoes\n");
            }else if(auxM != NULL){
                if (auxM->tipo == 0){//Deposito
                    printf("Tipo: Deposito | Valor: %.2f\n", auxM->valor);
                }
                else if (auxM->tipo == 1){//Saque
                    printf("Tipo: Saque    | Valor: -%.2f\n", auxM->valor);
                }
                else if (auxM->tipo == 2){//transferencia
                    if(auxM->idClienteDest != 0)
                        printf("Tipo: Transf.  | Valor: -%.2f ===> Destinatario: %d\n", auxM->valor, auxM->idClienteDest);
                    else
                    printf("Tipo: Transf.  | Valor: %.2f\n", auxM->valor);
                }
            } 
            auxM = auxM->prox;
        }while(auxM != NULL);
        printf("\n");
        printf("Saldo Final: %.2f\n", aux->conta->saldo);
        aux = aux->prox;
    }
    printf("=====================================================\n");
}
