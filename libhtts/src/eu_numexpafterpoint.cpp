/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 2005 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ numexp.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollando
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Larraitz

Version  dd/mm/aa  Autor     Proposito de la edicion
-------------------------------------------------------------
0.0.0    19/04/05  Larraitz   koma ondorengo zenbakiak irakurri

======================== Contenido ========================

  

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
  
/**********************************************************/

#include <stdio.h>

#include "eu_t2l.hpp"
#include "symbolexp.h"
#include "choputi.h"




/**********************************************************/

/**********************************************************/

CtI LangEU_TextToList::expnumafterpoint(CtI q)
{
  
	BOOL numzone[6]={FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};
    BOOL etaPend = FALSE;
	INT len;
	INT i=0;
	INT numceros=0;
	pCHAR temp, input;


	input = ct.getStr(q);
	len = strlen(input);

	while(i<len && input[i]== '0')
	{
		numceros++;
		i++;
	}
	if(i != 0)
	{
		if(i == len) 
			numceros--;
	}
	else
	{
		i++;
	}


	q = expnum(q);
	q = ct.del(q);

	ct.setPatternForce(q, (char *)"l");
	//ct.setStatus(q, 1);
	//ct.setTnor(q, UTYPENOR_NUMBER);

	for(i=1; i<= numceros; i++)
	{
		q = ct.insbefore(q, (char *)"zero", FALSE);  // para leer 007
	}

	ct.setPatternForce(q, (char *)"l");
	//ct.setStatus(q, 1);
	//ct.setTnor(q, UTYPENOR_NUMBER);
	
	return q;

}
/**********************************************************/





