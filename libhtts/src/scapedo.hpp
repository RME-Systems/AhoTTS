#ifndef __SCAPEDO_HPP__
#define __SCAPEDO_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ scapedo.hpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.0    18/06/01  Yon2.     Codificacion inicial.

======================== Contenido ========================

En este fichero se implementa la ejecución de las secuencias
de escape.
De momento sólo pausas.

Yon2.

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

/**********************************************************/

#include "tdef.h"
#include "t2l.hpp"

/**********************************************************/

#define DEBUG_SCAx

/***********************************************************************/

enum SeqType	{
	SEQ_UNKNOWN=0,
	SEQ_PAUSE
};

extern CHAR seqCodes[];


SeqType analizeSeq(CruTxt &ct, CtI p, pINT value);


/***********************************************************************/

#endif

