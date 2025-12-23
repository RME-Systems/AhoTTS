#ifndef __CHOPUTI_H__
#define __CHOPUTI_H__
/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ choputi.h
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.1.0    12/03/01  Yon2.     Se mueve del speller wrdList.
0.0.0    11/12/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

  Utilidades varias comunes a los fuentes del normalizador.

Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
 
/**********************************************************/

#include "tdef.h"

/**********************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/

UINT chu_str2num(pCHAR str); //Paso de cadena a n£mero.
BOOL isVowel(CHAR ch); //Es un caracter una vocal?
BOOL isConso(CHAR ch); //Es un caracter una consonante?
CHAR uniqVowel(CHAR ch); //Pasa a formato unico de vocal.
CHAR uniqConso(CHAR ch); //Pasa a formato unico de consonante.


INT str2wrdLst(pCHAR srcStr, pCHAR *words[]);
VOID freewrdLst(INT count, pCHAR words[]);


/**********************************************************/

#ifdef __cplusplus
}
#endif

/**********************************************************/

#endif
