#ifndef __ROMANHILVL_HPP__
#define __ROMANHILVL_HPP__
/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ romanhilvl.hpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.2    18/03/00  Yon2.     Tipo de numero romano.
0.0.0    28/11/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

!!!!!!!!!!!!!!!!!
NOTA: Verificar que no haya caracteres en may£culas y
minusculas a la vez ya que en este caso no es un n£mero
romano. O incluso que no aparezcan en min£sculas.
!!!!!!!!!!!!!!!!!

Los numeros romanos son siempre ordinales. Hacer.
Y si van acompa¤ados de "." fuera, fin frase ?

Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
  
 
/**********************************************************/

enum RomanType	{
	ROMAN_UNKNOWN=0,
	ROMAN_ROMAN,
  ROMAN_ROMAN_P,
	ROMAN_ROMAN_PUNT,
	ROMAN_NEEDMOREDATA
};

/**********************************************************/

#endif

