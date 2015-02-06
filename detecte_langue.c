#include <stdlib.h>
#include <stdio.h>
#include "mot.h"
#include "lettre.h"

int main() {
    char c;
    tab_langue_mot res;
    char* w;
    int i;
    table_langue tab_proba;
    int faux, total;

    // 1ère partie : construction des tableaux de proba de l'alphabet, selon le corpus
    tab_proba = init_tab_lettre_langue();
    afficherTab(tab_proba);

    // 2ème partie : entrée des mots à tester
    do {
        printf("Voulez-vous : \n");
        printf("\t Detecter la langue d'un mot ? (l) \n");
        printf("\t Calculer la probabilité d'apparition d'un mot ? (a) \n");        
        printf("\t Quitter ce programme ? (q) \n");
        scanf("%c", &c);
        if (c == 'l') {
            printf("Saisir le mot :\n");
            scanf("%s", w);
            p_langue_mot(w, res);
            for (i=0; i<NB_LANGUES; i++) { // affichage de P(l/w)
//////                printf("\t P(%s / %s) = %f \n", nom_langue(i), w, res[i]);
            }
        } else if (c == 'a') {
            printf("Saisir le mot :\n");
            scanf("%s", w);
        	p_mot_langue(w, res);
            for (i=0; i<NB_LANGUES; i++) { // affichage de P(w/l)
//////                printf("\t P(%s / %s) = %f \n", w, nom_langue(i), res[i]);
            }
        }
        
    } while(c != 'q');

    return 0;
}
