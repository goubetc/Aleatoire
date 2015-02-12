#include <stdlib.h>
#include <stdio.h>
#include "mot.h"



void p_langue_mot(char* w, tab_langue_mot res, table_langue donnees) {
    
    tab_langue_mot prob = malloc(donnees.nb_langues*sizeof(double));
    
    int i, j;

    for(j=0; j<donnees.nb_langues; j++){
        res[j] = 0.0;
        prob[j] = 0.0;
    }
    i = 0;
    for(j=0; j<donnees.nb_langues; j++) res[j]=1;

    while (w[i] != 0) {
        char lettre = w[i];
		
        for(j=0; j<donnees.nb_langues; j++) {
            res[j]*=p_langue_lettre(lettre, j, donnees);                               
        }
        i++;
    }

}


void p_mot_langue(char* w, tab_langue_mot tab, table_langue donnees) {
    int i, j;
    for(j=0; j<donnees.nb_langues; j++) {
		i = 0;
		tab[j] = 1;
		while(w[i] != 0) {
			tab[j] *= p_lettre_langue(w[i], j, donnees);
			i++;
		}
	}
}
