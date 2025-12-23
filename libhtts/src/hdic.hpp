#ifndef __HDIC_HPP__
#define __HDIC_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1999 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU) // Euskaltel

Nombre fuente................ hdic.hpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion: ............... Oscar Losada Abella
............................. Borja Etxebarria

Version  dd/mm/aa  Autor     Comentario
-------  --------  --------  ----------
1.1.0    01/07/00  richie    Separated mutexes (bin!=txt)
1.0.2    01/07/00  richie    Win32 Multithread
1.0.1    22/06/00  richie    POSIX Multithread
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.1.0    15/12/99  borja     primera version funcionando
0.0.0    16/11/99  Oscar     Version Inicial.

======================== Contenido ========================
<DOC>
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include <stdio.h>
#include <assert.h>
#include "tdef.h"
#include "string.hpp"
#include "kindof.hpp"
#include "htts_cfg.h"
#include "htts_cfg.h"

#ifdef __AHOTTS_MT__

#ifdef __OS_UNIX__
#include <pthread.h>
#endif
#ifdef __OS_WINDOWS__
#include <windows.h>
#include <process.h>
#endif

#endif

/**********************************************************/

typedef UINT HDicQuery;
#define HDICQUERY_ENCODE(bit0,nbits) ((((UINT)(nbits))<<8)|(((UINT)(bit0))&0xFF))
#define HDICQUERY_BIT0(query) ((query)&0xFF)
#define HDICQUERY_NBITS(query) (((query)>>8)&0xFF)

#define HDIC_QUERY_CASE HDICQUERY_ENCODE(31,1)
#define HDIC_BITS_MATCHLEN 8
#define HDIC_QUERY_MATCHLEN HDICQUERY_ENCODE(31-HDIC_BITS_MATCHLEN,HDIC_BITS_MATCHLEN)

/* bits libres para el usuario. del 0 al 22.!! */

/**********************************************************/

class HDicRef {
public:
	HDicRef( VOID ) { bits=0; }
	UINT32 bits;
protected:
	UINT __getbits(HDicQuery q);
	VOID __setbits(HDicQuery q, UINT val );

friend class HDicDB;
friend class LangES_HDicDB;
friend class LangEU_HDicDB;

public:
	UINT getquery(HDicQuery q) { return __getbits(q); }
	VOID setquery(HDicQuery q, UINT val ) { assert(HDICQUERY_BIT0(q)+HDICQUERY_NBITS(q)-1<31-HDIC_BITS_MATCHLEN); __setbits(q,val); }

friend int operator == (const HDicRef &r1, const HDicRef &r2);
friend int operator != (const HDicRef &r1, const HDicRef &r2);
};

inline int operator == (const HDicRef &r1, const HDicRef &r2) { return r1.bits==r2.bits; }
inline int operator != (const HDicRef &r1, const HDicRef &r2) { return r1.bits!=r2.bits; }

inline UINT HDicRef::__getbits(HDicQuery q)
{
	return (UINT)(~((~((UINT32)0))<<HDICQUERY_NBITS(q)) &
			(bits>>HDICQUERY_BIT0(q)));
}

inline VOID HDicRef::__setbits(HDicQuery q, UINT val )
{
	UINT32 m = ~((~((UINT32)0))<<HDICQUERY_NBITS(q));
	UINT b0 = HDICQUERY_BIT0(q);
	assert((val&m)==val);
	bits = (bits&(~(m<<b0)))|((val&m)<<b0);
}

const HDicRef HDIC_REF_NULL;

/**********************************************************/
/* cadena que identifica que el match debe ser case sensitive */

#define HDIC_STR_CASE "cs"

#define HDIC_FNAMEEXT_TXT ".dit"
#define HDIC_FNAMEEXT_BIN ".dic"

#define HDIC_MAX_STRLEN 255
#define HDIC_FTXT_STRLEN 500

/**********************************************************/

class HDicDB {
private:
	CHAR *dbname;
	FILE *fileTxt, *fileBin;

	/* variables para busquedas binarias */
	long b_base[4];
	long b_n[4];
	long b_blen[4];
	size_t b_slen[4];
	size_t b_exlen[4];

	const CHAR *tok;  // puntero al token de entrada que buscamos
	CHAR tokl[HDIC_MAX_STRLEN+1]; // token de entrada pasado a minusculas
	size_t toklen;  // longitud del token de entrada
	size_t hitlen;  // longitud del ultimo hit
	BOOL hitlonger;  // TRUE si queremos que una busqueda de hitlen>old_hitlen, FALSE para hitlen>=old_hitlen

	CHAR fBuf[HDIC_FTXT_STRLEN];  // buffer entrada del fichero
	CHAR hitBuf[HDIC_FTXT_STRLEN];  // mejor encaje hasta el momemto
	CHAR fstr_nc[HDIC_MAX_STRLEN+1];  // para meter {fstr} convertida a minusculas

	BOOL checkDBType( const CHAR *dbname, CHAR type[2], LONG v );
	VOID ftxtCreate( const CHAR *fname );
	VOID fbinCreate( const CHAR *fname );

	VOID txt2HDicRef( const CHAR *s, HDicRef &r, char **exp);
	HDicRef searchTxt(char **exp);
	long tokbsearch( const CHAR *tok, long base, long nmemb, long size );

#ifdef HTTS_IOTXT
	String txtbuf;
#endif
	friend class LangES_HDicDB;
	friend class LangEU_HDicDB;

	virtual const CHAR *getLangStr( VOID ) = 0;
	virtual BOOL flagParse( const CHAR *s, HDicRef &f ) { return FALSE; };
	virtual HDicRef searchBin(char **exp)=0;

protected:

public:

	HDicDB(VOID);
	virtual ~HDicDB();
	BOOL create( const CHAR * dbname );

	HDicRef search(const CHAR *str, char **exp=NULL);
	HDicRef searchFull(const CHAR *str, char **exp=NULL);
	static UINT query( HDicRef ref, HDicQuery q ) { return ref.getquery(q); }
	static VOID setSearchFull( HDicRef &ref ) { ref.__setbits(HDIC_QUERY_MATCHLEN,0); }

#ifdef HTTS_IOTXT
	const CHAR *hDicRefToTxt(HDicRef hDicRef);
	HDicRef txtToHDicRef(const CHAR *str);
#endif

	KINDOF_DECL();
};

/**********************************************************/

#endif

