/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ phmap.cpp
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
Mapeo de fonemas
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include <assert.h>
#include "uti.h"
#include "phmap.hpp"

/**********************************************************/

PhMap::PhMap( VOID )
{
	lang="eu";
	phMap_jw2iu=FALSE;
}

/**********************************************************/

BOOL PhMap::set( const CHAR *param, const CHAR *val )
{
	if (!strcmp(param,"Lang")) lang=param;
	else if (!strcmp(param,"PhMap_jw2iu")) phMap_jw2iu=str2bool(val,TRUE);
	else return FALSE;

	return TRUE;
}

/**********************************************************/

const CHAR *PhMap::get( const CHAR *param )
{
	if (!strcmp(param,"Lang")) return lang;
	else if (!strcmp(param,"PhMap_jw2iu")) return bool2str(phMap_jw2iu);
	else return NULL;
}

/**********************************************************/

VOID PhMap::utt_phmap( UttPh &u )
{
	Lix p;
	assert(u.isKindOf("UttPh"));

	if (phMap_jw2iu) {
		for (p=u.phoneFirst(); p!=0; p=u.phoneNext(p)) {
			if (u.cell(p).getPhone()==PH_j) u.cell(p).setPhone(PH_i);
			else if (u.cell(p).getPhone()==PH_w) u.cell(p).setPhone(PH_u);
		}
	}
}

/**********************************************************/
