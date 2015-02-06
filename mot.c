#include <stdlib.h>
#include <stdio.h>
#include "mot.h"



void p_langue_mot(char* w, tab_langue_mot res, table_langue donnees) {
    tab_langue_mot prob = {0.0};
    int i, j;
    for(j=0; j<NB_LANGUES; j++) res[j] = 0.0;
    i = 0;

    while (w[i] != 0) {
        char lettre = w[i];
		prob[j] = p_langue_lettre(lettre, j, donnees);
        for(j=0; j<NB_LANGUES; j++) {
            if (res[j]<prob[j]) res[j] = prob[j]; //  on garde la prob maximale pour chaque lettre
        }
        i++;
    }
}


void p_mot_langue(char* w, tab_langue_mot tab, table_langue donnees) {
    int i, j;
    for(j=0; j<NB_LANGUES; j++) {
		i = 0;
		tab[j] = 1;
		while(w[i] != 0) {
			tab[j] *= p_lettre_langue(w[i], j, donnees);
			i++;
		}
	}
}
