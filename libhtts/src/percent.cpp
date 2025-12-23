/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ percent.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.4    04/05/01  Yon2.     Right Warning/Error info.
0.0.3    04/05/01  Yon2.     Split in language dependent files.
0.0.2    25/04/01  Yon2.     Multiling support.
0.0.1    07/04/01  Yon2.     If 2nd pattern null => need more data.
0.0.0    22/03/01  Yon2.     Codificacion inicial.

======================== Contenido ========================

	Este módulo se encarga de resolver el signo de tanto por
ciento. Si aparece solo se expandirá y se acabo.
	Si aparece con un número por delante (forma castellana)
se pasará a la forma en euskara. Si aparece detrás el número
se expandirá como corresponda, y si aparece un número detrás
y otro delante será preferida la forma en euskara, es decir,
se tomarña el número que va por detrás.

		% 100 -> ehuneko hamarra

Se declina el numero.  XX-a

Nota: Puede que estemos buscando el número siguiente y este todavía
no haber entrado => falla detección. => WorkArround
Solo números enteros.

Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "percent.hpp"
#include "t2l.hpp"

#include "httsmsg.h"
 
/**********************************************************/


/**********************************************************/

/*PercentType TextToList::isPercent( CtI p)
{
	PercentType retval = PERCENT_UNKNOWN;
	pCHAR pattern;
  INT patlen;

	CtI q;
	
#ifdef HTTS_DEBUG

        if (!ct(p).pattern) htts_error("TextToList::isPercent(CtI) - Trying to read null Pattern.");
#endif



	if (ct(p).pattern) pattern = xstrdup(ct(p).pattern);

  else return retval;



  patlen = strlen(pattern);



	//Si es patron de signo de porciento -> Simbolo.
 	if (!((pattern[0] == 's') && (patlen == 1))) {
    xfree(pattern);

    return retval;

  }

	if (!((ct.getStr(p)[0] == '%') && (strlen(ct.getStr(p)) == 1))) {
    xfree(pattern);

    return retval;

  }


	xfree(pattern);



	

	//Verificamos que hay un número en el entorno.

	//Primero en Euskara, el número detrás.
	if (ct.nextGrp(p)) {
		q = ct.nextGrp(p);

#ifdef HTTS_DEBUG
    if (!ct(q).pattern) htts_warn("TextToList::isPercent(CtI) - Trying to read null 2nd Pattern.");
#endif



		if (!ct(q).pattern) {
			if (moreDataNeedAllowed) retval =	PERCENT_NEEDMOREDATA;
		}
		else	{
			pattern = xstrdup(ct(q).pattern);
			patlen = strlen(pattern);

			//Si es patron de numero tenemos un porcentaje en euskara.
			if (((pattern[0] == 'n') && (patlen == 1))) retval = PERCENT_BASQUE;
			xfree(pattern);
		}
  }

	else if (moreDataNeedAllowed) retval =	PERCENT_NEEDMOREDATA;

	if (!retval) if (ct.prevGrp(p)) {
		q = ct.prevGrp(p);


		if ((ct.getTnor(q) == UTYPENOR_NUMBER) && !(ct.isDekd(q)) )	retval = PERCENT_SPANISH;
  }




	 

	return retval;


}
*/
/**********************************************************/

