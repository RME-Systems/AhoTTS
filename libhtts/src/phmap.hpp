#ifndef __PHMAP_HPP__
#define __PHMAP_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ phmap.hpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Borja Etxebarria
.............................

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.0.0    24/11/97  borja     Codificacion inicial.

======================== Contenido ========================
<DOC>
Mapeo tosco de fonemas
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

/**********************************************************/

#include "string.hpp"
#include "uttph.hpp"

/**********************************************************/

class PhMap {
private:
	String lang;
	BOOL phMap_jw2iu;

public:
	PhMap( VOID );
	BOOL create( VOID ) { return TRUE; };
	VOID utt_phmap( UttPh &u );

	BOOL set( const CHAR *param, const CHAR *val );
	const CHAR *get( const CHAR *param );
};

/**********************************************************/

#endif

