/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 2004 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ es_pau2.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. inigos

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.0 	 24/09/04  inigos     Codificacion inicial.

======================== Contenido ========================
<DOC>
Metodos de {{LangES_Pauses}} que implementan el modelo "pau2" de
pausador.
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "es_lingp.hpp"
#include "xx_uti.hpp"
#include "tnor.h"

#define UMBRAL_INFERIOR 3

#ifdef HTTS_ES_PAU2

/**********************************************************/
enum {
        GF_ES_NONE=0,
	        GF_ES_MUY_BAJO,
		        GF_ES_BAJO, // 2
			        GF_ES_MEDIO,
				        GF_ES_NORMAL, // 4
					        GF_ES_ALTO,
						        GF_ES_MUY_ALTO,
							        GF_ES_EXTREMO   //7
								};
BOOL search_word(UttWS & ut, Lix &p, char * word){
	Lix w;
	for (w=ut.wordFirst(p,URANGE_PAUSE); w!=0; w=ut.wordNext(w,URANGE_PAUSE)){
		if(!strcmp(ut.cell(w).getWord(), word)){
			ut.cell(w).setPause(UPAUSE_SHORT);
			fprintf(stderr,"PAUSA_PUESTA :%s\n", word);
			return TRUE;

		}
	}
	return FALSE;
}
BOOL search_2_word(UttWS & ut, Lix &p, char * word1 , char *word2){
	Lix w;
	for (w=ut.wordFirst(p,URANGE_PAUSE); w!=0; w=ut.wordNext(w,URANGE_PAUSE)){
		if(!strcmp(ut.cell(w).getWord(), word1)){
			if(ut.wordNext(w,URANGE_PAUSE) !=NULL && !strcmp(ut.cell(ut.wordNext(w,URANGE_PAUSE)).getWord(), word2)){
				ut.cell(w).setPause(UPAUSE_SHORT);
			fprintf(stderr,"PAUSA_PUESTA 2:%s %s\n", word1, word2);
				return TRUE;
			}
		}
	}
	return FALSE;
}

VOID LangES_Pauses::utt_pau2(UttWS & ut)
{
	// primero ponemos las pausas de sentencia normales.
	uttSentencePauses(ut);

	Lix p;
	UttI gf;
	INT nivel = 0, nivel_ant = 0, nivel_bajo = 0;
	INT tnor;
	INT numpalabras;


//INAKI
	//si hay mas de 15 palabras seguidas sin pausa intentamos poner pausa despues de:
	//"y, ni, e, pero"
/*	Lix w;
	for (p=ut.pausegrFirst(); p!=0; p=ut.pausegrNext(p)){
			numpalabras=0;
		for (w=ut.wordFirst(p,URANGE_PAUSE); w!=0; w=ut.wordNext(w,URANGE_PAUSE))
			numpalabras+=1;
		//si hay más de 15 palabras intentamos meter pausa
		if(numpalabras >=15){
			//mirar si hay algun "pero"
			if(!search_word(ut,p,"pero")){
				if(!search_2_word(ut,p,"puesto", "que")){
					if(!search_2_word(ut,p,"ya", "que")){
						if(!search_word(ut,p,"porque")){
							if(!search_word(ut,p,"pues")){
								if(!search_word(ut,p,"ni")){
									search_word(ut,p,"y");

								}
							}
						}
					}
				}

			}
		}
	}
*/
//IÑIGO
	// Ponemos pausas de nivel extremo (conjunciones)
/*
	for (p=ut.pausegrFirst(); p!=0; p=ut.pausegrNext(p))
	{
		nivel_ant = 7;
		numpalabras = 0;

		for (gf=ut.fgrpFirst(p,URANGE_PAUSE); gf!=0; gf=ut.wordNext(gf,URANGE_PAUSE))
		{
			nivel = ut.cell(gf).getFGrp();

			tnor = ut.cell(gf).getTNor();

			// Si tenemos la normalización de un número no partimos
			if(tnor == UTYPENOR_NUMBER)
			{
				if(ut.cell(gf).getPause()==UPAUSE_NONE)
				{
					ut.cell(gf).setPause(UPAUSE_SHORT); // ¿¿Quizá más cortas??
					numpalabras = 0;
				}
				while (ut.fgrpNext(gf, URANGE_PAUSE)!=0 &&
					(tnor = ut.cell(ut.wordNext(gf, URANGE_PAUSE)).getTNor()) == UTYPENOR_UNKNOWN)
				{
					ut.cell(gf).setFGrp(GF_ES_BAJO); // ponemos como bajos todos los números
					gf=ut.wordNext(gf,URANGE_PAUSE);
					numpalabras++;
				}
				ut.cell(gf).setFGrp(GF_ES_BAJO); // ponemos como bajos todos los números
				nivel_ant = GF_ES_BAJO;
				continue;
			}

			if(nivel > nivel_ant)
			{
				if(nivel > GF_ES_ALTO)
				{
					if(ut.cell(gf).getPause()==UPAUSE_NONE)
					{
						ut.cell(ut.wordNext(gf,URANGE_PAUSE)).setPause(UPAUSE_LONG); // ¿¿Quizá más largas??
						numpalabras=0;
					}
				}
				else
				{
					if(nivel> GF_ES_BAJO)
					{
						if(ut.cell(gf).getPause()==UPAUSE_NONE)
						{
							if(numpalabras>UMBRAL_INFERIOR)
							{
								ut.cell(ut.wordNext(gf,URANGE_PAUSE)).setPause(UPAUSE_SHORT);
								numpalabras=0;
							}
						}
					}
				}
			}
			numpalabras++;
			nivel_ant = nivel;
		}
	}
*/
}

/**********************************************************/

#endif
