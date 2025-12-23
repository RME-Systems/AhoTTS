/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ eu_w2ph.cpp
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
Metodos de {{LangEU_PhTrans}} para gestionar la conversion de palabras
a fonemas (pasando por letras).
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

//#define DEBUG() fprintf (stderr,"file..: %s -- line..: %d\n",__FILE__,__LINE__);
#define DEBUG()
#include "eu_lingp.hpp"
#include "xx_uti.hpp"

/**********************************************************/

VOID LangEU_PhTrans::utt_w2phtr(UttPh & ut)
{
	UttI wo;
	DEBUG()
	// primero expandimos las palabras a letras
	for (wo=ut.wordFirst(); wo!=0; ) {
		UttI wn=ut.wordNext(wo);  // pre-fetch de next. mas rapido porque aun no esta expandido
		ut.word2Char(wo);
		wo=wn;
	}
	DEBUG()
	// asegurar que hay alguna sentencia
	uttDefaultSentence(ut);
	DEBUG()
	// ahora, pausa a pausa, convertir letra -> fonema
	for (UttI se=ut.pausegrFirst(); se!=0; se=ut.pausegrNext(se))
		pausegr_ch2ph(ut, se);
	DEBUG()
	// silabificar palabra a palabra
	for (wo=ut.wordFirst(); wo!=0; wo=ut.wordNext(wo))
		word_syllab(ut, wo);
	DEBUG()
	iu2jw(ut); // detecta diptongos/triptongos
	DEBUG()
#ifdef USE_TOKENIZER
	//construir grupos acentuales,se trabaja de fgrp en fgrp
	for (UttI fg=ut.fgrpFirst(); fg!=0; fg=ut.fgrpNext(fg,URANGE_UTT))
		fgrp2agrp(ut,fg);
	//acentuar los grupos acentuales que no lo esten ya
	for (UttI ag=ut.agrpFirst(); ag!=0; ag=ut.agrpNext(ag)){
		DEBUG()
		if (!agrp_stressed(ut,ag)) agrp_stress(ut, ag);  //acentuar
		//no se else agrp_stress_text(ut,ag);//
		DEBUG()
	}
#else
		// acentuar palabras que no lo esten ya
	for (wo=ut.wordFirst(); wo!=0; wo=ut.wordNext(wo))
		if (!word_stressed(ut,wo)) word_stress(ut, wo);  //acentuar
#endif
	uttPausePh(ut);  // fonemas de silencio en pausas
}

/**********************************************************/
