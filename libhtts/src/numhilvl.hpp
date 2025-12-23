#ifndef __NUMHILVL_HPP__
#define __NUMHILVL_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ numhilvl.hpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.7	 02/01/07  inaxio    Añadido NUM_RESTA y NUM_SUMA para restas y sumas de números
0.0.6	 29/12/06  inaxio    Añadido NUM_NEGATIVE para números negativos
0.0.5	 20/11/06  inaxio    Añadido NUM_UNIT para unidades monetarias
0.0.4	 18/10/06  inaxio    Añadidos NUM_ORD_ES_OS (1os) y el femenino _AS (1as) para el plural
0.0.3    16/11/02  inigos    Añadidos NUM_ORD_ES_O (º) y el femenino _A (ª)
0.0.3    07/03/01  Yon2.     Too Large Number (>18 chars) -> spell.
0.0.2    22/03/01  Yon2.     Need More Data.
0.0.1    09/12/00  Yon2.     Tipo de numero.
0.0.0    19/11/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

M¢dulo expansor de n£meros a nivel alto. Expande cardinales
y ordinales. Se apoya en el m¢dulo de expansi¢n num‚rica de
nivel bajo.

Yon2.

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
  
 
/**********************************************************/

enum NumType	{
	NUM_UNKNOWN=0,
	NUM_CARD,
	NUM_PUNT,
	NUM_COMA,
	NUM_NEGATIVE,
	NUM_RESTA,
	NUM_SUMA,
	NUM_ORD_ES_O,
	NUM_ORD_ES_A,
	NUM_ORD_ES_OS,
	NUM_ORD_ES_AS,
	NUM_ORD,
	NUM_ORD_PUNT,
	NUM_CARD_DEC,
	NUM_TOO_LARGE,
	NUM_NEEDMOREDATA,
// Los porcentajes
	NUM_CARD_PER,
	NUM_PUNT_PER,
	NUM_COMA_PER,
// Las unidades monetarias
	NUM_UNIT
};

/**********************************************************/

#endif

