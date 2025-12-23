/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ eu_pow1.cpp
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
Metodos de {{LangEU_Prosod}} que implementan diferentes modelos
de energia. Este es un modelo sencillo.
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "spl.h"
#include "eu_lingp.hpp"
#include "xx_uti.hpp"
//#define DEBUG() fprintf (stderr,"file..: %s -- line..: %d\n",__FILE__,__LINE__);
#define DEBUG()

/**********************************************************/
/* modelo de energia. Se trabaja en unidades log2 */

typedef struct {  // debe tener media 0, desviacion aprox. 1.
	DOUBLE KPowInitial;  // inicial
	DOUBLE KPowFinal;    // final
	DOUBLE KPowStress;   // incr. en acentos propios
	DOUBLE KPowEmphasis; // incr. en acentos prosodicos
	DOUBLE KPowSOU;      // incr. en Start of Utterance
	DOUBLE KPowEOU;      // incr. en End of Utterance
} UttCfg;

PRIVATE UttCfg utt_all = { 0.3, -0.3, 0.2, 0.5, 0.0, 0.0 };

/**********************************************************/

VOID LangEU_Prosod::utt_pow1(UttPh & ut)
{
	UttI p;
	LONG N;
	DOUBLE kacc, kstep, k;

	DEBUG()
	N = ut.phoneN();	// numero de fonemas
	DEBUG()
	kacc = utt_all.KPowInitial;		// energia inicial
	kstep = (N > 1) ? (utt_all.KPowFinal - kacc) / (N - 1) : 0;		// incr. entre fonemas

	for (p = ut.phoneFirst(); p != 0; p = ut.phoneNext(p)) {
		k = kacc;	// valor base
		// modificar segun stress y emphasis
		if (ut.cell(p).getStress() != USTRESS_NONE) k+=utt_all.KPowStress;
		if (ut.cell(p).getEmphasis() != UEMPHASIS_NONE) k+=utt_all.KPowEmphasis;
		ut.cell(p).setPow(k);
		kacc += kstep;	// valor base para siguiente fonema
	}
	DEBUG()
	// primera silaba de la utt. (realmente solo semisilaba inicial)
	for (p = ut.phoneFirst(); p != 0; p = ut.phoneNext(p, URANGE_SYLLABLE)) {
		ut.cell(p).setPow(utt_all.KPowSOU+ut.cell(p).getPow());
		// al llegar a una vocal, ya hemos procesado la semisilaba inicial
		if (LangEU_PhUti::phIsVowel(ut.cell(p).getPhone()))
			break;
	}
	DEBUG()
	// ultima silaba de la utt. (realmente solo semisilaba final)
	for (p = ut.phoneLast(); p != 0; p = ut.phonePrev(p, URANGE_SYLLABLE)) {
		ut.cell(p).setPow(utt_all.KPowEOU+ut.cell(p).getPow());
		// al llegar a una vocal, ya hemos procesado la semisilaba final
		if (LangEU_PhUti::phIsVowel(ut.cell(p).getPhone()))
			break;
	}

	/* pasar de db2 a lineal la energia, aplicando media {pow_mean} y varianza {pow_dev} */
	DOUBLE powd=lin2log2(pow_dev+1.0);
	for (p=ut.phoneFirst(); p!=0; p=ut.phoneNext(p))
		if(ut.cell(p).getPhone() == PH_sil) //Para reducir el ruido en difonemas del tipo s+_ mal "cortados"
			ut.cell(p).setPow(0);
		else
			ut.cell(p).setPow(pow_mean*log22lin(ut.cell(p).getPow()*powd));
	DEBUG()
}

/**********************************************************/
