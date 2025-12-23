
/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ numhilvl.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.6    04/05/01  Yon2.     Right Warning/Error info.
0.0.5    04/05/01  Yon2.     Split in language dependent files.
0.0.4    25/04/01  Yon2.     Multiling support.
0.0.3    22/03/00  Yon2.     Point & 2. resolv
0.0.2    22/03/00  Yon2.     Need More Data.
0.0.1    11/12/00  Yon2.     Soporte tipo de normalizacion.
0.0.0    19/11/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

M¢dulo expansor de n£meros a nivel alto. Expande cardinales
y ordinales. Se apoya en el m¢dulo de expansi¢n num‚rica de
nivel bajo.

Nota: Faltan los casos de ordinal con el punto como "right
fragment". Cardinales con el punto como separador de miles,
cardinales con separador decimal. O cardinales con signo.
Se deja por no ser prioritario en este momento.


Yon2.

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
  
/**********************************************************/
#include <stdio.h>

#include "t2l.hpp"
#include "choputi.h"

#include "httsmsg.h"
#include "chset.h"

/**********************************************************/



/**********************************************************/
/*
NumType TextToList::isNum(CtI p)
{
	NumType retval = NUM_UNKNOWN;
	NumType numTemp = NUM_UNKNOWN;
	pCHAR pattern;
	INT patlen;
	CtI q;
	CHAR puntt;

#ifdef HTTS_DEBUG
        if (!ct(p).pattern) htts_error("TextToList::isNum() - Trying to read null Pattern.");
#endif
	if (ct(p).pattern) pattern = xstrdup(ct(p).pattern);
	else return retval;
	
	patlen = strlen(pattern);

	//Si no es uno de los patrones de numero.
 	if ((pattern[0] == 'n') && (patlen == 1)) numTemp = NUM_CARD;
	if (patlen == 2)
		 if ((pattern[0] == 'n') && (pattern[1] == 'p')) numTemp = NUM_ORD;
	if (numTemp == NUM_CARD)
	{
  		if ( ct.nextGrp(p) )
		{
			if (ct.isRightFrg(ct.nextGrp(p)))
			{
			  	q = ct.nextGrp(p);
		        if ((strlen(ct(q).pattern) == 1) && ((ct(q).pattern)[0] == 'p'))
				{
		        	if (((ct(q).str)[0] == '.') && (strlen(ct(q).str) == 1))
					{
						if (ct.nextGrp(q))
						{
							q=ct.nextGrp(q);
							if (ct(q).pattern)
							{
								if ((ct(q).pattern)[0] == 'l')
								{
									if (ct.getStr(q)[0] == chset_ToLower(ct.getStr(q)[0]) )
									{
										numTemp = NUM_ORD_PUNT;
									}
								}
							}
							else if (moreDataNeedAllowed) if (!ct.nextGrp(q)) numTemp = NUM_NEEDMOREDATA;
						}
						else if (moreDataNeedAllowed) if (!ct.nextGrp(q)) numTemp = NUM_NEEDMOREDATA;
	          		}
					if (((ct(q).str)[0] == '.') && (strlen(ct(q).str) > 1))
					{
						numTemp = NUM_ORD_PUNT;
					}

					if (((ct(q).str)[0] == 'º'))	numTemp = NUM_ORD_ES_O;
					if (((ct(q).str)[0] == 'ª'))	numTemp = NUM_ORD_ES_A;
				}
				else if ((strlen(ct(q).pattern) > 1) && ((ct(q).pattern)[0] == 'p'))
				{
					if ((ct(q).str)[0] == '.')	numTemp = NUM_ORD_PUNT;
				}
      		}
		}
	}
	xfree(pattern);

	
	//Chequeamos que los separadores sean válidos.
	if (numTemp == NUM_ORD)
	{
		q=ct.next(p);
		if (strlen(ct(q).str) != 1) return retval;
		puntt = (ct(q).str)[0];
		if (puntt != '.') return retval;
	}

	//Verificamos que el n£mero no tiene m s de 18 cifras.
	if ( (numTemp != NUM_UNKNOWN) && (numTemp != NUM_NEEDMOREDATA) )
		if (strlen(ct.getStr(p)) >18) numTemp = NUM_TOO_LARGE;

	retval = numTemp;
		 
	return retval;
}*/
/**********************************************************/

/**********************************************************/



