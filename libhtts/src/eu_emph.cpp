/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ eu_emph.cpp
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
Metodos de {{LangEU_Prosod}} que buscan los puntos de enfasis en los
que se debe poner el acento prosodico.
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include <string.h>

#include "chset.h"
#include "eu_lingp.hpp"

/**********************************************************/
// $$$ buscar mas palabritas de estas...
// $$$ habria que usar el campo POS en vez de buscar en {atonas}...

PRIVATE CHAR *atonas[] =
{
	(char *)"el", (char *)"la", (char *)"lo", (char *)"los", (char *)"las",
	(char *)"un", (char *)"una", (char *)"unos", (char *)"unas",

	(char *)"mi", (char *)"tu", (char *)"su", (char *)"mis", (char *)"tus", (char *)"sus",
	(char *)"nuestra", (char *)"vuestra", (char *)"nuestras", (char *)"vuestras",
	(char *)"nuestro", (char *)"vuestro", (char *)"nuestros", (char *)"vuestros",

	(char *)"me", (char *)"te", (char *)"le", (char *)"nos", (char *)"os", (char *)"les", (char *)"se",
	(char *)"al", (char *)"del",

	(char *)"a", (char *)"ante", (char *)"bajo", (char *)"cabe", (char *)"con", (char *)"contra", (char *)"de",
	(char *)"desde", (char *)"en", (char *)"entre", (char *)"hacia", (char *)"hasta", (char *)"para", (char *)"por",
	(char *)"sin", (char *)"sobre", (char *)"tras", (char *)"mediante",

	(char *)"y", (char *)"e", (char *)"ni", (char *)"mas", (char *)"o", (char *)CS_S_otilde, (char *)"u", (char *)"pero", (char *)"aunque", (char *)"si",
	(char *)"porque", (char *)"que", (char *)"quien", (char *)"cuando", (char *)"como", (char *)"donde", (char *)"cual", (char *)"cuan",
	(char *)"aun", (char *)"pues", (char *)"tan", (char *)"mientras", (char *)"sino", (char *)"cada",

	NULL
};

/**********************************************************/

PRIVATE BOOL is_atona(const CHAR * word)
{
	CHAR **s = atonas;

	while (*s) {
		if (!strcmp(word, *s)) return TRUE;
		s++;
	}
	return FALSE;
}

/**********************************************************/

PRIVATE VOID word_emphasis(UttPh & u, UttI wordp)
{
	UttI w, p;

	w = u.cellFirst(wordp, URANGE_WORD); // vamos a la primera celda de la palabra

	// a las palabras atonas no les ponemos acento prosodico
	if (is_atona(u.cell(w).getWord())) return;

	// buscamos los fonemas acentuados (vocal) de esta palabra.
	// Normalmente solo habra uno, pero hacemos que puede funcionar con varios
	for (p=u.phoneFirst(w,URANGE_WORD); p!=0; p=u.phoneNext(p,URANGE_WORD)) {
		if (u.cell(p).getStress() != USTRESS_NONE)
			u.cell(p).setEmphasis(UEMPHASIS_STRESS);  // marcamos el punto de acento prosodico
	}
}

/**********************************************************/
/* Recorre la lista de palabras, marcando los focos de enfasis: todas
las palabras salvo las atonas. */

VOID LangEU_Prosod::utt_emphasis(UttPh & ut)
{
	for (UttI p=ut.wordFirst(); p!=0; p=ut.wordNext(p)) word_emphasis(ut,p);
}

/**********************************************************/
