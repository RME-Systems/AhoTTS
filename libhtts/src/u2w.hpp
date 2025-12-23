#ifndef __U2W_HPP__
#define __U2W_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ u2w.hpp
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
Conversion parametros -> wave
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "tdef.h"
#include "kindof.hpp"
#include "htts_cfg.h"
#include "utt.hpp"

#ifdef HTTS_INTERFACE_WAVEMARKS
#include "mark.hpp"
#endif

/**********************************************************/

enum { U2W_CB_NOCALL=0, U2W_CB_CALL1=1, U2W_CB_BLOCKCALL=-1 };

/**********************************************************/

class Utt2Wav {
protected:
	BOOL created;
	INT flushing;
	BOOL woutack;

	DOUBLE *wav_buf;  // wave buffer
	INT wav_len;  // numero total de muestras del buffer
	INT wav_nused; // numero de muestras ocupadas
	INT wav_nready;  // n. muestras listas
	INT wav_nlen; // longitud "negativa" (por delante)

#ifdef HTTS_INTERFACE_WAVEMARKS
	Mark1DList mrkl;
	LONG wav_origin;
#endif

#ifdef HTTS_TIMEEVS
	INT timeev_current;
#endif

private:
	BOOL shiftReady( INT n, BOOL inflush );

protected:

	VOID setBufSize( INT n, INT nlen );
	BOOL xcreate( VOID );

	virtual VOID reset( VOID ) = 0;
	virtual BOOL xinput( Utt *u ) = 0;
	virtual BOOL doNext( BOOL flush ) = 0;
	virtual VOID shiftedWav( INT n );

public:
	Utt2Wav( VOID );
	virtual ~Utt2Wav();
	KINDOF_DECL();

	BOOL flush( VOID );
	BOOL input( Utt* utt );

	const DOUBLE * output( INT *len, BOOL *flush=NULL, INT mode=0, VOID *cb_n=0 );
	BOOL isFlush( VOID );
#ifdef HTTS_TIMEEVS
	INT get_timeev( VOID ) { return timeev_current; }
#endif
#ifdef HTTS_INTERFACE_WAVEMARKS
	const Mark1DList & mrkget( VOID );
	VOID mrkdel( VOID );
	BOOL outack( INT n, BOOL mrkdel=TRUE );
#else
	BOOL outack( INT n );
#endif

	virtual VOID callback( VOID * /*cb_n*/ ) { };
	virtual BOOL set( const CHAR* /*param*/, const CHAR* /*val*/ ) { return FALSE; }
	virtual const CHAR* get( const CHAR* /*param*/ ) { return NULL; }
};

/**********************************************************/

#endif
