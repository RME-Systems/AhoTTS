#ifndef __ROMAN_H__
#define __ROMAN_H__


/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ roman.h
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.0    28/11/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

  Se da en este m¢dulo soporte para n£meros Romanos. Se da en
base a dos funciones:
  - isRoman() -> que nos dice si un n£mero es romano o no.
  - romanStr2num -> que convierte una cadena de caracteres
romanos en un n£mero decimal.
  La mayor complejidad se encuentra en saber si un n£mero es
romano. Sabido esto convertir el n£mero a decimal es
simplic¡simo.

NOTA: Actualmente, operan ambas funciones est‚ la cadena
formada por letras en mayusculas, minusculas o combinaci¢n
de ambas.

!!!!!!!!!!!!!!!!!
NOTA: Verificar que no haya caracteres en may£culas y
minusculas a la vez ya que en este caso no es un n£mero
romano. O incluso que no aparezcan en min£sculas.
!!!!!!!!!!!!!!!!!

Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/


/**********************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/

#include "tdef.h"

enum  {
      ROMAN_NONUM = 0,
      ROMAN_I,
      ROMAN_V,
      ROMAN_X,
      ROMAN_L,
      ROMAN_C,
      ROMAN_D,
      ROMAN_M,
      NUM_ROMAN
};

/**********************************************************/


/**********************************************************/

BOOL isRoman(pCHAR str);
UINT romanStr2num(pCHAR str);

/**********************************************************/

#ifdef __cplusplus
}
#endif

/**********************************************************/

#endif
