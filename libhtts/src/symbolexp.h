#ifndef __SYMBOLEXP_H__
#define __SYMBOLEXP_H__
/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ isofilt.c
Nombre paquete............... normalizador
Lenguaje fuente.............. C
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.1.0	 11/11/02  inigos	 Adaptación al castellano
0.0.1    26/10/00  Yon2.     Archivo de cabecera y 
                             metodo de acceso.
0.0.0    17/10/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

Matriz de 256 elementos que filtra caracteres de la tabla
ISO 8859/Latin 1.
Los caracteres que no son de interés los convierte a
No editar este archivo desde DOS con BC la página de códigos
es totalmente diferente.

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/




#include "tdef.h"

/**********************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/

pCHAR getchexp(CHAR c);
extern pCHAR symbolexp[256];
pCHAR eu_getchexp(CHAR c);
extern pCHAR eu_symbolexp[256];
pCHAR es_getchexp(CHAR c);
extern pCHAR es_symbolexp[256];

/**********************************************************/

#ifdef __cplusplus
}
#endif

/**********************************************************/


/**********************************************************/
#endif
