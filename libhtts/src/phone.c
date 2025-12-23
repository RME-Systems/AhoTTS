/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ phone.c
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Borja Etxebarria
.............................

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
1.1.1    04/11/13  inaki     Añadir fonemas Iparralde
1.1.0    20/10/08  inaki     Añadir fonemas Inglés
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.0.0    24/11/97  borja     Codificacion inicial.

======================== Contenido ========================
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "phone.h"
#include "uti.h"
#include "httsmsg.h"

/**********************************************************/

typedef struct {
	Phone phone;
	const CHAR *sampa;
} PhoneInfo;

/**********************************************************/

PhoneInfo phinfo[] = {
	{ PH_sil, "_" },
	{ PH_sic, "+" },
	{ PH_breath, "~" },
	{ PH_p, "p" },
	{ PH_b, "b" },
	{ PH_t, "t" },
	{ PH_d, "d" },
	{ PH_k, "k" },
	{ PH_g, "g" },
	{ PH_m, "m" },
	{ PH_n, "n" },
	{ PH_J, "J" },
	{ PH_tS,"tS" },
	{ PH_B, "B" },
	{ PH_f, "f" },
	{ PH_T, "T" },
	{ PH_D, "D" },
	{ PH_s, "s" },
	{ PH_jj,"jj" },
	{ PH_x, "x" },
	{ PH_G, "G" },
	{ PH_l, "l" },
	{ PH_L, "L" },
	{ PH_r, "r" },
	{ PH_rr,"rr" },
	{ PH_i, "i" },
	{ PH_j, "j" },
	{ PH_e, "e" },
	{ PH_a, "a" },
	{ PH_o, "o" },
	{ PH_u, "u" },
	{ PH_w, "w" },
	{ PH_S, "S" },
	{ PH_ts,"ts" },
	{ PH_dj,"gj" },
	{ PH_X, "s`" },
	{ PH_tZ,"ts`" },
	{ PH_Q, "c" },
	//{ PH_dZ,"Z" }, //BLIZZARD

	/* maria */
	{ PH_dZ_, "dZ" },
	{ PH_v, "v" },
	{ PH_z, "z" },
	{ PH_Z, "Z" },
	{ PH_h, "h" },
	{ PH_N, "N" },
	{ PH_I, "I" },
	{ PH_IA, "I@" },
	{ PH_eA, "e@" },
	{ PH_a_, "{" },
	{ PH_Q_, "Q" },
	{ PH_A_, "A:" },
	{ PH_V, "V" },
	{ PH_U, "U" },
	{ PH_UA, "U@" },
	{ PH_A, "@" },
	{ PH_i_, "i:" },
	{ PH_eI, "eI" },
	{ PH_aI, "aI" },
	{ PH_OI, "OI" },
	{ PH_AU, "@U" },
	{ PH_aU, "aU" },
	{ PH_3_, "3:" },
	{ PH_O_, "O:" },
	{ PH_u_, "u:" },
	/*********** unilex BLIZZARD2008*/
	{ PH_lw, "lw" },
	{ PH_nx, "nx" },
	{ PH_uw, "uw" },
	{ PH_lx, "lx" },
	{ PH_mx, "mx" },
	///IPARRALDE
	{ PH_aa_, "a~" },
	{ PH_e_, "e~" },
	{ PH_o_, "o~" },
	{ PH_2, "Y" },
	{ PH_y, "y" }, //iparralde, u afrancesada
	{ PH_R, "R" },
	{ PH_Jb, "J\\" },
	/* ****** */
	{ PH_none, " " }  /* este siempre el ultimo */
};

/**********************************************************/

const CHAR * phone_tosampa( Phone ph )
{
	INT i=-1;

	do {
		i++;
		if (phinfo[i].phone==ph) return phinfo[i].sampa;
	} while (phinfo[i].phone!=PH_none);
	htts_error("Phone code not known (%ld [%c])",(long)ph,(char)ph);
	return NULL;
}

/**********************************************************/

Phone phone_fromsampa( const CHAR *sampa )
{
	INT i=-1;

	do {
		i++;
		if (!strcmp(phinfo[i].sampa,sampa)) return phinfo[i].phone;
	} while (phinfo[i].phone!=PH_none);
	htts_error("SAMPA phone name not known (%s)",sampa);
	return PH_none;
}

/**********************************************************/
