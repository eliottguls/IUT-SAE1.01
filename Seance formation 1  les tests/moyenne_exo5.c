#include <stdio.h>
#include <stdlib.h>

int main(){
    int cpt, val, somme_moy;
    float moy;

    printf("Valeurs :");
    scanf("%d", &val);

    if (val==0){
        printf("");
    }
    else{
        while (val!=0){
            cpt = cpt+1;
            somme_moy=somme_moy+1;

            scanf("%d", &val);

        }
        
    }
}