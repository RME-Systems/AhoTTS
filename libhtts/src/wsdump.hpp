#ifndef __WSDUMP_HPP__
#define __WSDUMP_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ wsdump.hpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.0    08/01/01  Yon2.     Codificacion inicial.

======================== Contenido ========================

  Este m¢dulo vuelca la lista en formato "texto crudo" ya
normalizado a la lista est ndar del normalizador.
  De la lista est ndar se rellenan los campos:
- Tipo de Sentencia.
- Palabra.
- HDicRef
- Phrase
- Tipo de normalizaci¢n.

El campo Phrase junto con el de "tipo de sentencia" nos sit£an
dentro de los par‚ntesis.
Para poder distingrir fronteras en "tipo de normalizaci¢n" las
palabras que no hallan sufrido ninguna alteraci¢n en el
proceso de normalizaci¢n se han recogido con tipo de normalizaci¢n
UTYPENOR_NORMAL.

En este fichero de cabecera solo hay definiciones para el funcionamiento
del modulo de paso de lista de "texto crudo" a lista de texto
normalizado.


Yon2.

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "tdef.h"


/**********************************************************/
//Si aparecen 55 celdas en la lista de texto crudo, sin
//intercalar ning£n pipo de puntuaci¢n, se consideran
//estas palabras como integrantes de una frase.

#define CRUDE_LIST_MAX_LEN 100

/**********************************************************/

#endif

