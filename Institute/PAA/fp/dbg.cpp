#include <cstdio>
#include <cstring>
typedef unsigned __int128 u128;
int main(){
    char input[32];
    scanf("%s",input);
    int m=(int)strlen(input);
    printf("raw input bytes: ");
    for(int i=0;i<m;++i) printf("%02X ",(unsigned char)input[i]);
    printf("\n");
    printf("input string: [%s]\n",input);
    return 0;
}
