/*

    Neural Network Image Classifier
    Verze 1.0

    Modul edge.c
    Tento modul obsahuje funkce pro alokaci pameti pro strukturu
    hrany definovanou v prislusnem hlavickovem souboru, spojovani
    hran do spojoveho seznamu a nasledne uvolnovani pameti 
    po dokonceni prace se spojovym seznamem hran.
    
    Dialekt : ANSI C
    Prekladac: libovolny ANSI C-kompatibilni

    Copyright (c) Petr Kozler (A13B0359P), 2014
    Seminarni prace z predmetu `Programovani v jazyce C' (KIV/PC)

    Tento soubor je poskytovan "TAK, JAK JE" BEZ ZARUKY JAKEHOKOLIV DRUHU,
    VCETNE ZARUKY DESIGNU, PRODEJNOSTI A VHODNOSTI POUZITI KE KONRETNIMU UCELU.
    Autor si vyhrazuje veskera prava, ktera zde nejsou vyslovne udelena.

*/

#include <stdio.h>
#include <stdlib.h>
#include "edge.h"

/* ____________________________________________________________________________

    void add_edge(int n0, int n1, float weight, edge_t **first)
    
    Alokuje pamet pro novou hranu, ulozi do ni predane informace
    a vlozi ji do predaneho spojoveho seznamu.
   ____________________________________________________________________________
*/
void add_edge(int n0, int n1, float weight, edge_t **first) {
	edge_t *e;
	e = malloc(sizeof(edge_t));
	
	if (e != NULL) {
		e->n0 = n0;
		e->n1 = n1;
		e->weight = weight;
		
		if (*first == NULL) {
			e->next = NULL;
		}
		else {
			e->next = *first;
		}
		
		*first = e;
	}
}

/* ____________________________________________________________________________

    void delete_edges(edge_t *first)
    
    Uvolni pamet alokovanou pro jednotlive hrany v predanem spojovem seznamu
    a odstrani tak spojovy seznam hran.
   ____________________________________________________________________________
*/
void delete_edges(edge_t *first) {
	if (first == NULL) {
		return;
	}
	else {
		edge_t *temp;

		while (first != NULL)
		{
			temp = first;
			first = first->next;
			free(temp);
		}
	}
}

