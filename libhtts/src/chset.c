/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ chset.c
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C
Estado....................... -
Dependencia Hard/OS.......... pagina de codigos ISOLatin1
Codigo condicional........... -

Codificacion................. Oscar Losada
............................. Borja Etxebarria

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
1.0.2    03/07/00  richie    Hasta las pelotas ya!(minor bugfix)
1.0.1    24/01/00  oscar     Correccion de errores.
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.0.0    06/05/99  oscar     Codificacion inicial.

======================== Contenido ========================
<DOC>
Pagina de codigo ISOLatin1. Funciones de base de conversion
de caracteres.
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include <assert.h>
#include "chset.h"
#include <stdio.h>
/**********************************************************/
/* Esta funcion convierte el caracter {ch} {I} a
minuscualas. {devuelve} es el caracter convertido. Si el
caracter ya esta en minusculas o no es una letra, {devulve}
sera igual a {ch}. */

CHAR ISOLatin1_ToLower(CHAR ch)
{
	return((((ch<'\x61')||(ch>'\x7a'))&&(((ch>='\x41')&&(ch<='\x5a'))||
	((ch>='\xc0')&&((ch<='\xdf')&&(ch!='\xd7')))))?ch+32:ch);
	// Si es una letra y esta en mayusculas {devuelve}= a la correspondiente
	// minuscula. En caso contrario se {devuelve}={ch}.
}

/**********************************************************/
/* Esta funcion recorre la cadena de caracteres {str} {I/O}
convirtiendo estos a minusculas. Si el caracter no es una
letra en mayusculas no lo modifica. {devuelve} es la
longitud de la cadena.

Evidentemente, no se permite que {str} sea NULL, ni tampoco
que su longitud sea cero. */

size_t ISOLatin1_StrLower(CHAR *str)
{
	CHAR *strAux;	// Puntero al primer elemento de la cadena.
	assert(str&&(*str));
	for (strAux=str; *str; str++) *str=ISOLatin1_ToLower(*str);
	// Se realiza la conversion. Se devuelve en numero de caracteres de la
	return((size_t)(str-strAux)); // cadena.
}

/**********************************************************/
/* Esta funcion permite saber si el caracter {ch} {I} es
una letra minuscula o no. {devuelve} sera TRUE si en una
letra minuscula y FALSE en cualquier otro caso. */

BOOL ISOLatin1_IsLower(CHAR ch)
{
	return((((ch>='\x61')&&(ch<='\x7a'))||((ch>='\xe0')&&((ch<'\xff')&&
	(ch!='\xf7'))))?TRUE:FALSE); // Solo {devuelve} TRUE si es una letra en
	// minusculas.
}

/**********************************************************/
/* Esta funcion convierte el caracter {ch} {I} a
mayusculas. {devuelve} es el caracter convertido. Si el
caracter ya esta en mayusculas o no es una letra, {devulve}
sera igual a {ch}. */

CHAR ISOLatin1_ToUpper(CHAR ch)
{
	return((((ch>='\x61')&&(ch<='\x7a'))||((ch>='\xe0')&&((ch<='\xff')&&
	(ch!='\xf7'))))?ch-32:ch); // Si es una letra y esta en minusculas
	// {devuelve}= a su correspondiente mayuscual. En caso contrario
	// {devuelve}={ch}.
}

/**********************************************************/
/* Esta funcion recorre la cadena de caracteres {str} {I}
convirtiendo estos a mayusculas. Si el caracter no es una
letra en minusculas no lo modifica. {devuelve} es la
longitud de la cadena.

Evidentemente, no se permite que {str} sea NULL, ni tampoco
que su longitud sea cero. */

size_t ISOLatin1_StrUpper(CHAR *str)
{
	CHAR *strAux;	// Puntero al primer caracter de la cadena.
	assert(str&&(*str));
	for (strAux=str; *str; str++) *str=ISOLatin1_ToUpper(*str);
	// Se convierten a mayusculas
	return((size_t)(str-strAux));	// Se {devuelve} la longitud de la cadena.
}

/**********************************************************/
/* Esta funcion permite saber si el caracter {ch} {I} es
una letra mayuscula o no. {devuelve} sera TRUE si en una
letra mayuscula y FALSE en cualquier otro caso. */

BOOL ISOLatin1_IsUpper(CHAR ch)
{
	return((((ch<'\x61')&&(ch>'\x7a'))&&(((ch>='\x41')&&(ch<='\x5a'))||
	((ch>='\xc0')&&((ch<'\xdf')&&(ch!='\xd7')))))?TRUE:FALSE); // Si es una
	// letra mayuscula {devuelve}=TRUE. En otro caso {devuelve}=FALSE.
}

/**********************************************************/
/* Esta funcion permite saber si el caracter {ch} {I} es un
digito o no. {devuelve} sera TRUE si es un digito y FALSE
en cualquier otro caso. */

BOOL ISOLatin1_IsDigit(CHAR ch)
{
	return(((ch<'0')||(ch>'9'))?FALSE:TRUE); // Si no es digito
	// {devuelve}=FALSE. En caso contrario {devuelve} = TRUE.
}

/**********************************************************/
