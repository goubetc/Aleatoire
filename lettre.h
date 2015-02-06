#pragma once

// Définitions des constantes
#define NB_LANGUES 4
#define NB_LETTRES 26
typedef enum {DUTCH,ENGLISH,FRENCH,ITALIAN} langue;

typedef struct {
	int **tab_langue_lettre; // contient les p(L / wi) ou p(wi / L)
	int nb_langues;
	// char **indice_langue;
	} table_langue;

//table_langue init_tab_langue_lettre();

table_langue init_tab_lettre_langue();

//char *nom_langue(int l);

void afficherTab(table_langue tab);
