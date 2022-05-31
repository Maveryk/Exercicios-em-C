#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct {
 int valor;
 int fabs;
 float frel;
}Freq;

void calc_frequencias(int *vet, int tam, Freq *vetFreq){
	int i, j;
	
	for(i=0;i < tam;i++){
		vetFreq[i].valor = vet[i];
	}
	    
    for(i=0;i < tam;i++){
		vetFreq[i].fabs = 0;
		vetFreq[i].frel = 0;
	}

	for( i=0; i<tam; i++ ){
    	for( j=i; j<tam; j++ ){
    		if(vetFreq[i].valor == vetFreq[j].valor){
    			vetFreq[i].fabs += 1;
			}
    	}
    }
    
	for( i=0; i<tam; i++ ){
    	for( j=i; j<tam; j++ ){
    		if(vetFreq[i].valor == vetFreq[j].valor)
    			if(vetFreq[i].fabs != vetFreq[j].fabs)
					vetFreq[j].fabs =  vetFreq[i].fabs;
		}
    }

	for( i=0; i<tam; i++ ){
		vetFreq[i].frel = ((float)vetFreq[i].fabs / tam) ;
    }
  
}

int main(int argc, char* argv[]){
	
	if(argc<2 || argc>3){
		return 0;
	}
		
    int n = atoi(argv[1]);
    int x = atoi(argv[2]);
	int vet[n];
	int i;
	Freq freq[n];
	
	if(!isdigit(*argv[1]) || !isdigit(*argv[2])){
		printf("ERRO - não e digito\n");
		return 1;
	}
	
	if(n<1 || n>256){
		printf("ERRO - VALOR DEVE ESTAR ENTRE 1 E 256 ");
		return 2;
	}

	if(x<1){
		printf("ERRO - VALOR DEVE SER MAIOR QUE ZERO ");
		return 3;
	}
	
	time_t t;
	srand((unsigned) time(&t));
	for(i=0;i < n;i++){
		vet[i] = rand() % x;
	}
	
	for(i=0;i < n;i++){	
		freq[i].fabs = 0;
	}
	
	calc_frequencias(vet, n, freq);

	for(i=0;i < n;i++){	
		printf("Valor: %d\n", freq[i].valor);
		printf("Frequencia absoluta: %d\n", freq[i].fabs);
		printf("Frequencia relativa: %.2f\n\n", freq[i].frel);
	}
	
	return 0;
}
