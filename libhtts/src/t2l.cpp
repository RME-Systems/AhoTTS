/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ t2l.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version   dd/mm/aa  Autor     Proposito de la edicion
-------   --------  --------  -----------------------
0.0.12    06/07/01  Yon2.     Delayed flush support.
0.0.11    16/05/01  Yon2.     Scape Seq support.
0.0.10    04/05/01  Yon2.     Right Warning/Error info.
0.0.09    24/04/01  Yon2.     One to multiple files.
0.0.08    24/04/01  Yon2.     Multiling Support.
0.0.07    28/03/01  Yon2.     More Data Need.
0.0.06    11/02/01  Yon2.     Use create method WS.
0.0.05    05/02/01  Yon2.     Create method.
0.0.04    15/01/01  Yon2.     If no dic availabre no dic deletion.
0.0.03    08/01/01  Yon2.     prev -> prevGrp.
0.0.02    06/01/01  Yon2.     Real Time Norm.
0.0.01    04/01/01  Yon2.     Std Module I/O vars init.
0.0.00    31/10/00  Yon2.     Codificacion inicial.

======================== Contenido ========================
  En este m¢dulo se encuentran el constructor/destructor de
la clease funfamental del normalizador. As¡ como los m¢dulos
de preprocesado, salvo el busca-declinaciones.

  El m¢dulo 'preChop' se encarga de cortar palabras del stream por
el que viene el texto crudo. Separa el stream en palabras
conteniendo caracteres del mismo tipo y conservando la
cercanía que hay entre caracteres. Esto último mantiene
agrupadas palabras que forman unidades semánticas. Por
ejemplo: direcciones de correo, fechas, horas, ... en los
que se expresan los contenidos con combinación de
caracteres de distinto tipo.

  El m¢dulo 'puntChop' se encarga de separar de los patrones
signos de puntuaci¢n que se encuentren en el principio o final
del patr¢n. No as¡ los que se hallen en el m‚dio de los patrones.

  El m¢dulo 'show' muestra el estado actual de la lista en la
que se apoya el normalizador.

Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
 
/**********************************************************/

#include <stdio.h>

#include "t2l.hpp"
#include "chartype.h"
#include "httsmsg.h"

/**********************************************************/


/**********************************************************/

TextToList::TextToList( VOID)
{
	created = FALSE;

	wordStarted = FALSE;
	groupStarted = TRUE;

	//-------------------------------------------------------------------
	labelStarted = FALSE;
	//-------------------------------------------------------------------

	dicCreated = FALSE;

	dataNeed = FALSE;
	moreDataNeedAllowed = TRUE;

	nttxt = NULL;

	lastGrpProc = NULL;
	procLastGrp = FALSE;

	outAckPend = FALSE;
	flushPend = FALSE;
	ctFull = FALSE;
	delayFlush = FALSE;
}

/**********************************************************/


/**********************************************************/

TextToList::~TextToList( VOID )
{
}

/**********************************************************/


/**********************************************************/

BOOL TextToList::create(UttWS *uttWSP, HDicDB *hDicDBP)
{
  if (!created) {
	created = TRUE;
    nt = uttWSP;
    if (!nt) {
#ifdef HTTS_DEBUG
       htts_error("TextToList::create() - NULL Word String object.");
#endif
      return FALSE;
    }
  	dic = hDicDBP;
	if (dic) {
       dicCreated = TRUE;
       nt->setHDicDB(dic);
    }
    return TRUE;
  }

#ifdef HTTS_DEBUG
  htts_warn("TextToList::create() - Already created.");
#endif

  return FALSE;

}

/**********************************************************/


/**********************************************************/

VOID TextToList::show(void)
{
	CtI p;
	for (p=ct.first(); p!=NULL; p=ct.next(p))       {
		if (ct.isStart(p)) fprintf (stdout, "\n");
		fprintf(stdout, ">> %s  ", ct(p).str);
		if (ct.isStart(p)) {
			fprintf (stdout, "\t*");
			if (ct.isEscSeq(p)) fprintf(stdout, "ctrl ");
			if (ct.isRightFrg(p)) fprintf(stdout, "rf ");
			if (ct.isLeftFrg(p)) fprintf(stdout, "lf ");
			if (ct.isDekd(p)) fprintf(stdout, "dekd ");
			if (ct.isDek(p)) fprintf(stdout, "dek ");
			if (ct.isNorm(p)) fprintf(stdout, "nor ");
			if (ct.isFlush(p)) fprintf(stdout, "fsh ");
		}
		if (ct(p).pattern) fprintf (stdout, "\t [%s] ",ct(p).pattern);
		fprintf(stdout, "\n");
        }

}

/**********************************************************/


/**********************************************************/

