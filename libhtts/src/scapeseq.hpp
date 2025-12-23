#ifndef __SCAPESEQ_HPP__
#define __SCAPESEQ_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ scapeseq.hpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.1    21/06/01  Yon2.     insertPuase added.
0.0.0    18/06/01  Yon2.     Codificacion inicial.

======================== Contenido ========================

Soporte para secuencias de escape sólo en el normalizador.

El formato para las secuencias de escape es:
]C0;[
El patron que genera esta secuencia en WordChop, el troceador
de palabras es:
slnps -> símbolo letra numero puntuación símbolo, todas ellas
tienen longitud uno para que la detección sea más sencilla
y para que no se confundan con posibles secuencias en el 
texto original.

- Los corchetes y el punto y coma no tienen ningún significado.
- La letra indica el tipo de secuencia de escape y el número
es un parámetro para el tipo de secuencia de escape.
- Si el número es cero, indica el final de la secuencia de
escape. En generar habrá marcas de apertura y cierre de
secuencia de escape. Estas marcas afectarán a todo el texto
contenido entre ellas.

Marcas Soportadas:

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

En principio los tipos de pausa de la 3 a la 9 no tienen
mucho sentido en este módulo.

Se insertarán pausas de tipo 1 o de tipo 2 preferiblemente.

Yon2.

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/
  
/**********************************************************/

#include "tdef.h"
#include "t2l.hpp"
#include "scapedo.hpp"
#include "uttws.hpp"

/**********************************************************/

BOOL insertPause(UttWS *ws, UttI p, INT value);


/***********************************************************************/

#endif
