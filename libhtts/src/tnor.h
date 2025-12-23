#ifndef __TNOR_H__
#define __TNOR_H__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ tnor.h
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.6    01/10/04  inigos    Tipos de normalizaci¢n NAME y CAPITAL
0.0.5    07/05/01  Yon2.     Tipo de normalizaci¢n UNIT.
0.0.4    07/05/01  Yon2.     Tipo de normalizaci¢n palabra con ap¢strofe -> t'erdi
0.0.3    10/03/01  Yon2.     ..._ACRO -> ..._ACROABBUNI
0.0.2    03/03/01  Yon2.     Grupo palabra compuesta.
0.0.1    02/01/01  Yon2.     Grupo desconocido.
0.0.0    11/12/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

  Definici¢n de los tipos posibles de normalizaci¢n.
La normalizaci¢n en s¡ se hace en el m¢dulo normal.cpp.
El soporte para normalizaci¢n est  en el m¢dulo "ctlist"
ver tanto el 'hpp' como el 'cpp'.

Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

/**********************************************************/

enum TNOR	{
	UTYPENOR_UNKNOWN=0,
	UTYPENOR_NORMAL,
	UTYPENOR_NUMBER,
	UTYPENOR_TIME,
	UTYPENOR_DATE,
	UTYPENOR_ACROABBUNI,
	UTYPENOR_UNIT,
	UTYPENOR_SPELL,
	UTYPENOR_COMP,
	UTYPENOR_WEB,
	UTYPENOR_APOST,
	UTYPENOR_UNKGROUP,
	UTYPENOR_NAME,
	UTYPENOR_CAPITAL,
};


/**********************************************************/

#endif
