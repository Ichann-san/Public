#include<stdio.h>
#include<stdbool.h>
#include<math.h>

int main(){
    int p1, p2, dice, damage;
    while(true){
        double prob;
        scanf("%d %d %d %d", &p1, &p2, &dice, &damage);
        if(p1==0 && p2==0 && dice==0 && damage==0) break;
        if(dice==3 && p1==p2){
            printf("50.0\n");
            continue;
        }
        double win1=(double)dice/6.0; double win2=1.0-win1;
        int hit1=(p1+damage-1)/damage; int hit2=(p2+damage-1)/damage;//hit biar mati, asu cok ada beginiannya
        if(fabs(win1-win2)<1e-9){
            prob=(double)hit1/(hit1+hit2);//adil cik
        } else {
            if(fabs((double)(p2/p1)-1.0)<1e-9){
                prob=(double)hit1/(hit1+hit2);//adil cik pro ny walau game ny ampas
            } else {
                prob=(double)((1.0-pow((p2/p1), hit1))/(1.0-pow((p2/p1), hit1+hit2)));//anjay markov chain
            }
        }
        printf("%.1f\n", prob*100.0);
    }
//markov chain kont*l cok asu cik
return 0;
}