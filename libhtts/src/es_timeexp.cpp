/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ es_timeexp.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.1.1	 07/05/03  inigos	 Cuartos, medias y menos...
0.1.0    19/11/02  inigos    Adaptación al castellano.
0.0.6    04/05/01  Yon2.     Rename filename to eu_timeexp.cpp.
0.0.5    24/04/01  Yon2.     Multiling support.
0.0.4    23/12/00  Yon2.     0.0.3 & pasar trabajo al declinador.
0.0.3    13/12/00  Yon2.     Hora punta & declinada.
0.0.2    11/12/00  Yon2.     Soporte tipo de normalizacion.
0.0.1    30/11/00  Yon2.     Corregir hamaikaAK.
0.0.0    24/11/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

  Este m¢dulo se encarga de expandir horas y lapsos de
tiempo. Todas las horas se normalizan a formato de 12 horas.
Las que superan las 12 horas se acompa¤an de la franja
del d¡a. Ej:
14:12 -> Dos y doce minutos de la tarde.

Dice los cuartos e y media, además de decir "menos..."

  
inigos
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "stdlib.h"
#include "stdio.h"

#include "es_t2l.hpp"
#include "symbolexp.h"
#include "choputi.h"

/**********************************************************/

CHAR es_hourStr[]="horas";
CHAR es_minStr[]="minutos";
CHAR es_secStr[]="segundos";

CHAR es_cuarStr[]="cuarto";
CHAR es_medStr[]="media";

CHAR es_yminStr[]="y";
CHAR es_menosStr[]="menos";

CHAR es_deTimeStr[]="de";
CHAR es_laTimeStr[]="la";
CHAR es_delTimeStr[]="del";

CHAR es_mornStr[]="mañana";
CHAR es_midStr[]="mediodia";
CHAR es_evenStr[]="tarde";
CHAR es_nightStr[]="noche";

/**********************************************************/


/**********************************************************/
CtI LangES_TextToList::exptimeHM(CtI p)
{
	INT hours;
	INT minutes;
	CtI q;
	INT stat, emotion, emo_intensity;
	BOOL manhana=TRUE;;
	BOOL menos=FALSE;;

	stat = ct.getStatus(p);
	emotion = ct.getEmotion(p);
	emo_intensity = ct.getEmo_int(p);

	hours = chu_str2num(ct.cell(p).str);
	p = ct.next(p);
	p = ct.next(p);
	minutes = chu_str2num(ct.cell(p).str);
	q=p;

	if (minutes > 30)  // para decir menos....
	{
		hours++;
		menos = TRUE;
	}

	if (hours > 12)
	{
  		hours-=12;
		manhana = FALSE;
	}
	
	if(hours==1)
	{
		p = ct.insafter(p, (char *)"una", FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
	}
	else
	{
		if (hours == 0) // para no decir las "cero y cuarto de la noche"
		{
			hours += 12;
			manhana = FALSE;
			p = upTo99(hours, p, TRUE);
		}
		else
		{
			p = upTo99(hours, p, TRUE);
		}
	}
    if (minutes)
	{
		if(menos)
		{
			p = ct.insafter(p, es_menosStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			minutes = 60 - minutes;
		}
		else
		{
			p = ct.insafter(p, es_yminStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
		}

		if(minutes==1)
		{
			p = ct.insafter(p, (char *)"un", FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			p = ct.insafter(p, (char *)"minuto", FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
		}
		else
		{
			switch(minutes)
			{
			case 15:
					p = ct.insafter(p, es_cuarStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
					break;
			case 30:
					p = ct.insafter(p, es_medStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
					break;
			default:
					p = upTo99(minutes, p, TRUE);
					p = ct.insafter(p, es_minStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
					break;
			}
		}
	}

	if (!manhana)
	{
 		if (hours < 2)
		{
			p = ct.insafter(p, es_delTimeStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			p = ct.insafter(p, es_midStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
		}
		else
		{
	    	if (hours < 9)
			{
				p = ct.insafter(p, es_deTimeStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
				p = ct.insafter(p, es_laTimeStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
				p = ct.insafter(p, es_evenStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			}
			else
			{
				p = ct.insafter(p, es_deTimeStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
				p = ct.insafter(p, es_laTimeStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
				p = ct.insafter(p, es_nightStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			}
		}
	}
	else
	{
		if(hours==12)
		{
			p = ct.insafter(p, es_delTimeStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			p = ct.insafter(p, es_midStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
		}
		else
		{
			p = ct.insafter(p, es_deTimeStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			p = ct.insafter(p, es_laTimeStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			p = ct.insafter(p, es_mornStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
		}
	}
	
	q=ct.next(q);
	ct.setPatternForce(q, (char *)"l");
	ct.setStatus(q, stat);
	ct.setTnor(q, UTYPENOR_TIME);

	q=ct.prevGrp(q);
	q=ct.delGrp(q);
		
	return q;
}

/**********************************************************/


/**********************************************************/
CtI LangES_TextToList::exptimeHMS(CtI p)
{
	INT hours;
	INT minutes;
	INT seconds;
	CtI q;
	INT stat,emotion, emo_intensity;

	stat = ct.getStatus(p);
	emotion = ct.getEmotion(p);
	emo_intensity = ct.getEmo_int(p);

	hours = chu_str2num(ct.cell(p).str);
	p = ct.next(p);
	p = ct.next(p);
	minutes = chu_str2num(ct.cell(p).str);
	p = ct.next(p);
	p = ct.next(p);
	seconds = chu_str2num(ct.cell(p).str);
	q = p;

	switch(hours)
	{
		case 1:
			p = ct.insafter(p, (char *)"una", FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			p = ct.insafter(p, (char *)"hora", FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			break;

		default:
			p = upTo99(hours, p, TRUE);
			p = ct.insafter(p, es_hourStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			break;
		}


	switch(minutes)
	{
		case 1:
			p = ct.insafter(p, (char *)"un", FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			p = ct.insafter(p, (char *)"minuto", FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			break;

		default:
			p = upTo99(minutes, p, TRUE);
			p = ct.insafter(p, es_minStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
 			break;
		}

	switch(seconds)
	{
		case 1:
			p = ct.insafter(p, (char *)"un", FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			p = ct.insafter(p, (char *)"segundo", FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
			break;

		default:
			p = upTo99(seconds, p, TRUE);
			p = ct.insafter(p, es_secStr, FALSE, emotion, emo_intensity);//inaxio-> emotion eta emo_intensity gehitu
 			break;
	}

	q=ct.next(q);
	ct.setPatternForce(q, (char *)"l");
	ct.setStatus(q, stat);
	ct.setTnor(q, UTYPENOR_TIME);

	q=ct.prevGrp(q);
	q=ct.delGrp(q);

	return q;
}

/**********************************************************/

