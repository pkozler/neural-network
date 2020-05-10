/*

    Neural Network Image Classifier
    Verze 1.0

    Header neuron.h
    Podrobny popis v modulu neuron.c.
    
    Dialekt : ANSI C
    Prekladac: libovolny ANSI C-kompatibilni

    Copyright (c) Petr Kozler (A13B0359P), 2014
    Seminarni prace z predmetu `Programovani v jazyce C' (KIV/PC)

    Tento soubor je poskytovan "TAK, JAK JE" BEZ ZARUKY JAKEHOKOLIV DRUHU,
    VCETNE ZARUKY DESIGNU, PRODEJNOSTI A VHODNOSTI POUZITI KE KONRETNIMU UCELU.
    Autor si vyhrazuje veskera prava, ktera zde nejsou vyslovne udelena.

*/

#ifndef _NEURON_H
#define _NEURON_H

/* ____________________________________________________________________________

    Struktury a datove typy
   ____________________________________________________________________________
*/

typedef struct NEURON {
	unsigned int length;
	float *array;
} neuron_t;	/* struktura predstavujici neuron, ktery uchovava informaci 
			o indexu, hodnote aktivace, pocatecni konstante a adrese dalsiho 
			prvku spojoveho seznamu neuronu */

#endif

