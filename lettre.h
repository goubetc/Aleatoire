#pragma once

// Définitions des constantes
#define NB_LANGUES 4
#define NB_LETTRES 26
typedef enum {DUTCH,ENGLISH,FRENCH,ITALIAN} langue;
typedef int tab_langue_lettre[NB_LANGUES][NB_LETTRES]; // contient les p(L / wi) ou p(wi / L)

char* nom_langue(int l);
