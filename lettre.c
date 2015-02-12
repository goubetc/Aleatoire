#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
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
	tab = malloc(NB_LETTRES * sizeof(*tab));
	if (tab)
	{
	  for (i = 0; i < NB_LETTRES ; i++)
	  {
		tab[i] = malloc(sizeof (*(tab[i])) * nb_fichiers);
	  }
	}
	
	/* on effectue le +1 sur tout le tableau */
	for (i= 0;i<NB_LETTRES ; i++){
		for(j=0; j<nb_fichiers; j++) {
			tab[i][j] = 1;
		}
	}
	
	tab2 = malloc(NB_LETTRES * sizeof(*tab2));
	if (tab2)
	{
	  for (i = 0; i < NB_LETTRES ; i++)
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
	for(i =0; i<NB_LETTRES;i++){
		printf("%c, ", l+i);
	}
	printf("\n");
	for (j=0; j<tab.nb_langues; j++){
		for (i= 0; i<NB_LETTRES; i++) {
			printf("%f, ", tab.tab_lettre_langue[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (j=0; j<tab.nb_langues; j++){
		for (i= 0; i<NB_LETTRES; i++) {
			printf("%f, ", tab.tab_langue_lettre[i][j]);
		}
		printf("\n");
	}
}

table_langue init_tab_lettre_langue() {

//	FILE F;
    DIR *rep = opendir("corpus");         // ouverture du repertoire corpus

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
        double nb_lettres_total;
		
		while (fichierLu != NULL) {
            char fichier[50] ="corpus/"; // rajouter / après corpus
            char *nomfichier= fichierLu->d_name;
			tab.indice_langue[i] = malloc(sizeof(nomfichier));
			strcpy(tab.indice_langue[i], nomfichier);


			int k=0;
			while (tab.indice_langue[i][k] != '.') k++;
			tab.indice_langue[i][k] = '\0';
			nb_lettres_total=0;
			
            strcat(fichier, nomfichier);
            printf("%s\n",fichier);
			f = fopen(fichier,"r");
			if (f == NULL) printf("Erreur ouverture fichier %s\n", nomfichier);
			fscanf(f,"%c", &lettre);
			while (lettre != EOF){
			
				if (lettre <= 'z' && lettre>='a'){
					int id_lettre = lettre - 'a';
					tab.tab_lettre_langue[id_lettre][i]++;
					nb_lettres_total++;	
				}
				else if(lettre <= 'Z' && lettre>='A'){
					int id_lettre = lettre - 'A';
					tab.tab_lettre_langue[id_lettre][i]++;	
					nb_lettres_total++;
				}
				lettre = fgetc(f);	
							
			}
			// lissage
			nb_lettres_total+= NB_LETTRES;
			// on calcule P(wi|l)
		
			for (j=0;j<NB_LETTRES;j++){
                tab.tab_lettre_langue[j][i] = (tab.tab_lettre_langue[j][i]) / nb_lettres_total;
			}
		
			fclose(f);
			i++;
			fichierLu = readdir(rep);
		}
		
				
        // on remplit P(l|wi)
		
		double invPL = tab.nb_langues;
		double invPwi = NB_LETTRES;
		
		for (i=0; i<NB_LETTRES; i++){

            for (j=0; j<tab.nb_langues; j++) {
				tab.tab_langue_lettre[i][j] = ((tab.tab_lettre_langue[i][j] * invPwi) / invPL) ; 
			}
		}
		
		
	}
	closedir(rep);
	return tab;
	
}

double p_lettre_langue(char l, int langue, table_langue tab) {
	if ((l >= 'a')&&(l<='z'))
		return tab.tab_lettre_langue[l - 'a'][langue];
	else if ((l>= 'A') && (l<='Z'))
		return tab.tab_lettre_langue[l - 'A'][langue];
	else exit(0);
}

double p_langue_lettre(char l, int langue, table_langue tab) {
	if ((l >= 'a')&&(l<='z'))
		return tab.tab_langue_lettre[l - 'a'][langue];
	else if ((l>= 'A') && (l<='Z')) 
		return tab.tab_langue_lettre[l - 'A'][langue];
	else exit(0);
}

char *nom_langue(int l, table_langue tab){
	return tab.indice_langue[l];
}

