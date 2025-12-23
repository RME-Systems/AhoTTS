/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ virtual.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.1    07/05/01  Yon2.     Added isGroupDekd.
0.0.0    04/05/01  Yon2.     Codificacion inicial.

======================== Contenido ========================
  Este archivo contiene algunas de las funciones virtuales
que se definen en la clase "TextToList". Son funciones vac¡as
en esta clase y deber n ser redefinidas en una clase
dependiente de "TextToList" y para un lenguaje espec¡fico.

  Deben existir, ya que el m‚todo Input y alg£n otro las
llama.


Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
 
/**********************************************************/

#include "t2l.hpp"
#include "httsmsg.h"


/***********************************************************************/


/***********************************************************************/

AbbAcrUniType TextToList::isAbbAcrUni( CtI p )
{

#ifdef HTTSDEBUG
	htts_error("TextToList::isAbbAcrUni -> You must define your own language dependent function.");
#endif

	return AAU_UNKNOWN;
}

/***********************************************************************/

DateType TextToList::isDate(CtI p)
{

#ifdef HTTSDEBUG
	htts_error("TextToList::isDate -> You must define your own language dependent function.");
#endif

	return DATE_UNKNOWN;
}


/***********************************************************************/

INT TextToList::ct2nt(const CHAR *str, BOOL flush )
{

#ifdef HTTSDEBUG
	htts_error("TextToList::ct2nt -> You must define your own language dependent function.");
#endif

	return 0;
}

/***********************************************************************/


/***********************************************************************/

INT  TextToList::ct2nt(BOOL flush)
{

#ifdef HTTSDEBUG
	htts_error("TextToList::ct2nt -> You must define your own language dependent function.");
#endif

	return 0;
}

/***********************************************************************/


/***********************************************************************/

CtI TextToList::normal(VOID)
{

#ifdef HTTSDEBUG
	htts_error("TextToList::normal -> You must define your own language dependent function.");
#endif

	return NULL;
}

/***********************************************************************/


/***********************************************************************/

BOOL TextToList::isPronun(CtI p)
{

#ifdef HTTSDEBUG
	htts_error("TextToList::isPronun -> You must define your own language dependent function.");
#endif

	return FALSE;
}

/***********************************************************************/

/***********************************************************************/

BOOL TextToList::isGroupDecd(CtI p)
{

#ifdef HTTSDEBUG
	htts_error("TextToList::isGroupDecd -> You must define your own language dependent function.");
#endif

	return FALSE;
}

/***********************************************************************/
/***********************************************************************/

INT WdChop::getchtype(CHAR c)
{

#ifdef HTTSDEBUG
	htts_error("TextToList::getchtype -> You must define your own language dependent function.");
#endif

	return 0;
}

/***********************************************************************/

