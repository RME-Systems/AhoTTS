#ifndef __ISOFILT_H__
#define __ISOFILT_H__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ isofilt.h
Nombre paquete............... normalizador
Lenguaje fuente.............. C
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.1    25/10/00  Yon2.     Aniadir funciones para acceder
                             a la tabla y filtrar buffers.
0.0.0    17/10/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

Matriz de 256 elementos que filtra caracteres de la tabla
ISO 8859/Latin 1.
Los caracteres que no son de interés los convierte a
espacios, y los que tengan un sustituto se convierten.

Los menores de 32, caracteres de escape se sustituyen todos
por espacios. Incluidos el CR, el LF y el tabulador.
Del 127 al 160 son caracteres de control que también se eliminan.

No editar este archivo desde DOS con BC la página de códigos
es totalmente diferente. Es evidente que para poder ver este
archivo correctamente se necesita una tabla de caracteres en uso
ISO 8859/Latin 1

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

extern INT iso8859filter[256];
CHAR char_fltr(CHAR i);
pCHAR buff_fltr(pCHAR buffer);

/**********************************************************/

#ifdef __cplusplus
}
#endif

/**********************************************************/


#endif
