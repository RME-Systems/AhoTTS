/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*

(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ gfpau.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Inma Sardon
.............................


======================== Contenido ========================
<DOC>
GFPAU.CPP fuente para considerar grupos funcionales pausales
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
#ifndef __GFPAU_CPP__
#define __GFPAU_CPP__
#include "eu_lingp.hpp"

/**********************************************************/


VOID LangEU_GF::invpau(UttWS &u,UttI p,int *gf)
{
int fgrp,pau=0;
					if (u.cell(p).queryPOS(POS_EU_PAUSE_AURRE)) {
						u.cell(p).setFGrp(GF_EU_PAU_AURRE);
										fgrp=u.cell(p).getFGrp();
										pau=1;
					}
					if (u.cell(p).queryPOS(POS_EU_PAUSE_ATZE)) {
							u.cell(p).setFGrp(GF_EU_PAU_ATZE);
							fgrp=u.cell(p).getFGrp();
							pau=1;
								}
				if (u.cell(p).queryPOS(POS_EU_PAUSE_AURRE) &&
				 u.cell(p).queryPOS(POS_EU_PAUSE_ATZE)) {
						u.cell(p).setFGrp(GF_EU_PAU_ARTEAN);
						fgrp=u.cell(p).getFGrp();
						pau=1;
				 }
				 if (pau==1){
						indice2=1;
						encontrado=TRUE;
						*gf=fgrp;

	if (!u_p_flag.phrase_first && !u_p_flag.utt_first) {
					if (u.cell(inf.prev.p).queryPOS(POS_EU_PAUSE_AURRE) ||
					 u.cell(inf.prev.p).queryPOS(POS_EU_PAUSE_ATZE)) {
						u.cell(inf.prev.p).setFGrp(fgrp);
						u.cell(p).setFGrp(GF_EU_NONE);
						//*indice=1; //no, en realidad es dos OJOOO!!!
						indice2=1;
						encontrado=TRUE;
						*gf=fgrp;
					}
				}
		if (!u_p_flag.phrase_last && !u_p_flag.utt_last) {
					if (u.cell(inf.next.p).queryPOS(POS_EU_PAUSE_AURRE) ||
					 u.cell(inf.next.p).queryPOS(POS_EU_PAUSE_ATZE)) {
						u.cell(p).setFGrp(fgrp);
						u.cell(inf.next.p).setFGrp(GF_EU_NONE);
						indice2=2;
						encontrado=TRUE;
						*gf=fgrp;
					}
				}
		}//fin de pau==1
}
/*******************************************************************/
VOID LangEU_GF::jnt(UttWS &u,UttI p,int *gf)
{
		//Detectar noun o adj + enklitiko
				//*** 2.- Comprobar que existe esa palabra en el dicc no etiquetada con ize
				if (u.cell(p).queryPOS(POS_EU_NONE) || u.cell(p).queryPOS(POS_EU_IZE)) {
				//*** 3.-consideraremos la palabra como nombre
				//*** 1.- Comprobar que hay una palabra etiquetada con ize en el dicc
						//noun+bat
						u.cell(p).setFGrp(GF_EU_ARRUN);

		if (!u_p_flag.phrase_last && !u_p_flag.utt_last) {
									if ( u.cell(inf.next.p).queryPOS(POS_EU_LOT_JNT)) {
										u.cell(inf.next.p).setFGrp(0);
		if (!u_p_flag.phrase_prev_last && !u_p_flag.utt_prev_last) {
												if (u.cell(inf.nextn.p).queryPOS(POS_EU_NONE) ||
												 u.cell(inf.nextn.p).queryPOS(POS_EU_IZE)) {
													u.cell(inf.nextn.p).setFGrp(0);
													indice2=3;
													encontrado=TRUE;
													*gf=1;
												 }
											}
										}
						}
				}
}
#endif
