#include <stdio.h>

int divisores(int a, int b){
    

    if(b<=a){
        if(a%b == 0){
            printf("%d\n", b);
        }
        b++;
        return divisores(a,b);
    }
    return b;
}

int main () {
 int a;
 scanf("%d", &a);
 divisores(a, 1);
}