#include<stdio.h>
#include<string.h>
#include<math.h>
int main(){
    int b, lens;
    char x[3];
    char* bener = "Merupakan Bilangan Armstrong", *salah = "Bukan Merupakan Bilangan Armstrong";
    scanf("%s", &x);
    if(x[1]==NULL && x[2]==NULL){
        printf("%s", bener);
        return 0;
    } else {
        b = (x[0]-'0')*100 + (x[1]-'0')*10 + (x[2]-'0');
        if(b == pow(x[0]-'0', 3)+pow(x[1]-'0', 3)+pow(x[2]-'0', 3)) {
            printf("%s", bener);
            return 0;
        }
    }
    printf("%s", salah);
return 0;
}