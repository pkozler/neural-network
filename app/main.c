/*

    Neural Network Image Classifier
    Verze 1.0

    Modul main.c
    Tento modul obsahuje funkci, ktera slouzi jako vstupni bod programu,
    dale provadi validaci vstupnich paramentru a zavola funkce v modulech
    pro nacteni a zpracovani dat.
    
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
#include <stdbool.h>
#include "neuron.h"
#include "edge.h"
#include "load.h"

/* ____________________________________________________________________________

    static bool validate(int argc, char *argv[])
    
    Provede zbeznou kontrolu predanych argumentu prikazove radky - zkontroluje
    jejich pocet pokud je spravny, overi, zda soubory se zadanymi cestami
    existuji. V pripade chyby vypise hlaseni a navod k pouziti programu.
   ____________________________________________________________________________
*/
static bool validate(unsigned int argc, char *argv[]) {
	FILE *file;
	
	if (argc == 1) {
		return false;
	}
	
	if (argc != 3) {
		puts("Invalid arguments.\n");
		return false;
	}
	
	if ((file = fopen(argv[1], "r")) != NULL) {
		fclose(file);
	}
	else {
		puts("Network file does not exist.\n");
		return false;
	}
	
	if ((file = fopen(argv[2], "r")) != NULL) {
		fclose(file);
	}
	else {
		puts("Image file does not exist.\n");
		return false;
	}

	return true;
}

/* ____________________________________________________________________________

    static void process(char *net_file, char *img_file)
    
    Hlavni rutina programu, zavola funkce pro zpracovani vstupnich dat
    v ostatnich modulech a vypise vysledek.
   ____________________________________________________________________________
*/
static void process(char *net_file, char *img_file) {
	unsigned int image_class;
	neuron_t *input_layer;
	input_layer = load_image(img_file);
	image_class = load_network(net_file, input_layer);
	printf("%d\n", image_class);
}

/* ____________________________________________________________________________

    static void help()
    
    Vypise hlavicku obsahujici nazev, verzi a jmeno autora programu
	a dale strucny navod k pouziti programu.
   ____________________________________________________________________________
*/
static void help() {
	puts("Neural Network Image Classifier (Version 1.0)");
	puts("Seminar work of \"Programming in C\" (KIV/PC)");
	puts("Copyright (c) Petr Kozler (A13B0359P), 2014\n");
	puts("Usage:   <neural_net> \"<network file>\" \"<image file>\"");
    puts("Example:   neural_net.exe neuronova_sit.txt vstupy\0.dat");
    puts("Input files specification:");
    puts("   network file .... text, each line terminated by "
			"\\CR\\LF sequence");
    puts("   image file ...... binary, 32-bit float values, "
			"IEEE 754 format, Little Endian");
}

/* ____________________________________________________________________________
 
    VSTUPNI BOD PROGRAMU
   ____________________________________________________________________________
*/
int main(int argc, char *argv[]) {
	if (validate((unsigned int)argc, argv)) {
		process(argv[1], argv[2]);
		return EXIT_SUCCESS;
	}
	else {
		help();
		return EXIT_FAILURE;
	}
}

