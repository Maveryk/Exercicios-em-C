#include <stdio.h>

int mod( int a, int b){
    if(a >= b){
        a = a - b;
        mod(a,b);
    }else{
        return a;
    }
    return 0;

}

int main () {
 int a, b;

 scanf("%d", &a);
 scanf("%d", &b);

 if(b == 0){
     printf("divisor nao pode ser zero");
     return 0;
 }

 printf("%d", mod(a,b));

}