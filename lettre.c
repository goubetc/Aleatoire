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
	int **tab;
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

	
	// initialisation de la structure
	
	tableL.tab_langue_lettre = tab;
	tableL.nb_langues = nb_fichiers;
	
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
			printf("%d, ", tab.tab_langue_lettre[i][j]);
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
		int i =0;
		
		while (fichierLu != NULL) {
			char fichier[50] ="corpus/"; // rajouter / après corpus
			
			strcat(fichier, fichierLu->d_name);
			f = fopen(fichier,"r");
			printf("%s\n", fichier);
			if (f == NULL) printf("Erreur ouverture fichier\n");
			fscanf(f,"%c", &lettre);
			//lettre = fgetc(f);
			printf("langue n°%d \n",i);
			while (lettre != EOF){
				if (lettre <= 'z' && lettre>='a'){
					int id_lettre = lettre - 'a';
					tab.tab_langue_lettre[id_lettre][i]++;	
				}
				else if(lettre <= 'Z' && lettre>='A'){
					int id_lettre = lettre - 'A';
					tab.tab_langue_lettre[id_lettre][i]++;	
				}
				lettre = fgetc(f);				
			}
			fclose(f);
			i++;
			fichierLu = readdir(rep);
		}
		
		
	}
	closedir(rep);
	return tab;
	
}

