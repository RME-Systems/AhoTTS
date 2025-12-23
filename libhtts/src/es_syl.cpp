/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ es_syl.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Borja Etxebarria
.............................

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
1.1.0    20/10/08  inaki     Corregir bug para silabificación h intercalada
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.0.0    24/11/97  borja     Codificacion inicial.

======================== Contenido ========================
<DOC>
Metodos de {{LangES_PhTrans}} que silabifican las palabras. Hace falta
para luego poner el acento en la silaba adecuada, detectar diptongos, etc.
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include <string.h>

#include "es_lingp.hpp"

/**********************************************************/
/* {wordp} debe ser el primer fonema de la palabra */

VOID LangES_PhTrans::word_syllab(UttPh & u, UttI wordp)
{
#define SETSYL(p) u.cell(p).setSyllable(TRUE)
#define PH(p)  u.cell(p).getPhone()
#define ACC(p) u.cell(p).getStress()
#define ESVOCAL(ch) (LangES_PhUti::phIsVowel(ch))
#define NOESVOCAL(ch) (! LangES_PhUti::phIsVowel(ch))
#define CCVALIDO(c1,c2) (LangES_PhUti::phIsValidCC(c1,c2))
#define NEXT(p) u.phoneNext(p,URANGE_WORD)
// SPREV: anterior, pero dentro de la silaba
#define SPREV(p) u.phonePrev(p,URANGE_SYLLABLE)

	UttI i, i2, i3;
	Phone ph, ph2, ph3;

	wordp = u.phoneFirst(wordp,URANGE_WORD);  // primer fonema

	for (i = wordp; i != 0; i = NEXT(i)) {
		ph = PH(i);		// fonema actual

		if (NOESVOCAL(ph))
			continue;	// mientras no sea vocal, avanza

		i2 = SPREV(i);	// fonema anterior en silaba

		if (!i2) {
			SETSYL(i);
			continue;
		}	// #V -> #-V  (#=comienzo palabra/silaba)

		ph2 = PH(i2);	// fonema anterior

		i3 = SPREV(i2);		// fonema anterior de anterior en silaba    

		if (NOESVOCAL(ph2)) {	// CV 

			if (!i3) {
				SETSYL(i2);
				continue;
			}	// #CV -> #-CV

			ph3 = PH(i3);
			if (ESVOCAL(ph3)) {
				SETSYL(i2);
				continue;
			}	// VCV -> V-CV
			// CCV: comprobamos si el grupo CC es valido

			if (CCVALIDO(ph3, ph2)) {
				SETSYL(i3);
				continue;
			}	// CCV -> -CCV

			SETSYL(i2);
			continue;	// CCV -> C-CV  (ver nota1 abajo)

		}
		//INAKI, comentar este caso que no tiene sentido
	/*	else if ((i2!=u.charPrev(i,URANGE_SYLLABLE)) &&
				(u.cell(u.charPrev(i,URANGE_SYLLABLE)).getChar()=='h')) {  // V+letra_inutil_h+V
			SETSYL(i);
			continue;	// V+letra_inutil_h-V
		}
	*/	else {	// VV

			if (i3) {
				ph3 = PH(i3);
				if (ESVOCAL(ph3)) {		// VVV

					if (LangES_PhUti::phIsTriptongo(ph3, ph2, ph, ACC(i3), ACC(i))) {		// VVV triptongo

						i3 = SPREV(i3);		// retrocedemos uno mas en la silaba...

						if (!i3)
							continue;	// #VVV  es triptongo

						if (NOESVOCAL(PH(i3)))
							continue;	// CVVV  es triptongo
						// VVVV -> VVV-V  salimos del if de triptongo, para evitar cuatrongos :)

					}
					SETSYL(i);
					continue;	// no era triptongo: VVV -> VV-V

				}
			}	// llegamos aqui si #VV o CVV. comprobamos diptongos

			if (LangES_PhUti::phIsDiptongo(ph2, ph, ACC(i2), ACC(i)))
				continue;	// VV es diptongo

			SETSYL(i);
			continue;	// no era diptongo: VV -> V-V

		}
	}	// end for

	if (!wordp)  // puede haber palabras sin fonemas (ej: "h")
		return;

	// ver nota2
	if (!u.cell(wordp).getSyllable()) {		// no hay silaba al comienzo?

		i = u.syllableNext(wordp, URANGE_WORD);		// vamos al comienzo de la siguiente (que sera la "primera")

		if (i)
			u.cell(i).setSyllable(FALSE);	// quitamos la frontera de silaba (si la hay)

		SETSYL(wordp);	// y la corremos al principio de la palabra (1er fonema).

	}

#undef SETSYL
#undef PH
#undef ACC
#undef ESVOCAL
#undef NOESVOCAL
#undef NEXT
#undef SPREV

/* nota1: el resto de casos, las consonantes son de silabas diferentes,
	 se podria comprobar grupos CC especiales validos al principio de palabra,
   pero la regla que hay al final ya fuera del bucle principal 
   une ristras iniciales de consonantes a la primera silaba, asi que 
   no hace falta.
   ---
   nota2: si se ha dado un caso como este: #CCCCCV... se habra 
	 silabificado asi #CCCC-CV (o asi #CCC-CCV si CC es valido),
   y la ristra inicial de consonantes no pertenecen a ninguna
   silaba, asi que ahora lo arreglamos metiendo todo el paquete
   en la primera silaba. tambien manejamos el caso #CCCCC#: */
}

/**********************************************************/
