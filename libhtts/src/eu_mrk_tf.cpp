/*
(C) 2005 TSR/Aholab - ETSII/IT Bilbo (UPV/EHU)

Iturryaren izena................ eu_mrk_tf.cpp
Lenguaia ......................... C++
Egoera  ............................Erabilgarria

Kodeketa: ...............................Nora Barroso

Bertsioa  uu/hh/ee    Egilea     Oharrak
-----------------------------------------------------------
1.0.0		2025/12/29	ISC 	Progamos cambios de versión sourceforge
0.0.2		2008/10/20	inaki		corregir problema con el diccionario
0.0.1		2005/03/16	Nora		Hitzen transkripzio fonetikoa hitzegian agertu ahal izateko


======================== Edukina ===================================================
{{LangEU_PhTrans}}prozedura, transkripzio fonetikoa hiztegitik hartzen du, "tf_mrk" markarekin markaturik dauden hitzetan.

Hiztegitik hartzen den transkripzio fonetikoa itxura hau izan beharko luke:
hasiera	ize	tf_mrk	%a.s.i.e.r.a

Fonemak desberdintzeko puntu seinua erabiltzen da. Puntuaren erabilpenaren zergaitia nabaria da;
SAMPA kode zehatz batzuk 2 edo 3 grafiekin adierzten dira, hala nola; "s´", "tS", "tz", "ts", "ts´" eta "rr". 
ezer	ior	 tf_mrk	%e.s´.e.rr
=================================================================================
*/


#include <string.h>
#include <math.h>

#include "chset.h"
#include "eu_lingp.hpp"
#include "uti.h"
#include "uttws.hpp"


