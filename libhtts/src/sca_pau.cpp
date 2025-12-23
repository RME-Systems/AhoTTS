/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ sca_pau.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.1    22/06/01  Yon2.     Pause location change. From PrevCell 
                             to actual Cell.
0.0.0    21/06/01  Yon2.     Codificacion inicial.

======================== Contenido ========================

Inserción de pausas.

Caracter 'P' -> indica insertar pausa. La pausa se asocia a la
palabra inmediatamente anterior a la marca de comienzo. El
tipo de secuencia de escape "Pausa" no tiene marca de final.
El valor del parámetro puede ser:
(ver scapesec.hpp)
Aunque de momento sólo se insertan pausas de tipo UPAUSE_SHORT y
UPAUSE_LONG, correspondientes al valor 1 y 2 respectivamente.
El resto de pausas se mapean a UPAUSE_SHORT. Aunque no hay
ningún problema para soportarlas todas.

Caracter 'P' -> indica insertar pausa. La pausa se asocia a la
palabra inmediatamente anterior a la marca de comienzo. El
tipode secuencia de escape "Pausa" no tiene marca de final.
El valor del parámetro puede ser:
1 UPAUSE_SHORT
2 UPAUSE_LONG
3 UPAUSE_UBEGIN
4 UPAUSE_UEND
5 UPAUSE_SDECL
6 UPAUSE_SQUEST
7 UPAUSE_SEXCL
8 UPAUSE_SPAUSE
9 UPAUSE_SNEUTR


Yon2.

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
  
/**********************************************************/

#include "tdef.h"
#include "scapeseq.hpp"
#include "uttws.hpp"

#include "httsmsg.h"

/**********************************************************/


/**********************************************************/

BOOL insertPause(UttWS *ws, UttI p, INT value)
{
	BOOL retval = FALSE;
	if (value)	{
		switch(value)	{
			case 1:
				if (p) {
					ws->cell(p).setPause(UPAUSE_SHORT);
					retval = TRUE;
				}
				break;
			case 2:
				if (p) {
					ws->cell(p).setPause(UPAUSE_LONG);
					retval = TRUE;
				}
				break;
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				if (p) {
					ws->cell(p).setPause(UPAUSE_SHORT);
					retval = TRUE;
				}
				break;
			default:
#ifdef DEBUG_SCA
				htts_warn("Sca_pau.cpp: inserPause Value out of range %d", value);
#endif
				break;
		}
	}
	return retval;
} 

/**********************************************************/




