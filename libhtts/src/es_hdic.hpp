#ifndef __ES_HDIC_HPP__
#define __ES_HDIC_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1999 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU) // Euskaltel

Nombre fuente................ es_hdic.hpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion: ............... Borja Etxebarria
.............................

Version  dd/mm/aa  Autor     Comentario
-------  --------  --------  ----------
1.1.0    22/03/04  inigos	 nuevos casos
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.1.0    15/12/99  borja     version inicial

======================== Contenido ========================
<DOC>
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "hdic.hpp"

/**********************************************************/
/* bits libres para el usuario. del 0 al 22.!!
HDICQERY_ENCODE(firstbit,nbits) */

#define HDIC_QUERY_ES_SUSP HDICQUERY_ENCODE(0,2) // Sustantivos Personales
	#define HDIC_QUERY_ES_SUSP_VERB	1 // pre-post verbo (_me voy; vamonos)
	#define HDIC_QUERY_ES_SUSP_IND	2 // indiferente (_yo voy; voy _yo)
	#define HDIC_QUERY_ES_SUSP_NPV	3 // no post vervo (a _mí)

#define HDIC_QUERY_ES_DEMO HDICQUERY_ENCODE(2,2)  // Demostrativos
	#define HDIC_QUERY_ES_DEMO_NOVERB	1 // no pre verbo (_esta casa)
	#define HDIC_QUERY_ES_DEMO_IND	2 // indiferente (_esto es; _eso que no sabes)
	#define HDIC_QUERY_ES_ADJ	3 // adjetivos

#define HDIC_QUERY_ES_POSE HDICQUERY_ENCODE(4,2) // Posesivos
	#define HDIC_QUERY_ES_POSE_NOVERB	1 // no pre verbo (_mi casa)
	#define HDIC_QUERY_ES_POSE_IND	2 // indiferente (es _mío; el _mío es mejor)

#define HDIC_QUERY_ES_REL HDICQUERY_ENCODE(6,2) // Relativos
	#define HDIC_QUERY_ES_REL_AT	1 //
	#define HDIC_QUERY_ES_REL_IE	2 //

#define HDIC_QUERY_ES_INDNUM HDICQUERY_ENCODE(8,2) // Indefinidos y Numerales
	#define HDIC_QUERY_ES_INDNUM_NOVERB	1 // no pre verbo (_algún comentario)
	#define HDIC_QUERY_ES_INDNUM_IND	2 // indiferente (no es _nada; _nada es mejor)

#define HDIC_QUERY_ES_CARD HDICQUERY_ENCODE(10,2) // Numerales Cardinales
	#define HDIC_QUERY_ES_CARD_NOVERB	1 // no pre verbo (_un comentario)
	#define HDIC_QUERY_ES_CARD_IND	2 // indiferente (_dos es par; son _dos de esos)

#define HDIC_QUERY_ES_ADVE HDICQUERY_ENCODE(12,1) // Advervios
	#define HDIC_QUERY_ES_ADVER 1

#define HDIC_QUERY_ES_PREP HDICQUERY_ENCODE(13,1) // Preposiciones
	#define HDIC_QUERY_ES_PREPOS 1

#define HDIC_QUERY_ES_CONJ HDICQUERY_ENCODE(14,1) // Conjunciones
	#define HDIC_QUERY_ES_CONJUN 1

#define HDIC_QUERY_ES_VERB HDICQUERY_ENCODE(15,4) // Conjunciones
	#define HDIC_QUERY_ES_VERB_SIMP	1 // Simple (_soy)
	#define HDIC_QUERY_ES_VERB_COMP	2 // Compuesto (_he venido)
	#define HDIC_QUERY_ES_VERB_GERU	3 // GERUndios (_muriendo)
	#define HDIC_QUERY_ES_VERB_PPIO	4 // ParticiPIOs (_comido)
	#define HDIC_QUERY_ES_VERB_IR1C	5 // Infinitivos Regulares 1ª Conjugación (_cantar, _amar)
	#define HDIC_QUERY_ES_VERB_IR2C	6 // Infinitivos Regulares 2ª Conjugación (_comer, _lamer)
	#define HDIC_QUERY_ES_VERB_IR3C	7 // Infinitivos Regulares 3ª Conjugación (_emitir, _vivir)
	#define HDIC_QUERY_ES_VERB_IICC	8 // Infinitivos Regulares 3ª Conjugación (_huyir, _oigir)

#define HDIC_QUERY_ES_OTRO HDICQUERY_ENCODE(19,1) // Otros
	#define HDIC_QUERY_ES_OTRO_SUST	1 // Sustantivos (para evitar ambigüedades)
//EVA con 2 bits no es posible codificar el 4 que se usa para acronimos y no los expande. Le doy 3 bits a este campo y nos quedamos sin bits libres
//#define HDIC_QUERY_ES_NOR HDICQUERY_ENCODE(20,2)
#define HDIC_QUERY_ES_NOR HDICQUERY_ENCODE(20,3)
	#define HDIC_ANSWER_ES_NOR_ABB	1 // Abreviaturas
	#define HDIC_ANSWER_ES_NOR_ABBNF	2 // Abreviaturas No Fin (Sr. Sra.)
	#define HDIC_ANSWER_ES_NOR_UNIT 3 // Unidades
	#define HDIC_ANSWER_ES_NOR_ACR  4 // Acronimos


/**********************************************************/

class LangES_HDicDB : public HDicDB {
public: //protected:
	BOOL flagParse( const CHAR *s, HDicRef &r );
	const CHAR *getLangStr( VOID ) { return "es"; }
protected:
	HDicRef searchBin(char **exp);

	KINDOF_DECL();
};

/**********************************************************/

#endif

