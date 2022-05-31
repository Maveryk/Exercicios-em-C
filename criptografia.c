
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef char arranjo[255];


int main(void){

  arranjo palavra, alfabeto, codifica;
  int i, j,indice;
  int test;
  
  scanf("%[^\n]", alfabeto);
    
  test = strlen(alfabeto)-1; //não sei pq no run codes o strlen da 27
  
  if(test != 26){
  	printf("ERRO - A chave deve possuir 26 caracteres \n");
    return 0;
  }

    for(i = 0; i < 26; i++){
	    for(j = i+1; j < 26; j++){
	        if(alfabeto[i] == alfabeto[j]){
	        	printf("ERRO - A chave nao pode conter caracteres repetidos\n");
    			return 0;
	        }
	    }
	   	if(alfabeto[i] > 47 && alfabeto[i] < 58){
	        printf("ERRO - A chave nao pode conter caracteres nao alfabeticos \n");
    		return 0;
		}
  }
  
  for(i = 0; i < 26; i++){
  	alfabeto[i] = toupper(alfabeto[i]);
  }
  
  

  scanf(" %[^\n]", palavra);
   
  
  for(i = 0; palavra[i] != '\0'; i++){
  	codifica[i] = toupper(palavra[i]);
  }
  
  for(i = 0; palavra[i] != '\0'; i++){
	  	indice = codifica[i] - 65;
	  	 
	  	if(palavra[i] >64 && palavra[i] < 91)
	    	palavra[i] = alfabeto[indice];
	     
	    if(palavra[i] >96 && palavra[i] < 123)
	    	palavra[i] = tolower(alfabeto[indice]);    
	}
  printf("Texto Cifrado: %s", palavra);
 
  return 0;
  
}
