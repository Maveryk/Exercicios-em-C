#include <stdio.h>

void print_string(char* str, int a){

    if(str[a] != '\0'){
        printf ("%c", str[a]);
        a++;
        print_string(str, a);
    }
}

int main () {

    char str[256];
    
    scanf("%[^\n]", str);

    print_string(str, 0);

}