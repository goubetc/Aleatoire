#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include "lettre.h"

/* Traitement du corpus */

int compterFichier(DIR* dir)
{
    int nbr = 0;
    struct dirent* ent = NULL;
	ent = readdir(dir);
    while ((ent) != NULL)
    {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) /*  Et n'est pas .. non plus */
        	nbr++; /* Alors on incrémente le compteur */
        	ent = readdir(dir);
    }
	rewinddir(dir) ;
    return nbr;
}

table_langue initTab(DIR *rep){
		
	/* on initialise le tableau à la bonne taille */
	
	int nb_fichiers = compterFichier(rep);
	
	int i,j;
	table_langue tableL;
	double **tab, **tab2;
	tab = malloc(26 * sizeof(*tab));
	if (tab)
	{
	  for (i = 0; i < 26 ; i++)
	  {
		tab[i] = malloc(sizeof (*(tab[i])) * nb_fichiers);
	  }
	}
	
	/* on effectue le +1 sur tout le tableau */
	for (i= 0;i<26 ; i++){
		for(j=0; j<nb_fichiers; j++) {
			tab[i][j] = 1;
		}
	}
	
	tab2 = malloc(26 * sizeof(*tab2));
	if (tab2)
	{
	  for (i = 0; i < 26 ; i++)
	  {
		tab2[i] = malloc(sizeof (*(tab2[i])) * nb_fichiers);
	  }
	}
	
	

	
	// initialisation de la structure
	
	tableL.tab_lettre_langue = tab;
	tableL.tab_langue_lettre = tab2;
	tableL.nb_langues = nb_fichiers;
	tableL.indice_langue = malloc(sizeof(char*) * nb_fichiers);
	
	return tableL;

}

void afficherTab(table_langue tab){
	int i,j;
	char l = 'a';
	for(i =0; i<26;i++){
		printf("%c, ", l+i);
	}
	printf("\n");
	for (j=0; j<tab.nb_langues; j++){
		for (i= 0; i<26; i++) {
			printf("%f, ", tab.tab_lettre_langue[i][j]);
		}
		printf("\n");
	}
}

table_langue init_tab_lettre_langue() {

	FILE F;
	DIR *rep = opendir("corpus");         // ouverture du repertoir corpus

	table_langue tab = initTab(rep);	  // initialisation de la table
	printf("nb langues = %d\n", tab.nb_langues);
	char lettre;
	 
	struct dirent* fichierLu = NULL;  // pointeur vers la DIRent structure
	
	FILE* f;
	
		
	if (rep==NULL) perror("Erreur : ");  //affiche le message d'erreur selon l'erreur errno
	else {
		// lecture des premiers fichiers dans corpus, nom du fichier dans readDIR->d_name  commence par . puis ..
		fichierLu = readdir(rep); // .
		fichierLu = readdir(rep); // ..
		fichierLu = readdir(rep); // premier fichier de langue
		int j,i =0;
		int nb_l;
		
		while (fichierLu != NULL) {
			char fichier[50] ="corpus/"; // rajouter / après corpus
			char *nomfichier= fichierLu->d_name;
			tab.indice_langue[i] = nomfichier;
			nb_l =0;
			
			strcat(fichier, nomfichier);
			f = fopen(fichier,"r");
			printf("%s\n", fichier);
			if (f == NULL) printf("Erreur ouverture fichier\n");
			fscanf(f,"%c", &lettre);
			//lettre = fgetc(f);
			printf("langue n°%d \n",i);
			while (lettre != EOF){
			
				if (lettre <= 'z' && lettre>='a'){
					int id_lettre = lettre - 'a';
					tab.tab_lettre_langue[id_lettre][i]++;	
				}
				else if(lettre <= 'Z' && lettre>='A'){
					int id_lettre = lettre - 'A';
					tab.tab_lettre_langue[id_lettre][i]++;	
				}
				lettre = fgetc(f);	
				nb_l++;			
			}
			
			// lissage
			nb_l += 26;
			// on calcule P(wi|l)
		
			for (j=0;j<26;j++){
				tab.tab_lettre_langue[j][i] = tab.tab_lettre_langue[j][i] / nb_l;
			}
		
			fclose(f);
			i++;
			fichierLu = readdir(rep);
		}
		
				
		// on remplie P(l|wi)
		
		double PL = 1/tab.nb_langues;
		double Pwi = 1/26;
		
		for (i=0; i<26; i++){

			for (j=0; j<tab.nb_langues; j++) {
					printf("là\n");
			printf("i=%d, j=%d \n",i,j);
				tab.tab_langue_lettre[i][j] = (tab.tab_lettre_langue[i][j] * PL) / Pwi; 
			}
		}
				printf("ici\n");
		
		
	}
	closedir(rep);
	return tab;
	
}

double p_lettre_langue(char l, int langue, table_langue tab) {
	return tab.tab_lettre_langue[l - 'a'][langue];
}

double p_langue_lettre(char l, int langue, table_langue tab) {
	return tab.tab_langue_lettre[l - 'a'][langue];
}

char *nom_langue(int l, table_langue tab){
	return tab.indice_langue[l];
}

