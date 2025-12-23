#ifndef __XX_UTI_HPP__
#define __XX_UTI_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ xx_uti.hpp
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
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "uttph.hpp"

/**********************************************************/
/* Puntos con pitch indefinidos, se rellenan con este valor */

#define FillValue -1

/**********************************************************/

BOOL phSetContains(Phone * lset, Phone ph);
VOID uttDefaultSentence( UttWS &ut );
VOID uttSentencePauses( UttWS &ut );
VOID uttPthLin( UttPh &ut );
VOID uttPausePh(UttPh & u);

/**********************************************************/

#endif

