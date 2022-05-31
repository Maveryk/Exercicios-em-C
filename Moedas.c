#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
int main () {
  double valor, resto;
  int qtd_100, qtd_50, qtd_20, qtd_10, qtd_5, qtd_2;
  int qtd_1, qtd_050, qtd_025, qtd_010, qtd_005;

  scanf("%lf", &valor);

  if(valor<0) valor = 0;

  qtd_100 = valor / 100;
  resto = fmod(valor, 100);

  qtd_50 = abs(resto / 50);
  resto = fmod(resto, 50);

  qtd_20 = abs(resto / 20);
  resto = fmod(resto, 20);

  qtd_10 = abs(resto / 10);
  resto = fmod(resto, 10);

  qtd_5 = abs(resto / 5);
  resto = fmod(resto, 5);

  qtd_2 = abs(resto / 2);
  resto = fmod(resto, 2);

  printf("NOTAS:\n");
  printf("%d nota(s) de R$ 100.00\n", qtd_100);
  printf("%d nota(s) de R$ 50.00\n", qtd_50);
  printf("%d nota(s) de R$ 20.00\n", qtd_20);
  printf("%d nota(s) de R$ 10.00\n", qtd_10);
  printf("%d nota(s) de R$ 5.00\n", qtd_5);
  printf("%d nota(s) de R$ 2.00\n", qtd_2);

  qtd_1 = abs(resto);
  resto = fmod(resto, 1);

  qtd_050 = abs(resto / 0.5);
  resto = fmod(resto, 0.5);

  qtd_025 = abs(resto / 0.25);
  resto = fmod(resto, 0.25);

  qtd_010 = abs(resto / 0.1);
  resto = fmod(resto, 0.1);

  qtd_005 = abs(resto / 0.05);
  resto = fmod(resto, 0.05);
  
 	printf("\n");
  
    printf("MOEDAS:\n");
    printf("%d moeda(s) de R$ 1.00\n", qtd_1);
    printf("%d moeda(s) de R$ 0.50\n", qtd_050);
    printf("%d moeda(s) de R$ 0.25\n", qtd_025);
    printf("%d moeda(s) de R$ 0.10\n", qtd_010);
    printf("%d moeda(s) de R$ 0.05\n", qtd_005);
    printf("%.0lf moeda(s) de R$ 0.01\n", resto*100);
    
  return 0;
}
