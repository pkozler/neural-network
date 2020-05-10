/*

    Neural Network Image Classifier
    Verze 1.0

    Modul classify.c
    Tento modul provadi samotnou samotnou klasifikaci vstupniho obrazku pomoci
    vypoctu aktivace neuronu v predane neuronove siti. Po dokonceni analyzy
    provede uvolneni veskere alokovane pameti.
    
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
#include <math.h>
#include "neuron.h"
#include "edge.h"
#include "classify.h"

/* ____________________________________________________________________________

    static float compute_activation(neuron_t *j, 
									neuron_t *neurons, edge_t *edges)
    
    Vypocita aktivaci predaneho neuronu pomoci hodnot aktivace neuronu
	a vahy hran v odpovidajici vrstve site.
   ____________________________________________________________________________
*/
static float compute_activation(unsigned int j, float b,
								neuron_t *neurons, edge_t *edges) {
	float sum;
	unsigned int i;
	edge_t *k;
	
	sum = 0;

	for (k = edges; k != NULL; k = k->next) {
		if (k->n1 == j) {
			for (i = 0; i < neurons->length; i++) {
				if (k->n0 == i) {
					sum += (neurons->array[i] * k->weight);
				}
			}
		}
	}

	return (float) tanh(b + sum);
}

/* ____________________________________________________________________________

    static int get_most_active(neuron_t *neurons)
    
    V predane vrstve site nalezne neuron s nejvyssi aktivaci.
   ____________________________________________________________________________
*/
static unsigned int get_most_active(neuron_t *neurons) {
	unsigned int max, i;
	
	max = 0;

	for (i = 0; i < neurons->length; i++) {
		if (neurons->array[i] > neurons->array[max]) {
			max = i;
		}
	}

	return max;
}

/* ____________________________________________________________________________

    int get_class(int nl_count, 
					neuron_t *neuron_layers[], edge_t *edge_layers[])
    
    Pro kazdy neuron v kazde vrstve site mimo nactenou vstupni vrstvu
    zavola funkci pro vypocet hodnoty aktivace. Po provedeni vypoctu
    zavola funkci pro uvolneni veskere alokovane pameti.
   ____________________________________________________________________________
*/
int get_class(unsigned int nl_count, 
				neuron_t *neuron_layers[], edge_t *edge_layers[]) {
	unsigned int k, j, cls;
	
	for (k = 1; k < nl_count; k++) {
		for (j = 0; j < neuron_layers[k]->length; j++) {
			neuron_layers[k]->array[j] = compute_activation(j, neuron_layers[k]->array[j], 
												neuron_layers[k - 1], edge_layers[k - 1]);
		}
	}
	
	cls = get_most_active(neuron_layers[k - 1]);
	/*clear_lists(nl_count, neuron_layers, edge_layers);*/
	
	return cls;
}

/* ____________________________________________________________________________

    static void clear_lists(int nl_count, 
							neuron_t *neuron_layers[], edge_t *edge_layers[])
    
    Pro kazdy spojovy seznam predstavujici vrstvu neuronu resp. hran zavola
    funkci pro smazani seznamu a uvolneni alokovane pameti. Nakonec uvolni
    i zbyvajici pamet alokovanou pro ukazatele na jednotlive seznamy.
   ____________________________________________________________________________
*/
static void clear_lists(unsigned int nl_count, 
						neuron_t *neuron_layers[], edge_t *edge_layers[]) {
	unsigned int k;

	for (k = 0; k < nl_count - 1; k++) {
		delete_edges(edge_layers[k]);
		free(neuron_layers[k]->array);
		free(neuron_layers[k]);
	}
	
	free(neuron_layers[k]->array);
	free(neuron_layers[k]);
	free(edge_layers);
	free(neuron_layers);
}

