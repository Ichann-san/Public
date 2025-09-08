#include<stdio.h>
#include<string.h>

int main(){
    int x, b;
    char *nama;
    scanf("%d", &x);
    if(x > 99){
        b = x/100;
        switch(b){
            case 1:
            nama = "se";
            break;

            case 2:
            nama = "dua ";
            break;

            case 3:
            nama = "tiga ";
            break;

            case 4:
            nama = "empat ";
            break;

            case 5:
            nama = "lima ";
            break;

            case 6:
            nama = "enam ";
            break;

            case 7:
            nama = "tujuh ";
            break;

            case 8:
            nama = "delapan ";
            break;

            case 9:
            nama = "sembilan ";
            break;
        }
        strcat(nama, "ratus");
    } else if(x>19){
        b /= 10;
        switch(b){
            case 2:
            strcat(nama, "dua");
            break;

            case 3:
            strcat(nama, "tiga");
            break;

            case 4:
            strcat(nama, "empat");
            break;

            case 5:
            strcat(nama, "lima");
            break;

            case 6:
            strcat(nama, "enam");
            break;

            case 7:
            strcat(nama, "tujuh");
            break;

            case 8:
            strcat(nama, "delapan");
            break;

            case 9:
            strcat(nama, "sembilan");
            break;
        }
        strcat(nama, " puluh");
    } else if(x>9){
        if(x == 10) {
            strcat(nama, "sepuluh");
            printf("%s", nama);
            return 0;
        }
        b /= 10;
        switch(b){

        }
        strcat(nama, "belas");
    } else {

    }
return 0;
}