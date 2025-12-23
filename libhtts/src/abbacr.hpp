#ifndef __ABBACR_HPP__
#define __ABBACR_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ abbacr.hpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.2    29/03/01  Yon2.     Paso al directorio principal.
0.0.1    28/03/01  Yon2.     Need More Data.
0.0.0    22/03/01  Yon2.     Codificacion inicial.

======================== Contenido ========================
	Este modulo detecta y expande abreviaturas, acronimos y
unidades reflejadas en el diccionario.

	Los patrones que presentas estas formas son heterogeneos,
pudiendo ser:
- Para abreviaturas:
	lp    zbk.
  lplp  G.b.
- Para acronimos:
	l --> Generalmente en mayusculas.
- Para unidades:
  l --> no incluyen punto al final.

Se han encontrado tambien en el diccionario actual varias
ocurrencias extrañas, que habrá que corregir en el diccionario:
PSE-EE acr -> debería aparecer PSE por un lado y EE por otro.
zum. acr zumardi -> abreviatura o acrónimo? No importa.

Sólo en el caso de las unidades se tendrá en cuenta que se puede
alterar el orden:
   1 m -> metro bat.
   2 m -> bi metro.

Para decidir si se puede eliminar el punto correspondiente a un
acrónimo o abreviatura se necesita tener en ese momento el
grupo siguiente, para ver si es una letra mayúscula o minúscula.
Si este grupo siguiente no existe, se para la normalización hasta
que entren más datos.


Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

/**********************************************************/

enum AbbAcrUniType	{
	AAU_UNKNOWN=0,
	AAU_ABB,
	AAU_ACR,
	AAU_UNIT,
	AAU_ABBP,
	AAU_ACRP,
	AAU_UNITP,
	AAU_NEEDMOREDATA
};

/**********************************************************/

#endif

