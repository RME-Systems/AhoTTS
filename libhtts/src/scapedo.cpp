/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ scapedo.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.0    19/06/01  Yon2.     Codificacion inicial.

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
#include "scapedo.hpp"

#include "httsmsg.h"
#include "uti.h"

/**********************************************************/

//Los c¢digos de las secuencias de escape.
CHAR seqCodes[] = { '0', 'P'};


/**********************************************************/

SeqType analizeSeq(CruTxt &ct, CtI p, pINT value)
{
	SeqType retval = SEQ_UNKNOWN;
	CtI q;
	CHAR tempChar;


	q = ct.next(p);

	tempChar = ct.getStr(q)[0];

	htts_warn("scapedo: analizeSeq code: %c PauseCode %c", tempChar, seqCodes[SEQ_PAUSE]);

	if (tempChar == seqCodes[SEQ_UNKNOWN]) retval = SEQ_UNKNOWN;
	if (tempChar == seqCodes[SEQ_PAUSE]) retval = SEQ_PAUSE;


	q = ct.next(q);


	*value = xstr2li( ct.getStr(q), 0 );

	htts_warn("scapedo: analizeSeq value: %d", *value);


	return retval;
}


/**********************************************************/
