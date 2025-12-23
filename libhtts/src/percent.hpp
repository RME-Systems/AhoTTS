#ifndef __PERCENT_HPP__
#define __PERCENT_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ percent.hpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.1    28/03/01  Yon2.     Need More Data.
0.0.0    22/03/01  Yon2.     Codificacion inicial.

======================== Contenido ========================

	Este módulo se encarga de resolver el signo de tanto por
ciento. Si aparece solo se expandirá y se acabo.
	Si aparece con un número por delante (forma castellana)
se pasará a la forma en euskara. Si aparece detrás el número
se expandirá como corresponda, y si aparece un número detrás
y otro delante será preferida la forma en euskara, es decir,
se tomarña el número que va por detrás.

		% 100 -> ehuneko hamarra

Se declina el numero.  XX-a
Se declina de forma local, ya que no hay información de
declinación previa.

Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
 
/**********************************************************/

enum PercentType	{
	PERCENT_UNKNOWN=0,
	PERCENT_BASQUE,
	PERCENT_SPANISH,
	PERCENT_NEEDMOREDATA
};


/**********************************************************/

#endif

