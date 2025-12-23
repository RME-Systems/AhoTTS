/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ callback.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.2    04/05/01  Yon2.     Right Warning/Error info.
0.0.1    25/04/01  Yon2.     Multiling support.
0.0.0    15/01/01  Yon2.     Codificacion inicial.

======================== Contenido ========================

  Se implementa la funci¢n generica de CallBack.
  Es una funcion virtual que no hace nada.
  La tendr  que redefinir el usuario (para eso es virtual).
  Esta si hay depuraci¢n detiene el programa con una
condici¢n de error.

Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "t2l.hpp"
#include "httsmsg.h"

/**********************************************************/


/**********************************************************/

VOID TextToList::callback(VOID *param)
{

#ifdef HTTS_DEBUG
       htts_error("TextToList::callback() - You must program your own CallBack function.");
#endif

}

/**********************************************************/


