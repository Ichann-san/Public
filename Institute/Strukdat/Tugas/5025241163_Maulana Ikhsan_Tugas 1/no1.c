#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
FILE *file;
struct ktp{
    char nik[16];
    char nama[50];
    char tempat_lahir[50];
    char tanggal_lahir[50];
    char jenis_kelamin[50];
    char alamat[50];
    char agama[50];
    char status[50];
    char pekerjaan[50];
    char kewarganegaraan[50];
};
struct ktp penduduk[100];
int index=0;
void menu();
void add_data();
void search_data();
void display_data();
void delete_data();

int main(){
menu();
return 0;
}

void menu(){
    int choice=0;
    printf("1. Add Data\n");
    printf("2. Search Data\n");
    printf("3. Display Data\n");
    printf("4. Delete Data\n");
    printf("5. Finish\n");
    do {
    printf("Input: "); scanf("%d", &choice);
    switch(choice){
        case 1:
            system("cls");
            add_data();
            break;
        case 2:
            system("cls");
            search_data();
            break;
        case 3:
            system("cls");
            display_data();
            break;
        case 4:
            system("cls");
            delete_data();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Input tidak valid\n");
            break;
        }
    } while(choice<1 || choice>5);

}

void add_data(){
    printf("NIK: "); scanf("%s", penduduk[index].nik);
    printf("Nama: "); scanf("%s", penduduk[index].nama);
    printf("Tempat Lahir: "); scanf("%s", penduduk[index].tempat_lahir);
    printf("Tanggal Lahir: "); scanf("%s", penduduk[index].tanggal_lahir);
    printf("Jenis Kelamin: "); scanf("%s", penduduk[index].jenis_kelamin);
    printf("Alamat: "); scanf("%s", penduduk[index].alamat);
    printf("Agama: "); scanf("%s", penduduk[index].agama);
    printf("Status: "); scanf("%s", penduduk[index].status);
    printf("Pekerjaan: "); scanf("%s", penduduk[index].pekerjaan);
    printf("Kewarganegaraan: "); scanf("%s", penduduk[index].kewarganegaraan);
    index++;
    system("pause");
    system("cls");
    menu();
}

void search_data(){
    char search[16];
    bool found=false;
    printf("Cari data berdasarkan NIK\n");
    printf("NIK: "); scanf("%s", search);
    for(int i=0; i<index; i++){
        if(strcmp(search, penduduk[i].nik)==0){
            found=true;
            printf("NIK: %s\n", penduduk[i].nik);
            printf("Nama: %s\n", penduduk[i].nama);
            printf("Tempat Lahir: %s\n", penduduk[i].tempat_lahir);
            printf("Tanggal Lahir: %s\n", penduduk[i].tanggal_lahir);
            printf("Jenis Kelamin: %s\n", penduduk[i].jenis_kelamin);
            printf("Alamat: %s\n", penduduk[i].alamat);
            printf("Agama: %s\n", penduduk[i].agama);
            printf("Status: %s\n", penduduk[i].status);
            printf("Pekerjaan: %s\n", penduduk[i].pekerjaan);
            printf("Kewarganegaraan: %s\n", penduduk[i].kewarganegaraan);
            break;
        }
    }
    if(!found) printf("Data tidak ditemukan\n");
    system("pause");
    system("cls");
    menu();
}

void display_data(){
    printf("No\tNIK\tNama\tTempat Lahir\tTanggal Lahir\tJenis Kelamin\tAlamat\tAgama\tStatus\tPekerjaan\tKewarganegaraan\n\n");
    for(int i=0; i<index; i++){
        printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", i+1, penduduk[i].nik, penduduk[i].nama, penduduk[i].tempat_lahir, penduduk[i].tanggal_lahir, penduduk[i].jenis_kelamin, penduduk[i].alamat, penduduk[i].agama, penduduk[i].status, penduduk[i].pekerjaan, penduduk[i].kewarganegaraan);
    }
    system("pause");
    system("cls");
    menu();
}

void delete_data(){
    char search[16];
    bool found=false;
    printf("Hapus data berdasarkan NIK\n");
    printf("NIK: "); scanf("%s", search);
    for(int i=0; i<index; i++){
        if(strcmp(search, penduduk[i].nik)==0){
            found=true;
            for(int j=i; j<index; j++){
                penduduk[j]=penduduk[j+1];
            }
            index--;
            break;
        }
    }
    if(!found) printf("Data tidak ditemukan\n");
    system("pause");
    system("cls");
    menu();
}