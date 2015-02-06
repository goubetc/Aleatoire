#include <stdlib.h>
#include <stdio.h>
#include "mot.h"
#include "lettre.h"

int main() {
    char c;
    tab_langue_mot res;
    char w[50];
    int i;
    table_langue tab_proba;
    double faux = 0.0;
    double total = 0.0; // pour calculer le taux d'erreur

    // 1ère partie : construction des tableaux de proba de l'alphabet, selon le corpus
    tab_proba = init_tab_lettre_langue();
    afficherTab(tab_proba);

    // 2ème partie : entrée des mots à tester
    while(1) {
        printf("Voulez-vous : \n");
        printf("\t Detecter la langue d'un mot ? (l) \n");
        printf("\t Calculer la probabilité d'apparition d'un mot ? (a) \n");        
        printf("\t Quitter ce programme ? (q) \n");
        scanf("%c", &c);
        if (c == 'q') { // Quitter
        	if (total != 0) printf("Taux d'erreur : %f\n", 1.0-(faux/total));
		    return 0;
		} else if (c == 'l' || c == 'a') { // Appels de fonctions
			total++;
	        printf("Saisir le mot :\n");
	        scanf("%s", w);
	        if (c == 'l') { // calcul de P(l/w)
	        	p_langue_mot(w, res, tab_proba);
		        for (i=0; i<NB_LANGUES; i++) { 
	//////                printf("\t P(%s / %s) = %f \n", nom_langue(i), w, res[i]);
		        }
	        } else { // calcul de P(w/l)
	        	p_mot_langue(w, res, tab_proba);
		        for (i=0; i<NB_LANGUES; i++) { 
	//////                printf("\t P(%s / %s) = %f \n", w, nom_langue(i), res[i]);
		        }
	        }
			scanf("%c", &c); // pour éviter le \n
	        printf("Diriez-vous que ces résultats sont faux ? (o/n)");
	        scanf("%c", &c); 
	        if (c == 'o') faux++;
		} else {
			printf("%c n'est pas disponible\n", c);
		}
		scanf("%c", &c); // pour éviter le \n
    }

}
