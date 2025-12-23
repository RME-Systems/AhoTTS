/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ eu_pos.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Inma Sardon
.............................


======================== Contenido ========================
<DOC>
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#ifndef __EU_POS_CPP__
#define __EU_POS_CPP__
#include "eu_lingp.hpp"

LangEU_POS::LangEU_POS( VOID )
{
	created=FALSE;
}

/**********************************************************/

LangEU_POS::~LangEU_POS( VOID )
{
}


/**********************************************************/

BOOL LangEU_POS::create( VOID )
{
	BOOL ret=TRUE;
	created=TRUE;
	ret = ret && categ.create();
	ret = ret && grupof.create();

	return ret ;
}

/**********************************************************/

BOOL LangEU_POS::set( const CHAR *param, const CHAR * value )
{
	BOOL ret=FALSE;
/*	if (!strcmp(param,"PhTSimple")) {
		phtr.setPhTSimple(str2bool(value,TRUE));
		return TRUE;
	}*/
	ret = ret || categ.set(param,value);
	ret = ret || grupof.set(param,value);
	return ret;
}

/**********************************************************/

const CHAR *LangEU_POS::get( const CHAR *param )
{
	const CHAR *s;
	s=categ.get(param); if (s) return s;
	s=grupof.get(param); if (s) return s;
	return NULL;
}



/**********************************************************/

VOID LangEU_POS::utt_pos( UttWS &ut )
{
	assert(created);
	categ.utt_categ(ut);
	grupof.utt_gf(ut);
}

#endif


