#ifndef __CALLBACK_H__
#define __CALLBACK_H__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ callback.h
Nombre paquete............... normalizador
Lenguaje fuente.............. C
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.0    07/01/01  Yon2.     Codificacion inicial.

======================== Contenido ========================

Definici¢n de los modos de CALLBACK. Interfaz I/O.

Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
 
/**********************************************************/

enum  {
      TEX_CB_NOCALL=0,
      TEX_CB_CALL1=1,
      TEX_CB_BLOCKCALL=2
};


#endif

