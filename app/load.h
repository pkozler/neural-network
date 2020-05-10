/*

    Neural Network Image Classifier
    Verze 1.0

    Header load.h
    Podrobny popis v modulu load.c.
    
    Dialekt : ANSI C
    Prekladac: libovolny ANSI C-kompatibilni

    Copyright (c) Petr Kozler (A13B0359P), 2014
    Seminarni prace z predmetu `Programovani v jazyce C' (KIV/PC)

    Tento soubor je poskytovan "TAK, JAK JE" BEZ ZARUKY JAKEHOKOLIV DRUHU,
    VCETNE ZARUKY DESIGNU, PRODEJNOSTI A VHODNOSTI POUZITI KE KONRETNIMU UCELU.
    Autor si vyhrazuje veskera prava, ktera zde nejsou vyslovne udelena.

*/

#ifndef _LOAD_H
#define _LOAD_H

/* ____________________________________________________________________________

    Preprocesorem definovane konstanty
   ____________________________________________________________________________
*/

#define FLOAT_SIZE 4					/* delka cisla typu float v bytech */

#define COM_STRING_LENGTH 256			/* maximalni delka bezneho retezce */

/* ____________________________________________________________________________

    Struktury a datove typy
   ____________________________________________________________________________
*/

typedef union {
  char chars[FLOAT_SIZE];
  float f;
} pixel_t;	/* svaz predstavujici bod na vstupnim obrazku, ktery je ulozen 
			jako pole 4 bytu a pote nacten jako cislo typu float */

/* ____________________________________________________________________________

    Prototypy funkci
   ____________________________________________________________________________
*/

static neuron_t *read_floats(FILE *file, unsigned int neuron_count);

neuron_t *load_image(char *img_file);

static int parse_index(char *line);

static void read_edges(FILE *file, edge_t *edge_layers[], char *line);

static void read_neurons(FILE *file, neuron_t *neuron_layers[], char *line);

static void read_layers(FILE *file, unsigned int layer_count, 
						neuron_t *neuron_layers[], edge_t *edge_layers[]);

int load_network(char *net_file, neuron_t *input_layer);

#endif

