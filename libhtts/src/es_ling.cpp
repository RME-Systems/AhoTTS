/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ es_ling.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Borja Etxebarria
.............................

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
1.1.2 	 23/02/12  Inaki	speaker dependent transcription con PhTSpeaker
1.1.1 	 13/12/11  Inaki	Añadir opcion phtkatamotz para que las r al principio de palabras las pronuncie con r suave
1.1.0 	 12/07/10  Inaki	 Añadir celdas para modificar la prosodia desde el texto (proyecto Aritz) HTTS_PROSO_VAL
1.0.1	 03/10/07  Inaki     define MODULO_1 para dividir el sinte en 3 modulos
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.0.0    24/11/97  borja     Codificacion inicial.

======================== Contenido ========================
<DOC>
Metodos de {{LangES_LingP}} que gestionan el preprocesado linguistico
completo (llamando a metodos de {{LangES_Pauses}}, {{LangES_PhTrans}} y
{{LangES_Prosod}}).
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "es_lingp.hpp"
#include "uti.h"

/**********************************************************/

BOOL LangES_LingP::create( VOID )
{
	BOOL ret=TRUE;

	ret = ret && pos.create();
	#ifndef MODULE_1
	ret = ret && pauses.create();
	ret = ret && prosod.create();
	ret = ret && map.create();
	#endif
	return ret ;
}

/**********************************************************/

VOID LangES_LingP::utt_lingp( Utt *ut)
{

	assert(ut->isKindOf("UttWS"));
	pos.utt_pos(*(UttWS*)ut);

	#ifndef MODULE_1	
	pauses.utt_pauses(*(UttWS*)ut);
	#ifdef HTTS_PROSO_VAL
	pau.utt_n_val_pause(*(UttPh*)ut);//Aritz
	#endif

	assert(ut->isKindOf("UttPh"));
	phtr.utt_w2phtr(*(UttPh*)ut);

	prosod.utt_prosody(*(UttPh*)ut);

	map.utt_phmap(*(UttPh*)ut);
	#ifdef HTTS_PROSO_VAL
	pros.utt_n_val_pitch(*(UttPh*)ut);//Aritz
	
	pros.utt_n_val_rate(*(UttPh*)ut);//Aritz
	
	pros.utt_n_val_volume(*(UttPh*)ut);//Aritz
	
	pros.utt_n_val_emphasis(*(UttPh*)ut);//Aritz
	
	pros.utt_n_val_range(*(UttPh*)ut);//Aritz
	#endif
	#endif
}

/**********************************************************/
VOID LangES_LingP::utt_pos( Utt *ut )
{
	assert(ut->isKindOf("UttWS"));
	pos.utt_pos(*(UttWS*)ut);
}
/**********************************************************/
#ifdef HTTS_PROSO_VAL
VOID LangES_LingP::utt_n_val_pause(Utt * ut)//Aritz
{
	assert(ut->isKindOf("UttPh"));
	pau.utt_n_val_pause(*(UttPh*)ut);
}
/**********************************************************/
#endif
VOID LangES_LingP::utt_pauses( Utt *ut )
{
	assert(ut->isKindOf("UttWS"));
	pauses.utt_pauses(*(UttWS*)ut);
}
#ifdef HTTS_PROSO_VAL
/*************************************************************/
/*Aritz*/VOID LangES_LingP::utt_new_val(Utt *ut)
{
	assert(ut->isKindOf("UttPh"));
	pros.utt_n_val_pitch(*(UttPh*)ut);
	pros.utt_n_val_rate(*(UttPh*)ut);
	pros.utt_n_val_volume(*(UttPh*)ut);
	pros.utt_n_val_emphasis(*(UttPh*)ut);
	pros.utt_n_val_range(*(UttPh*)ut);
}
/**********************************************************/
#endif
/**********************************************************/

VOID LangES_LingP::utt_phtrans( Utt *ut )
{
	assert(ut->isKindOf("UttPh"));
	phtr.utt_w2phtr(*(UttPh*)ut);
}

/**********************************************************/

VOID LangES_LingP::utt_prosod( Utt *ut )
{
	assert(ut->isKindOf("UttPh"));
	prosod.utt_prosody(*(UttPh*)ut);
}

/**********************************************************/

VOID LangES_LingP::utt_map( Utt *ut )
{
	assert(ut->isKindOf("UttPh"));
	map.utt_phmap(*(UttPh*)ut);
}

/**********************************************************/

BOOL LangES_LingP::set( const CHAR *param, const CHAR * value )
{
	BOOL ret=FALSE;
	if (!strcmp(param,"PhTKatamotz")) {
                phtr.setPhTKatamotz(str2bool(value,TRUE));
                return TRUE;
        }

	#ifndef MODULE_1
	ret = ret || pauses.set(param,value);
	ret = ret || prosod.set(param,value);
	ret = ret || map.set(param,value);
	if (!strcmp(param,"PhTSpeaker")) {//INAKI: speaker dependent transcription
		phtr.setPhTSpeaker(value);
			return TRUE;
	}
	#endif
	return ret;
}

/**********************************************************/

const CHAR *LangES_LingP::get( const CHAR *param )
{	
	#ifndef MODULE_1
	const CHAR *s;
	if (!strcmp(param,"PhTSpeaker")) {//INAKI: speaker dependent transcription
		s=phtr.getPhTSpeaker();
		if(s) return s;
	}
	s=pauses.get(param); if (s) return s;
	s=prosod.get(param); if (s) return s;
	s=map.get(param); if (s) return s;
	#endif
	return NULL;
}

/**********************************************************/
