#ifndef __EU_HDIC_HPP__
#define __EU_HDIC_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1999 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU) // Euskaltel

Nombre fuente................ eu_hdic.hpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion: ............... Borja Etxebarria
.............................

Version  dd/mm/aa  Autor     Comentario
-------  --------  --------  ----------
2.0.1	 03/10/07  Inaki     z_T salbuespena gehitu
2.0.0		22/02/05	Nora		Transkripzio fonettikoaren salbuespenak hiztegian kodetzeko. 
										Dokumentazioa bete, azalpen batzuk sartuz.

1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.1.0    15/12/99  borja     version inicial

======================== Contenido ========================
Hitzegian daude datuak, era honetan kodetu dira, talde desberdinak eratuz:

	Talde bakoitzak (HDIC_QUERY_EU_TALDE1, HDIC_QUERY_EU_TALDE2, etabar) zenbaki bat dauka lotuta. 

	HDICQUERY_ENCODE(bit0,nbits) funtzioak ematen duen erantzuna hain zuzen ere. Funtzio honen erantzuna hau da; 
lehenengo Byte-an "bit0"-ren zenbakia ematen du eta beste 3 Byte-etan "nbit" zenbakia jartzen du.

	Talde baten barrua osagai desberdinak daude. Hau da; aditz jokatuak, loturak, aditz trinkoak.
Kodeketa guzti hau  hdic.hpp fitxategian "setbits" funtzioan erabiltzen da.


KODEKETA BERRIA: TRANSKRIPZIO FONETIKOAREN SALBUESPENAK HIZTEGIAN SARTU.
Transkripzio fonetikoaren arauetan salbuespen batzuk daude. 
Hitz zehatz batzuek nahiz eta arau zehatz bat bete beraien transkripzioa bestelakoa da. 
Informazio hau hitzegian sartu dugu, hau da, hitz batek zein salbuespen dituen. 
Adibidez arauaren arabera "l"ren transkripzioa [L] izan ordez, hitz zehatz batean [l] da. 
Informazio hau Hitzegian egotea oso erosoa eta komenia da.

Horrela, hiztegian TALDE bat sortu da HDIC_QUERY_EU_SALBTF, eta talde honen barruan salbuespen guztiak sartuko ditugu; 
HDIC_ANSWER_EU_ SALBTF_I_0_J 1 //"i" grafiaren transkripzioa [0] izan ordez [j] da
HDIC_ANSWER_EU_ SALBTF_J_0_X 2 //"j" grafiaren transkripzioa [0] izan ordez [x] da
HDIC_ANSWER_EU_ SALBTF_L_l_L 3 //"l" grafiaren transkripzioa [L] izan ordez [l] da
HDIC_ANSWER_EU_ SALBTF_N_J_N 3 //"n" grafiaren transkripzioa [J] izan ordez [n] da

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "hdic.hpp"

/**********************************************************/
/* bits libres para el usuario. del 0 al 22.!!
HDICQERY_ENCODE(firstbit,nbits) */

#define HDIC_QUERY_EU_TALDE1 HDICQUERY_ENCODE(3,3)

#define HDIC_ANSWER_EU_TALDE1_ADI_JOK 1
#define HDIC_ANSWER_EU_TALDE1_ADB  2
#define HDIC_ANSWER_EU_TALDE1_LOT_AZK  3
#define HDIC_ANSWER_EU_TALDE1_ATZ_ADI1 4
#define HDIC_ANSWER_EU_TALDE1_IOR  5

#define HDIC_QUERY_EU_TALDE2 HDICQUERY_ENCODE(6,3)

#define HDIC_ANSWER_EU_TALDE2_ADJ  1
#define HDIC_ANSWER_EU_TALDE2_DET  2
#define HDIC_ANSWER_EU_TALDE2_LOT_JNT  3
#define HDIC_ANSWER_EU_TALDE2_ATZ_IZE  4
#define HDIC_ANSWER_EU_TALDE2_ATZ_ADI2  5


#define HDIC_QUERY_EU_TALDE3 HDICQUERY_ENCODE(9,3)

#define HDIC_ANSWER_EU_TALDE3_ADI_TRN 1
#define HDIC_ANSWER_EU_TALDE3_PRT  2
#define HDIC_ANSWER_EU_TALDE3_ATZ_ADI3 3
#define HDIC_ANSWER_EU_TALDE3_IZE  4

#define HDIC_QUERY_EU_TALDE4 HDICQUERY_ENCODE(12,3)

#define HDIC_ANSWER_EU_TALDE4_ADI_LGN 1
#define HDIC_ANSWER_EU_TALDE4_PROKLITIKO  2
#define HDIC_ANSWER_EU_TALDE4_ENKLITIKO 3
#define HDIC_ANSWER_EU_TALDE4_PAU_AUR  4

#define HDIC_QUERY_EU_STR_MRK HDICQUERY_ENCODE(15,1)
#define HDIC_QUERY_EU_TF_MRK HDICQUERY_ENCODE(16,1)
#define HDIC_QUERY_EU_PAU_ATZE HDICQUERY_ENCODE(17,1)


#define HDIC_QUERY_EU_NOR HDICQUERY_ENCODE(0,2)
	#define HDIC_ANSWER_EU_NOR_ABB	1
	#define HDIC_ANSWER_EU_NOR_UNIT 2
	#define HDIC_ANSWER_EU_NOR_ACR  3

#define HDIC_QUERY_EU_DEC HDICQUERY_ENCODE(2,1)

/************KODEKETA BERRIA, TRANSKRIPZIO FONETIKOAREN SALBUESPENAK SARTZEKO***/
#define HDIC_QUERY_EU_SALBTF_I_0_J HDICQUERY_ENCODE(18,1)
#define HDIC_QUERY_EU_SALBTF_J_0_X HDICQUERY_ENCODE(19,1)
#define HDIC_QUERY_EU_SALBTF_L_l_L HDICQUERY_ENCODE(20,1)
#define HDIC_QUERY_EU_SALBTF_N_J_N HDICQUERY_ENCODE(21,1)
#define HDIC_QUERY_EU_SALBTF_Z_0_T HDICQUERY_ENCODE(22,1) //INAKI salbuespena z->T (ad. Zaragoza)

/********************************************************************************/
/*
Hasierako bit kopuru librea; 0tik 22rarte (23 bit aske).
Orain arte hartutako bit-ak; 0tik 19rarte (20 bit erabiliak)
Kodeketa berrietarako geratzen diren bit kopuru librea; 20tik 23rarte (2 bit aske)
*/
/********************************************************************************/

class LangEU_HDicDB : public HDicDB {
public:
	BOOL flagParse( const CHAR *s, HDicRef &r );
	const CHAR *getLangStr( VOID ) { return "eu"; }
protected: 
	HDicRef searchBin(char **exp);
	KINDOF_DECL();
};

/**********************************************************/

#endif

