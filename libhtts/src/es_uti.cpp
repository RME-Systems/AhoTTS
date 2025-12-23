/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ es_uti.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Borja Etxebarria
.............................

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
1.1.0    21/06/10  Iñaki     añadir aproximantes en las combinaciones de consonantes válidas dentro de una misma sílaba
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.0.0    24/11/97  borja     Codificacion inicial.

======================== Contenido ========================
<DOC>
Metodos de {{LangES_PhUti}}, que se utilizan por otros
metodos de las clases {{LangES_???}}: detectan grupos consonanticos
validos, detectan diptongos, etc.
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "xx_uti.hpp"

#include "es_lingp.hpp"

/**********************************************************/

BOOL LangES_PhUti::phIsVowel(Phone ph)
{
	return ((ph == PHES_a) || (ph == PHES_e) || (ph == PHES_i)
		|| (ph == PHES_o) || (ph == PHES_u));
}

/**********************************************************/

BOOL LangES_PhUti::phIsValidCC(Phone ph1, Phone ph2)
{
	Phone lset[] = {
		PHES_baprox, PHES_b, PHES_f, PHES_gaprox, PHES_g, PHES_k, PHES_p, PHES_t, 0};//INAKI
		//PHES_b, PHES_f, PHES_g, PHES_k, PHES_p, PHES_t, 0};
	Phone rset[] = {
		PHES_baprox,PHES_b, PHES_daprox, PHES_d, PHES_f, PHES_gaprox, PHES_g, PHES_k, PHES_p, PHES_t, 0};//INAKI
		//PHES_b, PHES_d, PHES_f, PHES_g, PHES_k, PHES_p, PHES_t, 0};

	if (ph2 == PHES_l)
		return phSetContains(lset, ph1);	// grupos con la l

	if (ph2 == PHES_r)
		return phSetContains(rset, ph1);	// grupos con la r

	return FALSE;
}

/**********************************************************/
/* diptongos: fuerte-debil, debil-fuerte, debil-debil,
   [aeo+iu] [iu+eao] [i+u] [u+i], salvo si la debil esta
   acentuada (iu, ui, si la primera esta acentuada no lo 
   tomo como diptongo). */

BOOL LangES_PhUti::phIsDiptongo(Phone ph1, Phone ph2, Stress acc1, Stress acc2)
{
	BOOL iu1, iu2;

	iu1 = (ph1 == PHES_i) || (ph1 == PHES_u);
	iu2 = (ph2 == PHES_i) || (ph2 == PHES_u);

	if (iu1 && !iu2 && (acc1==USTRESS_NONE))
		return TRUE;	// df o df'

	if (!iu1 && iu2 && (acc2==USTRESS_NONE))
		return TRUE;	// fd o f'd

	if (iu1 && iu2 && (acc1==USTRESS_NONE))
		return TRUE;	//  dd o dd'

	return FALSE;;
}

/**********************************************************/
/* triptongos: debil-fuerte-debil: [iu+aeo+iu], salvo si
   alguna debil esta acentuada */

BOOL LangES_PhUti::phIsTriptongo(Phone ph1, Phone ph2, Phone ph3,
	Stress acc1, Stress acc3)
{
	BOOL iu1, iu2, iu3;

	iu1 = (ph1 == PHES_i) || (ph1 == PHES_u);
	iu2 = (ph2 == PHES_i) || (ph2 == PHES_u);
	iu3 = (ph3 == PHES_i) || (ph3 == PHES_u);

	if (iu1 && !iu2 && iu3 && (acc1==USTRESS_NONE) && (acc3==USTRESS_NONE))
		return TRUE;

	return FALSE;
}

/**********************************************************/
/* {devuelve} lindice a  vocal de la silaba. En diptongos y 
   demas, a la vocal fuerte, o a la acentuada si todas son debiles (iu),
   o a la segunda si ninguna esta acentuada todavia */

UttI LangES_PhUti::syllable_vowel(UttPh & u, UttI syl)
{
	UttI i, v;
	Phone p;

	i = u.phoneFirst(syl, URANGE_SYLLABLE);		// vamos al principio de silaba

	v = 0;

	while (i) {
		p = u.cell(i).getPhone();
		if ((p == PHES_a) || (p == PHES_e) || (p == PHES_o))
			return i;	// si la vocal es fuerte, ya esta!

		if (((p == PHES_i) || (p == PHES_u)) &&		// si es debil y...
			 ((!v) || (u.cell(v).getStress() == USTRESS_NONE)))		// ... es la primera o la primera no estaba acentuada

			v = i;	// posicion de ultima vocal (debil) encontrada

		i = u.phoneNext(i, URANGE_SYLLABLE);
	}
	return v;
}

/**********************************************************/
/* como syllable_vowel, pero cuando no hay vocal, en vez de
NULL devuelve el mismo lindice {syl} */

UttI LangES_PhUti::syllable_xvowel(UttPh & u, UttI syl)
{
	UttI v =syllable_vowel(u,syl);
	return v?v:syl;
}

/**********************************************************/
