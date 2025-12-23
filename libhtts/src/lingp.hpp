#ifndef __LINGP_HPP__
#define __LINGP_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ lingp_hpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Borja Etxebarria
.............................

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
1.0.1	 22/06/24  Jon       Añadir Idioma externo	
1.0.1    22/06/00  richie    virtual destructor added
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.0.0    24/11/97  borja     Codificacion inicial.

======================== Contenido ========================
<DOC>
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "uttph.hpp"
#ifdef HTTS_LANG_EX
#include "wrapper.hpp"
#endif

/**********************************************************/

class LingP {
public:
	#ifdef HTTS_LANG_EX
	wrapper *miWrapper;	
	#endif

	virtual ~LingP() {};
	virtual VOID utt_lingp( Utt *u ) = 0; 
	virtual VOID utt_pauses( Utt *u ) = 0;
	virtual VOID utt_phtrans( Utt *u ) = 0;
	virtual VOID utt_prosod( Utt *u ) = 0;
	virtual VOID utt_map( Utt *u ) = 0;
	virtual VOID utt_pos( Utt *u ) = 0;
	

	virtual BOOL create( VOID ) { return TRUE; };

	virtual BOOL set( const CHAR *param, const CHAR *val ) = 0;
	virtual const CHAR *get( const CHAR *param ) = 0;
};

/**********************************************************/

#endif

