/*

    Neural Network Image Classifier
    Verze 1.0

    Modul load.c
    Tento modul provadi nacteni dat o rozpoznavanem obrazku a neuronove siti 
	ze souboru, jejichz cesty jsou predany programu jako vstupni parametry.
    
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
#include <string.h>
#include "neuron.h"
#include "edge.h"
#include "classify.h"
#include "load.h"

/* ____________________________________________________________________________

    static neuron_t *read_floats(FILE *file, int neuron_count)
    
    Nacte jednotlive ctverice bytu z binarniho souboru predstavujiciho
    rozpoznavany obrazek a ulozi je jako hodnoty typu float do noveho neuronu,
    ktery je pridan do spojoveho seznamu.
   ____________________________________________________________________________
*/
static neuron_t *read_floats(FILE *file, unsigned int neuron_count) {
	unsigned int i;
	pixel_t p;
	neuron_t *input_layer;
	input_layer = malloc(sizeof(neuron_t));
	input_layer->length = neuron_count;
	input_layer->array = malloc(neuron_count * sizeof(float));

	for (i = 0; i < neuron_count; i++) {
		fread(p.chars, 1, FLOAT_SIZE, file);
		input_layer->array[i] = p.f;
	}
	
	return input_layer;
}

/* ____________________________________________________________________________

    neuron_t *load_image(char *img_file)
    
    Otevre binarni soubor predstavujici rozpoznavany obrazek, zjisti 
	jeho velikost, zavola funkci pro cteni dat a vrati vznikly 
	spojovy seznam neuronu predstavujici vstupni vrstvu neuronove site.
   ____________________________________________________________________________
*/
neuron_t *load_image(char *img_file) {
	FILE *file;
	unsigned int neuron_count;
	long size;
	neuron_t *input_layer;

	file = fopen(img_file, "rb");
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	neuron_count = (unsigned int) (size / FLOAT_SIZE);
	input_layer = read_floats(file, neuron_count);
	fclose(file);
	
	return input_layer;
}

/* ____________________________________________________________________________

    static int parse_index(char *line)
    
    Ze radku vyjme textovou informaci o indexu vrstvy neuronove site a vrati
    ji jako hodnotu typu int.
   ____________________________________________________________________________
*/
static int parse_index(char *line) {
	char *str;

	strtok(line, " ");
	strtok(NULL, " ");
	strtok(NULL, " ");
	str = strtok(NULL, " ");
	
	return atoi(strtok(str, ":"));
}

/* ____________________________________________________________________________

    static void read_edges(FILE *file, edge_t *edge_layers[], char *line)
    
    Precte jednotlive radky predstavujici informace o hranach z textoveho
    souboru predstavujiciho neuronovou sit a vytvori odpovidajici hrany,
    ktere jsou ulozeny do spojoveho seznamu hran tvoriciho aktualni
    vrstvu neuronove site.
   ____________________________________________________________________________
*/
static void read_edges(FILE *file, edge_t *edge_layers[], char *line) {
	unsigned int index, has_next;
	char *str;

	str = "b hodnoty vrstvy";
	index = parse_index(line) - 1;
	edge_layers[index] = NULL;
	
	do {
		fgets(line, COM_STRING_LENGTH, file);
		has_next = strncmp(line, str, strlen(str));

		if (has_next && !feof(file)) {
			unsigned int i, j;
			float w;
			
			i = atoi(strtok(line, " "));
			j = atoi(strtok(NULL, " "));
			w = atof(strtok(NULL, " "));
			add_edge(i, j, w, &edge_layers[index]);
		}
		else {
			break;
		}
	}
	while (has_next);
}

/* ____________________________________________________________________________

    static void read_neurons(FILE *file, neuron_t *neuron_layers[], char *line)
    
    Precte jednotlive radky predstavujici informace o neuronech z textoveho
    souboru predstavujiciho neuronovou sit a vytvori odpovidajici neurony,
    ktere jsou ulozeny do spojoveho seznamu neuronu tvoriciho aktualni
    vrstvu neuronove site.
   ____________________________________________________________________________
*/
static void read_neurons(FILE *file, neuron_t *neuron_layers[], char *line) {
	unsigned int index, pos, len, i, has_next;
	char *str;
	
	str = "W hodnoty vrstvy";
	index = parse_index(line);
	pos = ftell(file);
	len = 0;
	
	do {
		fgets(line, COM_STRING_LENGTH, file);
		has_next = strncmp(line, str, strlen(str));

		if (has_next && !feof(file)) {
			len++;
		}
		else {
			break;
		}
	}
	while (has_next);
	
	neuron_layers[index] = malloc(sizeof(neuron_t));
	neuron_layers[index]->length = len;
	neuron_layers[index]->array = malloc(len * sizeof(float));
	fseek(file, pos, SEEK_SET);
	fgets(line, COM_STRING_LENGTH, file);
	
	for (i = 0; i < len; i++) {
		unsigned int k;
		float b;
		
		k = atoi(strtok(line, " "));
		b = atof(strtok(NULL, " "));
		neuron_layers[index]->array[k] = b;
		
		fgets(line, COM_STRING_LENGTH, file);
	}
}

/* ____________________________________________________________________________

    static void read_layers(FILE *file, int layer_count, 
							neuron_t *neuron_layers[], edge_t *edge_layers[])
    
    Podle zjisteneho poctu vrstev neuronove site provede odpovidajici pocet
    volani funkci pro cteni radku s informacemi o hranach, resp. neuronech
    ze vstupniho textoveho souboru predstavujiciho neuronovou sit.
   ____________________________________________________________________________
*/
static void read_layers(FILE *file, unsigned int layer_count, 
						neuron_t *neuron_layers[], edge_t *edge_layers[]) {
	char line[COM_STRING_LENGTH];
	unsigned int i;
	
	fgets(line, COM_STRING_LENGTH, file);

	for (i = 0; i < layer_count; i++) {
		read_edges(file, edge_layers, line);
		read_neurons(file, neuron_layers, line);
	}
}

/* ____________________________________________________________________________

    int load_network(char *net_file, neuron_t *input_layer)
    
    Otevre textovy soubor predstavujici neuronovou sit, precte prvni radek
    obsahujici informaci o poctu vrstev site, alokuje pamet pro potrebny
    pocet ukazatelu na spojove seznamy neuronu resp. hran predstavujici
    jednotlive vrstvy site a zavola funkce pro precteni a ulozeni informaci
    o jednotlivych neuronech a hranach v kazde vrstve site.
   ____________________________________________________________________________
*/
int load_network(char *net_file, neuron_t *input_layer) {
	FILE *file;
	neuron_t **neuron_layers;
	edge_t **edge_layers;
	char line[COM_STRING_LENGTH];
	unsigned int layer_count;

	char *str = "Pocet vrstev:";
	file = fopen(net_file, "r");
	fgets(line, COM_STRING_LENGTH, file);
	strtok(line, ":");
	layer_count = (unsigned int) atoi(strtok(NULL, ":"));
	neuron_layers = malloc((size_t) (layer_count + 1 * sizeof(neuron_t*)));
	neuron_layers[0] = input_layer;
	edge_layers = malloc((size_t) (layer_count * sizeof(edge_t*)));
	read_layers(file, layer_count, neuron_layers, edge_layers);
	fclose(file);
	
	return get_class(layer_count + 1, neuron_layers, edge_layers);
}

