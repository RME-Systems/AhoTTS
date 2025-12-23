/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ gfadi.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Inma Sardon
.............................

======================== Contenido ========================
<DOC>
GFADI.CPP para elaborar grupos funcionales verbales
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
#ifndef __GFADI_CPP__
#define __GFADI_CPP__
#include "eu_lingp.hpp"

/**********************************************************/

VOID LangEU_GF::baitadi(UttWS &u,UttI p,int *gf)
{
	if (u.cell(p).queryPOS(POS_EU_PROKLITIKO)) {
		if (!u_p_flag.phrase_last && !u_p_flag.utt_last) {
			if ( (u.cell(inf.next.p).queryPOS(POS_EU_ADI_LGN)) ||
				 (u.cell(inf.next.p).queryPOS(POS_EU_ADI_TRN))  ||
				 (u.cell(inf.next.p).queryPOS(POS_EU_ADI_JOK))  ||
				 (u.cell(inf.next.p).queryPOS(POS_EU_ATZ_ADI1))  ||
      			(u.cell(inf.next.p).queryPOS(POS_EU_ATZ_ADI2))  ||
				 (u.cell(inf.next.p).queryPOS(POS_EU_ATZ_ADI3)) ) {
						if (!strcmp(inf.act.word,"ez")) {
							if (u.cell(inf.next.p).queryPOS(POS_EU_ATZ_ADI2))
								u.cell(p).setFGrp(GF_EU_ADI);
							else
								u.cell(p).setFGrp(GF_EU_ADI_EZ);
						}
						else
							u.cell(p).setFGrp(GF_EU_ADI);
						u.cell(inf.next.p).setFGrp(GF_EU_NONE);
						indice2=2;
						encontrado=TRUE;
						*gf=u.cell(p).getFGrp();
						if (!u_p_flag.phrase_prev_last && !u_p_flag.utt_prev_last) {
							if ((u.cell(inf.nextn.p).queryPOS(POS_EU_ADI_JOK)) ||
							 (u.cell(inf.nextn.p).queryPOS(POS_EU_ATZ_ADI1)) ){
										u.cell(inf.nextn.p).setFGrp(GF_EU_NONE);
										indice2=3;
										encontrado=TRUE;
										*gf=u.cell(p).getFGrp();
							}
						} //fin comprobacion
			}
		}//fin de comprobacion
	} //fin de enclitico
}

/*********************************************************************/
VOID LangEU_GF::joklgn(UttWS &u,UttI p,int *gf)
{
	if ( (u.cell(p).queryPOS(POS_EU_ADI_JOK)) ||
	 u.cell(p).queryPOS(POS_EU_ATZ_ADI1)){
			u.cell(p).setFGrp(GF_EU_ADI);
			if (!u_p_flag.phrase_last && !u_p_flag.utt_last) {
				if ( (u.cell(inf.next.p).queryPOS(POS_EU_ADI_LGN)) ||
				 (u.cell(inf.next.p).queryPOS(POS_EU_ATZ_ADI3)) ){
							u.cell(inf.next.p).setFGrp(GF_EU_NONE);
							indice2=2;
							encontrado=TRUE;
							*gf=2;
				}
				else
						if ( (u.cell(inf.next.p).queryPOS(POS_EU_PROKLITIKO))||
						 (u.cell(inf.next.p).queryPOS(POS_EU_PRT)) ){
							if (!u_p_flag.phrase_prev_last && !u_p_flag.utt_prev_last) {
								if ( (u.cell(inf.nextn.p).queryPOS(POS_EU_ADI_LGN)) ||
									(u.cell(inf.nextn.p).queryPOS(POS_EU_ATZ_ADI3)) ){
										if (!strcmp(u.cell(inf.next.p).getWord(),"ez")) {
											u.cell(p).setFGrp(GF_EU_ADI_EZ);
											u.cell(inf.next.p).setFGrp(GF_EU_NONE);
											u.cell(inf.nextn.p).setFGrp(GF_EU_NONE);
											indice2=3;
											encontrado=TRUE;
											*gf=3;	//GF verbal negativo
										}
										else{
											u.cell(p).setFGrp(GF_EU_ADI);
											u.cell(inf.next.p).setFGrp(GF_EU_NONE);
											u.cell(inf.nextn.p).setFGrp(GF_EU_NONE);
											indice2=3;
											encontrado=TRUE;
											*gf=2;	//GF verbal no negativo

										}
								}
							}
						}
			 }
	}
//fprintf(stderr,"joklgn %s encontrado %d\n",u.cell(p).getWord(),encontrado);
}

/*********************************************************************/

VOID LangEU_GF::trn(UttWS &u,UttI p,int *gf)
{
	if ( (u.cell(p).queryPOS(POS_EU_ADI_TRN)) ||
		(u.cell(p).queryPOS(POS_EU_ATZ_ADI1)) ){
				u.cell(p).setFGrp(GF_EU_ADI);
				indice2=1;
				encontrado=TRUE;
	}
}

/*********************************************************************/

VOID LangEU_GF::jokjok(UttWS &u,UttI p,int *gf)
{
	if ( (u.cell(p).queryPOS(POS_EU_ADI_JOK)) ||
	 u.cell(p).queryPOS(POS_EU_ATZ_ADI1)){
			u.cell(p).setFGrp(GF_EU_ADI);
			if (!u_p_flag.phrase_last && !u_p_flag.utt_last) {
				if ( (u.cell(inf.next.p).queryPOS(POS_EU_ADI_JOK)) ||
				(u.cell(inf.next.p).queryPOS(POS_EU_ATZ_ADI1)) ){
						u.cell(inf.next.p).setFGrp(GF_EU_NONE);
						indice2=2;
						encontrado=TRUE;
						*gf=2;
				if (!u_p_flag.phrase_prev_last && !u_p_flag.utt_prev_last) {
						if ((u.cell(inf.nextn.p).queryPOS(POS_EU_ADI_LGN)) ||
						 (u.cell(inf.nextn.p).queryPOS(POS_EU_ATZ_ADI3)) ){
									u.cell(inf.nextn.p).setFGrp(GF_EU_NONE);
									indice2=3;
									encontrado=TRUE;
									*gf=2;
						}
					} //fin de comprobacion
				}
			} //fin de comprobacion
	}
}
#endif