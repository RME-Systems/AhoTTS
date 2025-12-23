/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ httsmsg.c
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
Gestion de mensajes de error, warning, debug.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include <stdio.h>
#include <stdlib.h>

#define __HTTSMSG_NOEXTERNS__
#include "httsmsg.h"

/**********************************************************/

HTTSMsgFunc * __htts_error=NULL;
HTTSMsgFunc * __htts_warn=NULL;

/**********************************************************/

VOID htts_set_error_func( HTTSMsgFunc *f )
{
	__htts_error=f;
}

/**********************************************************/

VOID htts_set_warn_func( HTTSMsgFunc *f )
{
	__htts_warn=f;
}

/**********************************************************/

VOID htts_error( const CHAR *fmt, ... )
{
	va_list argptr;
	va_start(argptr, fmt);

	if (__htts_error) __htts_error(fmt,argptr);
	else {
		fprintf(stderr,"[aHoTTS error]: ");
		vfprintf(stderr, fmt, argptr);
		fprintf(stderr,"\n");
	}

	va_end(argptr);
	exit(1);
}

/**********************************************************/

VOID htts_cerror( INT condition, const CHAR *fmt, ... )
{
	if (condition) {
		va_list argptr;
		va_start(argptr, fmt);

		if (__htts_error) __htts_error(fmt,argptr);
		else {
			fprintf(stderr,"[aHoTTS error]: ");
			vfprintf(stderr, fmt, argptr);
			fprintf(stderr,"\n");
		}

		va_end(argptr);
		exit(1);
	}
}

/**********************************************************/

VOID htts_warn( const CHAR *fmt, ... )
{
	va_list argptr;
	va_start(argptr, fmt);

	if (__htts_warn) __htts_warn(fmt,argptr);
	else {
		fprintf(stderr,"[aHoTTS warn]: ");
		vfprintf(stderr, fmt, argptr);
		fprintf(stderr,"\n");
	}

	va_end(argptr);
}

/**********************************************************/

#ifdef HTTS_DEBUGxxx
VOID htts_debug( INT lvl, const CHAR *fmt, ... )
{
	va_list argptr;

	fprintf(stderr,"[aHoTTS debug %ld]: ",(long)lvl);
	va_start(argptr, fmt);
	vfprintf(stderr, fmt, argptr);
	va_end(argptr);
	fprintf(stderr,"\n");
}
#endif

/**********************************************************/

