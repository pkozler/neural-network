/*

    Neural Network Image Classifier
    Verze 1.0

    Header classify.h
    Podrobny popis v modulu classify.c.
    
    Dialekt : ANSI C
    Prekladac: libovolny ANSI C-kompatibilni

    Copyright (c) Petr Kozler (A13B0359P), 2014
    Seminarni prace z predmetu `Programovani v jazyce C' (KIV/PC)

    Tento soubor je poskytovan "TAK, JAK JE" BEZ ZARUKY JAKEHOKOLIV DRUHU,
    VCETNE ZARUKY DESIGNU, PRODEJNOSTI A VHODNOSTI POUZITI KE KONRETNIMU UCELU.
    Autor si vyhrazuje veskera prava, ktera zde nejsou vyslovne udelena.

*/

#ifndef _CLASSIFY_H
#define _CLASSIFY_H

/* ____________________________________________________________________________

    Prototypy funkci
   ____________________________________________________________________________
*/

static float compute_activation(unsigned int j, float b,
								neuron_t *neurons, edge_t *edges);

static unsigned int get_most_active(neuron_t *neurons);

int get_class(unsigned int nl_count, 
				neuron_t *neuron_layers[], edge_t *edge_layers[]);

static void clear_lists(unsigned int nl_count, 
						neuron_t *neuron_layers[], edge_t *edge_layers[]);

#endif

