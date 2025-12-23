/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ es_pos.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Inma Sardon
Recodificacion............... inigos

Version  dd/mm/aa  Autor     Comentario
-------  --------  --------  ----------
1.0.1    03/10/07  Inaki     define MODULO_1 y _2 para dividir el sinte en 3 modulos
1.0.0    09/01/04  inigos    Adaptacion castellano
0.1.0    24/11/97  Borja     Codificacion inicial (copia euskera)

======================== Contenido ========================
<DOC>
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
#include "uti.h"
#include "uttws.hpp"
#include "httsmsg.h"
#include "uttws.hpp"
#include "uttph.hpp"
#include "es_lingp.hpp"
//#include "aholib.hpp"

/**********************************************************/

LangES_POS::LangES_POS( VOID )
{
	created=FALSE;
}

/**********************************************************/

LangES_POS::~LangES_POS( VOID )
{
}


/**********************************************************/

BOOL LangES_POS::create( VOID )
{
	BOOL ret=TRUE;
	created=TRUE;

	#ifndef MODULO_2 //IÑAKI
	ret = ret && categ.create();
	#endif
	#ifndef MODULO_1 //IÑAKI
	ret = ret && grupof.create();
	#endif

	return ret ;
}

/**********************************************************/

BOOL LangES_POS::set( const CHAR *param, const CHAR * value )
{
	BOOL ret=FALSE;
/*	if (!strcmp(param,"PhTSimple")) {
		phtr.setPhTSimple(str2bool(value,TRUE));
		return TRUE;
	}*/
	#ifndef MODULO_2 //IÑAKI
	ret = ret || categ.set(param,value);
	#endif
	#ifndef MODULO_1 //IÑAKI	
	ret = ret || grupof.set(param,value);
	#endif
	return ret;
}

/**********************************************************/

const CHAR *LangES_POS::get( const CHAR *param )
{
	const CHAR *s;
	#ifndef MODULO_2 //IÑAKI
	s=categ.get(param); if (s) return s;
	#endif
	#ifndef MODULO_1 //IÑAKI
	s=grupof.get(param); if (s) return s;
	#endif
	return NULL;
}

/**********************************************************/

/**********************************************************/

VOID LangES_POS::utt_pos( UttWS &ut )
{
	assert(created);
	#ifndef MODULO_2 //IÑAKI
	categ.utt_categ(ut);
	#endif
	#ifndef MODULO_1 //IÑAKI
	grupof.utt_gf(ut);
	#endif
}

/**********************************************************/

