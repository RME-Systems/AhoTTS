#ifndef __UTTDPH_HPP__
#define __UTTDPH_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ uttdph.hpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Borja Etxebarria
.............................

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
1.0.1    13/05/00  borja     update ULEVEL, docs
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
#include "dphdb.hpp"

/**********************************************************/
/* diferentes niveles a los que se puede trabajar:  Tienen que ser
compatibles con otros bits definidos en otros ficheros derivados
de {{utt}} (utt, uttph, etc)  */

enum {
	ULEVEL_DIPHONE  =0x1000,

	URANGE_DIPHONE = URANGE_UTT | ULEVEL_DIPHONE,
};

/**********************************************************/
/* La clase UttDph esta pensada para sintesis de difonemas
(polifonemas): Aparte de lo manejado por la clase de
fonemas UttPh tiene ademas un campo con el codigo de difonema,
y la utterance puede almacenar un puntero a la base de datos
de difonemas.

El campo Diphone *no* se translada automaticamente cuando se borra
una celda!

Un difonema siempre debe comenzar en la celda de su primer fonema,
o en celdas posteriores (logicamente antes del fonema siguiente). */

class UttCellDph: public UttCellPh {
public:
	BOOL isStartOf( UttLevel range ) const;
private:
	DiphoneRef dph;       // codigo difonema

public:
	UttCellDph ( VOID );
	VOID setDiphoneRef( DiphoneRef code ) { dph = code; }
	DiphoneRef getDiphoneRef( VOID ) const { return dph; }

	VOID setDummyDiphoneRef( VOID ) { dph = DphDB::getDummy(); }
	BOOL isDummyDiphoneRef( VOID ) const { return DphDB::isDummy(dph); }

	virtual VOID reset( VOID );

public:
#ifdef HTTS_IOTXT
	virtual VOID __foutput(FILE *f) const;
	virtual CHAR *__finput( CHAR *buf );

	static VOID setGlobalDphDB( DphDB * dbase ) { db=dbase; }
protected:
	static DphDB* db;
#endif

public:
	KINDOF_DECL();

};

/**********************************************************/
/* Esta clasecilla agrupa datos necesarios para recorrer
la lista UttDph segmento a segmento (un fonema se forma
con varios segmentos, que pueden estar en difonemas diferentes).
Si {phn} es -1 y {dph} no es 0, significa que el difonema es
dummy (de relleno, cuando no hay un difonema adecuado), y {ph}
apunta al fonema en cuestion.
{dph} o {ph} pueden ser 0 (NULL) en cuyo caso phn==-1 (realmente
vale con verificar si {dph} es o no 0, {ph} solo tiene
sentido si {dph} no es 0. */

class DphPhSeg {
public:
	UttI ph;   // fonema actual
	UttI dph;  // difonema actual
	INT phn;   // numero de fonema dentro del difonema
};

/**********************************************************/

class UttDph : public UttPh {
protected:
	// al crear nuevas celdas, que sean del tipo adecuado (Dph)
	UttCell * newCell( VOID );

	DphDB* dphdb;  // puntero a base de datos

public:
	UttDph( VOID );
	// Cast automatico de las celdas al tipo adecuado
	UttCellDph& cell( UttI p ) const { assert(Utt::cell(p).isKindOf("UttCellDph")); return (UttCellDph&)(Utt::cell(p)); }
	UttCellDph& operator()( UttI p ) const { return cell(p); }

	VOID setDphDB( DphDB * db ) { dphdb=db; } // acceso a base de datos
	DphDB *getDphDB( VOID ) { return dphdb; }

	UTT_LEVELSHORTCUTS(diphone,ULEVEL_DIPHONE);

	KINDOF_DECL();

#ifdef HTTS_IOTXT
	virtual VOID foutput( FILE *f ) const;
	virtual BOOL finput( FILE *f );
#endif

	VOID segFirst( DphPhSeg & si );
	VOID segNext( DphPhSeg & si );

};

/**********************************************************/

#endif

