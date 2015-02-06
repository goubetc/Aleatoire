#pragma once

#include "lettre.h"

typedef double tab_langue_mot[NB_LANGUES]; 

void p_langue_mot(char* w, tab_langue_mot tab); // renvoie P(langue / mot)

void p_mot_langue(char* w, tab_langue_mot tab); // renvoie P(mot / langue)
