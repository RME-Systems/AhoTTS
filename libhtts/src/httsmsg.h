#ifndef __HTTSMSG_H__
#define __HTTSMSG_H__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ httsmsg.h
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C
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
Gestion de mensajes de error, warning, debug.
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include <stdarg.h>
#include "tdef.h"
#include "htts_cfg.h"

/**********************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/

VOID htts_error( const CHAR *fmt, ... );
VOID htts_warn( const CHAR *fmt, ... );

#ifdef HTTS_DEBUGxxx
VOID htts_debug( INT lvl, const CHAR *fmt, ... );
#endif

/**********************************************************/

typedef VOID HTTSMsgFunc( const CHAR *fmt, va_list arglist );

VOID htts_set_error_func( HTTSMsgFunc *f );
VOID htts_set_warn_func( HTTSMsgFunc *f );

#ifndef __HTTSMSG_NOEXTERNS__
extern HTTSMsgFunc * __htts_error;
extern HTTSMsgFunc * __htts_warn;
#endif

/******************************************************************/

#ifdef __cplusplus
}  /* extern "C" */
#endif

/**********************************************************/

#endif
