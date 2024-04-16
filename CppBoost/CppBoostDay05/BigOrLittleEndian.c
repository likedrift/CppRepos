#include <stdio.h>

int main(){

    short i = 0x1234;
    char *a = (char *)&i;

    printf("%p\n", a);
    printf("%x\n", *a);

    printf("%p\n", a+1);
    printf("%x\n", *(a+1));

    return 0;
}