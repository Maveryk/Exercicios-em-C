#include <stdio.h>

int div(int a, int b){
    int c = 0;
    if( a >= b ) {
        c++;
        a = a - b;
        return div(a,b)+ c;
    } 
    return c;     
}

int main () {
 int a, b;

 scanf("%d", &a);
 scanf("%d", &b);

 if(b == 0){
     printf("divisor nao pode ser zero");
     return 0;
 }

 printf("%d", div(a,b));

}