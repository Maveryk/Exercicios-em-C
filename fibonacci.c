#include <stdio.h>

unsigned int fibonacci(unsigned int n){
 unsigned int a=0,b=1,c,count;
 count=1;

 while(count<n) {
    c=a+b;
    a=b;
    b=c;
    count++;
 }
 return c;
}

int main () {
    int n;

    scanf("%d", &n);
    if(n>1){
        printf("%d", fibonacci(n));
    }
    else if (n<=1){
        printf("%d", n);
    }

}