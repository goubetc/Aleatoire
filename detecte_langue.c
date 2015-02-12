#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "mot.h"
#include "lettre.h"

int main(int argc, char** argv) {

	char c;
	char w[50];
	char w2[25];
	int i;
	double faux = 0.0;
	double total = 0.0; // pour calculer le taux d'erreur
	double max = 0.0;
	char lg[3], langue[3];
	double vrai = 0.0;
	table_langue tab_proba;
	tab_langue_mot res;
	switch (argc) {
		case 1 :
			printf("\n \n \n");
			printf("detecte_langue permet de prendre un mot en entrée et de déterminer la probabilité de se son language sachant le mot, ainsi que la probabilité du mot sachant le langage \n");
			printf("\n\n");
			printf("Il exite deux modes d'utilisation :\n");
			printf("\tManuel : executer le programme avec l'argument --man\n");
			printf("\t\"automatique\" : executer le programme avec en argument le nom d'un fichier ayant comme format : \n \t\t des lignes sous la forme <mot> <langue>\n\tle programme renvoie alors le nombre d'errueurs.\n\nIl est aussi possible de rajouter une langue en rajoutant dans le dossier \"Corpus\" un fichier au nom du language contenant un texte sans accents ni caractère n'appartenant pas a \"a\"..\"z\" ou \"A\"..\"Z\" dans la table ASCII. \n\n\n");
		break;
		
		case 2 :
			
			tab_proba = init_tab_lettre_langue();
			res = malloc(tab_proba.nb_langues * sizeof(double));
			
				
			if (strcmp(argv[1],"--man")==0){
				

				// 1ère partie : construction des tableaux de proba de l'alphabet, selon le corpus
					//afficherTab(tab_proba);

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
							for (i=0; i<tab_proba.nb_langues; i++) { 
								printf("\t P(%s | %s) = %.2e \n", nom_langue(i, tab_proba), w, res[i]);
							}
						} else { // calcul de P(w/l)
							p_mot_langue(w, res, tab_proba);
							for (i=0; i<tab_proba.nb_langues; i++) { 
								printf("\t P(%s | %s) = %.2e \n", w, nom_langue(i, tab_proba), res[i]);
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
			else {
				FILE *F1;
				char c;
				F1 = fopen(argv[1], "r");
				if (F1 == NULL) printf("erreur ouverture fichier %s\n", argv[1]);
				c = fscanf(F1,"%s",w2);
				
				
				
				while(c!=EOF){	
					total++;
					max = 0.0;
					p_langue_mot(w2, res, tab_proba);
					
					for (i=0; i<tab_proba.nb_langues; i++) { 
						if (res[i]>max) {
							max = res[i];
							strncpy(lg, nom_langue(i, tab_proba), 2);
							
						}
					}
					
					lg[0]=toupper(lg[0]);
					lg[1]=toupper(lg[1]);
					lg[2] = '\0';
					if (!strcmp(lg,"DU")){
						strcpy(lg,"GR");
					}
					
					c = fscanf(F1,"%s",langue);
					if (!strcmp(langue,lg))
						vrai++;
					
					c =fscanf(F1,"%s",w2);

				}
				fclose(F1);
				double taux = 100.0*(total-vrai)/total;
				printf("%.0f vrai résultats sur %.0f soit un taux d'erreur de : %.2f %% \n", vrai, total, taux);
			}
					 
			break;
		}
		
}
