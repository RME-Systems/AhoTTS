/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*

(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ galdeg.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Inma Sardon
				 ................. Nora Barroso (2005/04/11)

======================== Contenido ==================================================
<DOC>
GALDEG.CPP fuente para calificar grupos funcionales como galdegaia

2005/04/11-an egindako aldaketak:
	set_up_flag funtzioaren baitan aldaketa batzuk egin dira. "flag"-en ezarpena ez zen guztiz ondo egiten eta batzuetan irakurri 
	ezinak ziren tokietan informazioa irakurtzen zaiatzen zen, ondorioz ".pho" fitxategia ez zen guztiz sortzen.
</DOC>
==================================================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
#ifndef __GALDEG_CPP__
#define __GALDEG_CPP__
#include "eu_lingp.hpp"

/**********************************************************/

VOID LangEU_GF::set_inf(UttWS &u, UttI p)
{
UttI p_word_next=NULL,p_word_nextn=NULL;
	strcpy(inf.act.word,u.cell(p).getWord());
	inf.act.word_POS=u.cell(p).getPOS();
	if (p!=u.wordLast()) {
		p_word_next=u.wordNext(p);
		strcpy(inf.next.word,u.cell(p_word_next).getWord());
		inf.next.word_POS=u.cell(p_word_next).getPOS();
	}

	if ((p!=u.wordLast()) && (p_word_next!=u.wordLast())) {
		p_word_nextn=u.wordNext(p_word_next);
		strcpy(inf.nextn.word,u.cell(p_word_nextn).getWord());
		inf.nextn.word_POS=u.cell(p_word_nextn).getPOS();
	}
}

//**********************************************************************
VOID LangEU_GF::set_up_flag(UttWS &u, UttI p)
{
	if (p==u.wordLast())
	{
		u_p_flag.utt_last=1;	//detecta final de frase
		u_p_flag.utt_prev_last=0; //NORA

	}
	else	{//si no es ultimo
		u_p_flag.utt_last=0;
		inf.next.p=u.wordNext(p);	//evitar el null
		if (u.wordNext(p)==u.wordLast()) //si es penultimo
			u_p_flag.utt_prev_last=1;
		else {
			u_p_flag.utt_prev_last=0;
			inf.nextn.p=u.wordNext(u.wordNext(p)); 	//evitar el null
		}
	}

	if (u.wordIsLast(p,URANGE_PHRASE))
	{
		u_p_flag.phrase_last=1;	//detecta final de utterance
		u_p_flag.phrase_prev_last=0; //NORA
	}
	else {
		u_p_flag.phrase_last=0;
		if (u.wordIsLast(u.wordNext(p),URANGE_PHRASE))
			u_p_flag.phrase_prev_last=1;
		else
			u_p_flag.phrase_prev_last=0;
	}

	if (p==u.wordFirst())
		u_p_flag.utt_first=1;
	else
		u_p_flag.utt_first=0;

	if (u.wordIsFirst(u.wordNext(p),URANGE_PHRASE))
		u_p_flag.phrase_first=1; //detecta comienzo de frase
	else {
		u_p_flag.phrase_first=0;
		inf.prev.p=u.wordNext(p);	//evitar el null
	}
}

//**********************************************************************

VOID LangEU_GF::galdeg(UttWS &u)
{
UttI p_FGrp_last=NULL,p_FGrp_next=NULL;
UttI p=NULL;
int FGrp_next=0,FGrp_act=0;
	p_FGrp_last=u.fgrpLast();
	for (p=u.fgrpFirst();p!=0;p=u.fgrpNext(p)) {
		if (p != p_FGrp_last) {
 //			if (p!=u.wordLast()) {
//		if (u.cell(p).fgrpIsLast(p,URANGE_PHRASE)) {//INMASS ????
			if (!u.wordIsLast(p,URANGE_PHRASE)) {
				p_FGrp_next=u.fgrpNext(p);
				FGrp_next = u.cell(p_FGrp_next).getFGrp();
				FGrp_act = u.cell(p).getFGrp();
/* EVA -> Si la frase empieza por verbo, esa es la galdegaia*/	
			if (p==u.fgrpFirst())
						if (FGrp_act==GF_EU_ADI)
							u.cell(p).setFGrp(GF_EU_GALDE);
 
				if ( (FGrp_next==GF_EU_ADI) && (FGrp_act==GF_EU_ARRUN))
					if ( !(u.cell(p).queryPOS(POS_EU_LOT_JNT)) ||
						!(u.cell(p).queryPOS(POS_EU_LOT_AZK)) )
						u.cell(p).setFGrp(GF_EU_GALDE);
			}
		}
	}
}
#endif