#ifdef USE_TOKENIZER
UttI LangEU_PhTrans::tf_mrk_ch2ph(UttPh & u, UttI senp)
//VOID LangEU_PhTrans::tf_mrk_ch2ph(UttPh & u, UttI senp)
{

#define SETPH(p,ph)  u.cell(p).setPhone(ph)							//Fonema bat ezartzeko
#define SETSTREUS(p) u.cell(p).setStress(USTRESS_TEXT)	//Azentua ezartzeko
#define NEXT(p)  u.charNext(p,URANGE_WORD)					//Seinalatzailea elementu bat aurreratzen da, letra mailen

	//fprintf(stderr,"0\n");
	HDicDB * mydic;
	HDicRef myref;
	pCHAR exp;
	const CHAR * word;
	UttI pTF,pTF2;
	CHAR * transkrip;		
	INT	lengTF, lengWORD, dif, lengTFPKin, lengWORDPKin, numP, numTF;
	INT	i=0;
	CHAR *pch;

	mydic=new LangEU_HDicDB; //INAKI
	mydic->create(getPhTHDicName()); //INAKI
	//Hiztegian egin behar den BILAKETA
	pTF=u.charFirst(senp, URANGE_WORD);
	//mydic=u.getHDicDB(); //INAKI
	myref = mydic->search(u.cell(u.charFirst(senp,URANGE_WORD)).getWord(), &exp);
	transkrip=strdup(exp);			//Hiztegian dagoen transkripzio fonetikoaren edukina edukiko du
	word=u.cell(pTF).getWord();	//Hitza
	if (transkrip[strlen(transkrip)-1]==10) 
	{
		//fprintf(stderr,"transkrip[strlen(transkrip)-1]=10\n");
	
		transkrip[strlen(transkrip)-1]='\0';
	}
	//Behar diren luzeeren kalkulua
//0.1.0 ISC rehacemos el calculo del numero de puntos de verdad
//	numP=(INT)floor(float(lengWORD/2.0));	//Hiztegiaren transkripzio fonetikoaren fonemak puntu seinuen bitartez banandurik daude. Transkripzioaren puntu seinuen kopuruaren kalkulua.
	numP=0;
	pch=transkrip;
	while ((pch=strchr(pch,'.'))!=NULL) {
		numP++;
		pch++;
		}
	lengTFPKin=strlen(transkrip);		//Transkripzio fonetikoaren luzeera puntuekin.
	lengTF=lengTFPKin-numP; //Transkripzio fonetikoaren luzeera.
	lengWORD=strlen(word);	//Hitzaren luzeera.
	dif=lengWORD-lengTF;		//Luzeeren desberdintasuna.		
	lengWORDPKin=lengWORD+numP;	//Hitzaren luzeera puntu seinuak edukiko balitu.
	
	numTF=1;  //
	for (i=0;i<lengTFPKin;i++)
	{
		if ((numTF<lengWORD)&&(transkrip[i] != '.')) //si el n?mero de fonemas procesado es menor que el n?mero de letras y tenemos un nuevo fonema usamos la celda de la siguiente letra
		{
			pTF2 = NEXT(pTF);  			
		}
		else if((numTF!=lengWORD)&&(transkrip[i] != '.'))//Bestela gelaxka berria sortu beharko da.
		{			
			pTF=u.cellAddAfter(pTF);			
		}

	
	switch (transkrip[i]) 
	{

		case '.' : numTF++; break; 
		case 'a' : SETPH(pTF, PHEU_a);   break;
		case 'e' : SETPH(pTF, PHEU_e); break;
		case 'i' : SETPH(pTF, PHEU_i);  break;
		case 'o' : SETPH(pTF, PHEU_o);  break;
		case 'u' : SETPH(pTF, PHEU_u);  break;

		case 'j': 
			if (i!=(lengTFPKin-1))
			{
				if (transkrip[i+1]=='.')
				{
					SETPH(pTF, PHEU_iaprox); 	break;
				}
				if (transkrip[i+1]!='.')
				{
					if (transkrip[i+1]!='j')
					{
						fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
						SETPH(pTF, PHEU_iaprox); break;
					}
					else  
					{
						i++;
						SETPH(pTF, PHEU_jj);  break;
					}
				}
			}	
			else
			{
				SETPH(pTF, PHEU_iaprox); break;
			}		

		case 'w': SETPH(pTF,PHEU_uaprox); break;


		case CS_atilde: SETPH(pTF, PHEU_a); SETSTREUS(pTF); break;
		case CS_etilde: SETPH(pTF, PHEU_e); SETSTREUS(pTF); break;
		case CS_itilde: SETPH(pTF, PHEU_i); SETSTREUS(pTF); break;
		case CS_otilde: SETPH(pTF, PHEU_o); SETSTREUS(pTF); break;
		case CS_utilde: SETPH(pTF, PHEU_u); SETSTREUS(pTF); break;
		case CS_uuml:	SETPH(pTF, PHEU_u); break;


		case 'b': SETPH(pTF, PHEU_b);  break;
		
		case 'B': SETPH(pTF, PHEU_baprox);  break;
		
		case 'c': SETPH(pTF, PHEU_tt); break;

		case 'd': SETPH(pTF, PHEU_d);  break;
		
		case 'D': SETPH(pTF, PHEU_daprox);  break;
		
		case 'f': SETPH(pTF, PHEU_f);  break;

		case 'g': 
			if (i!=(lengTFPKin-1))
			{
				if (transkrip[i+1]!='.')
				{
					if (transkrip[i+1]!='j')
					{
						fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
						SETPH(pTF, PHEU_g); break;
					}
					else  
					{
						i++;
						SETPH(pTF, PHEU_dj); break;
					}
				}
/*EVA 2015/07/07
Si llegaba aquí como no habia else con el correspondiente break se ponia la gaproximante del siguiente case en vez de la g normal
*/
				else
				{
					SETPH(pTF, PHEU_g); break;
				}
			}
			else
			{
				SETPH(pTF, PHEU_g); break;
			}					
		
		case 'G': SETPH(pTF, PHEU_gaprox);  break;

		case 'k': SETPH(pTF, PHEU_k);  break;

		case 'l': SETPH(pTF, PHEU_l);	break;
		
		case 'L': SETPH(pTF, PHEU_ll);  break;

		case 'm': SETPH(pTF, PHEU_m); 	break;

		case 'n': SETPH(pTF, PHEU_n); break;
		
		case 'J': SETPH(pTF,PHEU_ntilde); 	break;

		case 'p': SETPH(pTF, PHEU_p); break;

		case 'r': 
			if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
			{
				if (transkrip[i+1]=='.')
				{
					SETPH(pTF, PHEU_r); 	break;
				}
				else if (transkrip[i+1]!='.')
				{
					if (transkrip[i+1]!='r')
					{
						fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
						SETPH(pTF, PHEU_r); 	break;
					}
					else  
					{
						i++;
						SETPH(pTF, PHEU_rr);  break;
					}
				}
			}	
			else //Azkenekoa baldin bada
			{
				SETPH(pTF, PHEU_r); 
				break;
			}		

			case 's':
				if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
				{
					if (transkrip[i+1]=='.')
					{
						SETPH(pTF, PHEU_s); break;
					}
					if (transkrip[i+1]!='.')
					{
						if (transkrip[i+1]!='`')
						{
							fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
							SETPH(pTF, PHEU_s); break;					
						}
						else  
						{
							i++;
							SETPH(pTF, PHEU_z); 	break;
						}
					}
				}	
				else //Azkeneko grafia bada
				{
					SETPH(pTF, PHEU_s); 	break;
				}		
			
			case 'S': SETPH(pTF,PHEU_x); break;

			case 't':
				if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
				{
					if (transkrip[i+1]=='.')  //"." bat baldin badu "t" grafia da.
					{						
						SETPH(pTF,PHEU_t); break;
					}
					else if (transkrip[i+1]!='.')  //"." ez bada
					{
						if ((transkrip[i+1]!='s') && (transkrip[i+1]!='S'))//hurrengo ez bada s edo S gaizki dago
						{												
							fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
							SETPH(pTF,PHEU_t); break;
						}

						else if (transkrip[i+1]=='S')  //S bada
						{							
							i++;
							SETPH(pTF,PHEU_tx); break;
						}

						else if (transkrip[i+1]=='s')  //s bada
						{
							i++;
							if (i!=(lengTF-1)) //"s"-a ez bada azkeneko grafia
							{
								if (transkrip[i+1]=='.') 	
								{									
									SETPH(pTF,PHEU_ts); break;
								}
								else if (transkrip[i+1]=='`')
								{									
									i++;
									SETPH(pTF,PHEU_tZ); break;
								}
								else
								{									
									fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
									SETPH(pTF,PHEU_ts); break;
								}
							}
							else //"s" azken grafia baldin bada
							{
								SETPH(pTF,PHEU_ts); break;
							}
						}	//"s"-ren bukaera					
					}//"tS", "ts", edo "ts´"-ren bukaerak
				}				
				
				else //Azkeneko grafia baldin bada
				{
					SETPH(pTF,PHEU_t); break;
				}		

		case 'T': SETPH(pTF, PHEU_T); break;

		case 'x': SETPH(pTF, PHEU_j);  break;

		} // switch-en bukarea

		
//0.1.0 ISC		if (i<lengWORDPKin)
		if ((numTF<lengWORD)&&(transkrip[i]!='.'))
		{
			pTF=pTF2;
		}		
	
	}//for-en bukaera

	/* Hitzaren luzeera transkripzioarena baino luzeago baldin bada, bueltatu behar den seinalatzailea 
		hitzaren azkeneko grafiara seinalatu behar du. */
	if (dif>=0) 
	{
		pTF=u.charLast(senp,URANGE_WORD);
	}
	delete mydic;//INAKI
	free(transkrip);//INAKI

return pTF; 

#undef SETPH
#undef SETSTREUS
#undef NEXT
}//main-en bukaera

#endif

