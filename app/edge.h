/*

    Neural Network Image Classifier
    Verze 1.0

    Header edge.h
    Podrobny popis v modulu edge.c.
    
    Dialekt : ANSI C
    Prekladac: libovolny ANSI C-kompatibilni

    Copyright (c) Petr Kozler (A13B0359P), 2014
    Seminarni prace z predmetu `Programovani v jazyce C' (KIV/PC)

    Tento soubor je poskytovan "TAK, JAK JE" BEZ ZARUKY JAKEHOKOLIV DRUHU,
    VCETNE ZARUKY DESIGNU, PRODEJNOSTI A VHODNOSTI POUZITI KE KONRETNIMU UCELU.
    Autor si vyhrazuje veskera prava, ktera zde nejsou vyslovne udelena.

*/

#ifndef _EDGE_H
#define _EDGE_H

/* ____________________________________________________________________________

    Struktury a datove typy
   ____________________________________________________________________________
*/

typedef struct EDGE {
	int n0;
	int n1;
	float weight;
	struct EDGE *next;
} edge_t;	/* struktura predstavujici hranu, ktera uchovava informace 
			o indexech neuronu, ktere propojuje, hodnote vahy a adrese dalsiho 
			prvku spojoveho seznamu hran */

/* ____________________________________________________________________________

    Prototypy funkci
   ____________________________________________________________________________
*/

void add_edge(int n0, int n1, float weight, edge_t **first);

void delete_edges(edge_t *first);

#endif

