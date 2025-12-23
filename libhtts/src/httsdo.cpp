/******************************************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

AhoTTS Multilingual: A Text-To-Speech system for Basque*, Spanish*, Galician',
Catalan^ and English^^, developed by Aholab Signal Processing Laboratory at the
University of the Basque Country (UPV/EHU). Its acoustic engine is based on
hts_engine** and it uses AhoCoder'' as vocoder.
(Read COPYRIGHT_and_LICENSE_code.txt for more details)
--------------------------------------------------------------------------------

*Linguistic processing for Basque and Spanish, Vocoder (Ahocoder) and
integration by Aholab UPV/EHU.

''AhoCoder is an HNM-based vocoder for Statistical Synthesizers
http://aholab.ehu.es/ahocoder/

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyrights:
	*1997-2012  Aholab Signal Processing Laboratory, University of the Basque
	 Country (UPV/EHU)
    	''2011-2012 Aholab Signal Processing Laboratory, University of the Basque
	  Country (UPV/EHU)

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Licenses:
	*GPL-3.0+
	''Modified BSD (Compatible with GNU GPL)

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GPL-3.0+
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 .
 This package is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 .
 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
 .
 On Debian systems, the complete text of the GNU General
 Public License version 3 can be found in /usr/share/common-licenses/GPL-3.

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/******************************************************************************/
/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ httsdo.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Borja Etxebarria
.............................

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
7.0.0    22/12/2025 ISC       ExtLangLing
4.0.0	 19/12/25  ISC 		 Version using multilingual functions for public repo and non-linux platforms
3.0.0    09/02/23  Inigo     Integrate Tacotron model
2.0.4    19/04/12  Agustin   Gallego usando cotovia-ecess y bool InputIsFile para procesar
* 							usando festival con la entrada siendo una cadena o el nombre de un fichero
2.0.4	 20/02/12  Agustin   Utt chunking para idiomas festival
2.0.3	 02/10/11  Inaki     add transcription API (y soporte para idiomas festival)
2.0.2	 15/12/10  Inaki     integrate HTS Synthesis Method
2.0.1	 03/10/07  Inaki     integrate Corpus Synthesis Method
2.0.0    27/06/03  lander    integrate HNS Synthesis Module
1.0.1    22/06/00  richie    minor bugfix
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.0.0    06/02/98  borja     Codificacion inicial.

======================== Contenido ========================
<DOC>
</DOC>
===========================================================
*/
/*IMPORTANTE
 * hay algunas funciones que estan copiadas de festival, no se
 * si habra que tener cuidado con la licencia o algo*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#define DEBUG_SHELLx

#include <assert.h>
#include "uti.h"

#include "htts.hpp"
#include "httsdo.hpp"
#include "httsmsg.h"

#ifdef HTTS_LANG_ES
#include "es_lingp.hpp"
#ifdef USE_TOKENIZER
#include "es_hdic.hpp"
// #include "es_tex.hpp"  // $$$ aun no hay tokenizer para castellano...
#include "es_t2l.hpp"  // $$$ EVA YA tenemos tokenizer en castellano
#endif
#endif

#ifdef HTTS_LANG_EU
#include "eu_lingp.hpp"
#ifdef USE_TOKENIZER
#include "eu_hdic.hpp"
#include "eu_t2l.hpp"
#endif
#endif

#ifdef HTTS_LANG_EX
#include "ex_lingp.hpp"
#include "t2l.hpp"
#include "t2u.hpp"
#include "wrapper.hpp" 
#endif


#ifdef HTTS_METHOD_HTS
#include "hts.hpp"
#endif
#ifdef HTTS_METHOD_TACO
#include "taco.hpp"
#endif
#ifdef HTTS_METHOD_VITS
#include "vits.hpp"
#endif
/**********************************************************/

#ifdef HTTS_METHVARS
#ifdef HTTS_METHOD_HTS           //INAKI
BOOL __htts_method_hts=TRUE;
#else
BOOL __htts_method_hts=FALSE;
#endif
#ifdef HTTS_METHOD_TACO
BOOL __htts_method_taco=TRUE;
#else
BOOL __htts_method_taco=FALSE;
#endif
#ifdef HTTS_METHOD_VITS
BOOL __htts_method_vits=TRUE;
#else
BOOL __htts_method_vits=FALSE;
#endif
#endif

/**********************************************************/

#ifdef HTTS_LANGVARS
#ifdef HTTS_LANG_ES
BOOL __htts_lang_es=TRUE;
#else
BOOL __htts_lang_es=FALSE;
#endif
#ifdef HTTS_LANG_EU
BOOL __htts_lang_eu=TRUE;
#else
BOOL __htts_lang_eu=FALSE;
#endif
#ifdef HTTS_LANG_EX
BOOL __htts_lang_ex=TRUE;
#else
BOOL __htts_lang_ex=FALSE;
#endif
#endif


/**********************************************************/

/**********************************************************/
HTTSDo::HTTSDo( VOID )
{
	created=FALSE;
	flushbuf=0;
#ifdef USE_TOKENIZER
	hdic=NULL;
	#ifdef HTTS_LANG_EX
		t2u_ex=NULL;
		tfil=NULL;
	#endif
#else
	tfil=NULL;
#endif
	t2u=NULL;
	lingp=NULL;
	utt=NULL;
	u2w=NULL;

	localdb=TRUE;

/* El primero definido sera el idioma por defecto */
#if defined(HTTS_LANG_EU)
	lang = "eu";
#elif defined(HTTS_LANG_ES)
	lang = "es";
#endif

/* El primero definido sera el metodo por defecto */
#if defined(HTTS_METHOD_HTS) //INAKI
	smethod = "HTS";
#elif defined(HTTS_METHOD_TACO)
	smethod = "Taco";
#elif defined(HTTS_METHOD_VITS)
	smethod = "Vits";
#endif

#ifdef USE_TOKENIZER
	hdicdbname = "hdic";
	//sustfn = "sust.txt";
#endif


    //hdicdbname="";
	modelpth="";
	dbpros="";
	modelpow="";
	modeldur="";
	modelpau="";
#ifdef HTTS_LANG_EX

	hdicdbname="";
	langvariante="";

#endif
}

/**********************************************************/

HTTSDo::~HTTSDo( )
{
	destroy();
}

/**********************************************************/

VOID HTTSDo::destroy( VOID )
{
#define DELIT(x) if (x) { delete x; x=NULL; }
#ifdef USE_TOKENIZER
	DELIT(hdic);
	#ifdef HTTS_LANG_EX
		DELIT(t2u_ex);
		DELIT(tfil);
	#endif
#else
	DELIT(tfil);
#endif
	DELIT(t2u);
	DELIT(lingp);
	DELIT(utt);
	DELIT(u2w);
#ifdef HTTS_LANG_EX
	DELIT(miWrapper);
#endif

}

/**********************************************************/

BOOL HTTSDo::create( VOID * db )
{
	int numerror=0;

	assert(!created);

#ifdef USE_TOKENIZER
	assert(!hdic);
	#ifdef HTTS_LANG_EX
		assert(!t2u_ex);
		assert(!tfil);
	#endif
#else
	assert(!tfil);
#endif
	assert(!t2u);
	assert(!lingp);
	assert(!utt);
	assert(!u2w);
#ifdef HTTS_LANG_EX
	assert(!miWrapper);
#endif


	BOOL ok;
	const CHAR* npth=NULL;
	DOUBLE d=0;

#ifndef USE_TOKENIZER
	t2u = new T2ULst;
	tfil = new TxtFilt;
#endif

	ok=FALSE;


#ifdef HTTS_LANG_EU
	if (!strcmp(lang,"eu")) {
		ok=TRUE;
		lingp = new LangEU_LingP;
#ifdef USE_TOKENIZER
		hdic = new LangEU_HDicDB;
		t2u = new LangEU_TextToList;
#else
		tfil = new TxtFilt;
		tfil->set("Lang",lang);
#endif

	}
#endif
#ifdef HTTS_LANG_ES
	if (!strcmp(lang,"es")) {
		ok=TRUE;
		lingp = new LangES_LingP;
#ifdef USE_TOKENIZER	
		hdic = new LangES_HDicDB;
		t2u = new LangES_TextToList;  // $$$ EVA como YA hay tokenizer ES ...
#else
		tfil = new TxtFilt;
		tfil->set("Lang",lang);
#endif
	}
#endif

#ifdef HTTS_LANG_EX

	if (!strcmp(lang,"ex")) {
		ok=TRUE;
		lingp = new LangEX_LingP;
		tfil = new TxtFilt;
		tfil->set("Lang",lang);
		miWrapper =new wrapper;
		miWrapper->set("Lang",langext);
		miWrapper->set("hdicdbname",hdicdbname);
		miWrapper->set("lang_variant",langvariante);
		miWrapper->initialize();
		tfil->miWrapper=miWrapper;
		lingp->miWrapper=miWrapper;
		//tfil->set_wrapper(miWrapper);
		//lingp->set_wrapper(miWrapper);
		#ifdef USE_TOKENIZER
			t2u_ex = new T2ULst;
		#else
			t2u = new T2ULst;
		#endif
	}
#endif



	if (!ok) htts_error("Invalid language (%s)",(const CHAR *)lang);
#ifdef USE_TOKENIZER
	#ifdef HTTS_LANG_EX
	if(strcmp(lang,"ex")){
	#endif
		if (!(lingp && t2u)) {numerror=1;goto error;}
	#ifdef HTTS_LANG_EX
	}else{
		if (!(lingp && t2u_ex)) {numerror=1;goto error;}
	}
	#endif
#else
	if (!(lingp && t2u)) {numerror=1;goto error;}
#endif

#ifdef USE_TOKENIZER
	#ifdef HTTS_LANG_EX
	if(strcmp(lang,"ex")){
	#endif
		if (!hdic)  goto error;
	#ifdef HTTS_LANG_EX
	}else{
		if (!tfil)  {numerror=2;goto error;}
	}
	#endif
#else
	if (!tfil)  {numerror=2;goto error;}
#endif

	ok=FALSE;




#ifdef HTTS_METHOD_HTS //INAKI
	if (!strcmp(smethod,"HTS")) {
		ok=TRUE;
		utt = new UttPh;
		u2w = new HTS_U2W;
		if (!(utt&&u2w))  {numerror=31;goto error;}
		hts=TRUE;
	}
	else
		hts =FALSE;
#endif


#ifdef HTTS_METHOD_TACO
	if (!strcmp(smethod,"Taco")) {
		ok=TRUE;
		utt = new UttPh;
		u2w = new TACO_U2W;
		if (!(utt&&u2w))  {numerror=32;goto error;}
		taco=TRUE;
	}
	else
		taco =FALSE;
#endif
#ifdef HTTS_METHOD_VITS
	if (!strcmp(smethod,"Vits")) {
		ok=TRUE;
		utt = new UttPh;
		u2w = new VITS_U2W;
		if (!(utt&&u2w))  {numerror=33;goto error;}
		vits=TRUE;
	}
	else
		vits =FALSE;
#endif
	if (!ok) htts_error("Invalid synthesis method (%s)",(const CHAR*)smethod);

#ifdef USE_TOKENIZER
	#ifdef HTTS_LANG_EX
	if(strcmp(lang,"ex")){
	#endif
		hdic->create(hdicdbname);
	#ifdef HTTS_LANG_EX	
	}else{
		if (!tfil->create()) goto error;
	}
	#endif
#else
	//if (!tfil->set("SustFile",sustfn))  {numerror=9;goto error;}//linea cambiada
	if (!tfil->create()) goto error;
#endif
	if (!modelpth.empty()) {
		if(strcmp(lang,"ex")){
			if (!lingp->set("PthModel",modelpth))  {numerror=10;goto error;}
		}
	}


#ifdef USE_TOKENIZER
	//$$$ Richie added. Muru Changed HDicDBName -> HDicDB
	#ifdef HTTS_LANG_EX
	if(strcmp(lang,"ex")){
	#endif
		lingp->set("HDicDB",hdicdbname);
	#ifdef HTTS_LANG_EX
	}
	#endif
#endif
	if (!lingp->create())  {numerror=15;goto error;}
	if (!utt->create())  {numerror=16;goto error;}
#ifdef USE_TOKENIZER
	#ifdef HTTS_LANG_EX
	if(strcmp(lang,"ex")){
	#endif
		((UttWS*)utt)->setHDicDB(hdic);
		if (!t2u->create((UttWS*)utt,hdic))  {numerror=17;goto error;}
	#ifdef HTTS_LANG_EX
	}else{		
		if (!t2u_ex->create((UttWS*)utt))  {numerror=18;goto error;}
	}
	#endif
#else
	if (!t2u->create((UttWS*)utt))  {numerror=18;goto error;}
#endif

#ifdef HTTS_METHOD_HTS
	if (!strcmp(smethod,"HTS")) if (! ((HTS_U2W*)u2w)->create(lingp->get("Lang")))  {numerror=32;goto error;} //INAKI
#endif
#ifdef HTTS_METHOD_TACO
	if (!strcmp(smethod,"Taco")) if (! ((TACO_U2W*)u2w)->create(lang))  {numerror=32;goto error;}
#endif
#ifdef HTTS_METHOD_VITS
	if (!strcmp(smethod,"Vits")) if (! ((VITS_U2W*)u2w)->create(lang))  {numerror=33;goto error;}		
#endif
/* Configurar pitch nominal si es posible, si no, pitch 100Hz */
	npth=get("NominalPth");
	d=npth?atof(npth):0;
	if (!strcmp(lang,"es")||!strcmp(lang,"eu")) {
		if (!set("PthMean",d?npth:"100"))  {numerror=28;goto error;}
	}
	/* cableamos un par de opciones... */
#ifdef HTTS_METHOD_TACO
	if (!strcmp(smethod,"Taco")) lingp->set("PhMap_jw2iu","n");
	else lingp->set("PhMap_jw2iu","y");
#elif defined(HTTS_METHOD_VITS)
	if (!strcmp(smethod,"Vits")) lingp->set("PhMap_jw2iu","n");
	else lingp->set("PhMap_jw2iu","y");
#else
	lingp->set("PhMap_jw2iu","y");
#endif
	lingp->set("Lang",lang);


	ackpending=FALSE;
	created=TRUE;
	flushbuf=0;

	return TRUE;

error:
	switch (numerror){
	case 1: htts_error("Error 1. Can't create HTTS module");
	case 2: htts_error("Error 2. Can't create HTTS module");
	case 3: htts_error("Error 3. Can't create HTTS module");
	case 4: htts_error("Error 4. Can't create HTTS module");
	case 5: htts_error("Error 5. Can't create HTTS module");
	case 6: htts_error("Error 6. Can't create HTTS module");
	case 7: htts_error("Error 7. Can't create HTTS module");
	case 8: htts_error("Error 8. Can't create HTTS module");
	case 9: htts_error("Error 9. Can't create HTTS module");
	case 10: htts_error("Error 10. Can't create HTTS module");
	case 11: htts_error("Error 11. Can't create HTTS module");
	case 12: htts_error("Error 12. Can't create HTTS module");
	case 13: htts_error("Error 13. Can't create HTTS module");
	case 14: htts_error("Error 14. Can't create HTTS module");
	case 15: htts_error("Error 15. Can't create HTTS module");
	case 16: htts_error("Error 16. Can't create HTTS module");
	case 17: htts_error("Error 17. Can't create HTTS module");
	case 18: htts_error("Error 18. Can't create HTTS module");
	case 19: htts_error("Error 19. Can't create HTTS module");
	case 20: htts_error("Error 20. Can't create HTTS module");
	case 21: htts_error("Error 21. Can't create HTTS module");
	case 22: htts_error("Error 22. Can't create HTTS module");
	case 23: htts_error("Error 23. Can't create HTTS module");
	case 24: htts_error("Error 24. Can't create HTTS module");
	case 25: htts_error("Error 25. Can't create HTTS module");
	case 26: htts_error("Error 26. Can't create HTTS module");
	case 27: htts_error("Error 27. Can't create HTTS module");
	case 28: htts_error("Error 28. Can't create HTTS module");
	case 29: htts_error("Error 29. Can't create HTTS module"); //INAKI
	case 30: htts_error("Error 30. Can't create HTTS module"); //INAKI
	case 31: htts_error("Error 31. Can't create HTTS module"); //INAKI
	case 32: htts_error("Error 32. Can't create HTTS module");
	case 33: htts_error("Error 33. Can't create HTTS module");
	}

	//ts_error("Can't create HTTS module");
	destroy();
	return FALSE;
}

/**********************************************************/

VOID *HTTSDo::getDB(VOID)
{
#ifdef HTTS_THREADSAFE
	// si no se puede obtener el modo o es distinto de Preload, no es thread-safe
		//const CHAR *s=dphdb->get("DBLoadMode");
		//if (!s || strcmp(s,"Preload")) return NULL;

#endif
		//return (VOID*)dphdb;
	//}
	// si es de formantes o no esta creada la base de datos, NULL
	return NULL;
}

/**********************************************************/

BOOL HTTSDo::advance( VOID )
{
	BOOL flush;
	Utt* u=NULL;
	const DOUBLE* vec;
	INT len;
	BOOL ret;

	vec = u2w->output(&len,&flush);
	
	if (vec||flush) return TRUE;  // si u2w genera salida valida, OK

/*... si no hay mas tramas de formantes o si es el sinte de
difonemas, intentamos obtener una nueva utt de t2u, y sintetizarla.
pero primero, borramos la lista vieja del primer modulo (t2u)*/

	if (ackpending) {  // solo si hace falta
		#ifdef USE_TOKENIZER
			#ifdef HTTS_LANG_EX
			if(!strcmp(lang,"ex")){
				t2u_ex->outack();
			}else{
			#endif
				t2u->outack();
			#ifdef HTTS_LANG_EX
			}
			#endif
		#else
		t2u->outack();
		#endif
		ackpending= FALSE;
	}
	
	/* manejamos el buffer de flushes {flushbuf}. Lo necesitamos porque
	los flushes no llegan a t2u mientras se esta procesando una frase,
	ya que el ack() a este modulo se envia cuando se termina
	con la frase en los demas modulos, y no tras el tu2->output() */
	while (flushbuf>0) {
		#ifdef USE_TOKENIZER
			#ifdef HTTS_LANG_EX
			if(!strcmp(lang,"ex")){
				if (t2u_ex->flush()) flushbuf--; else break;
			}else{
			#endif
				if (t2u->flush()) flushbuf--; else break;
			#ifdef HTTS_LANG_EX
			}
			#endif
		#else
			if (t2u->flush()) flushbuf--; else break;
		#endif
	}
	#ifdef USE_TOKENIZER
		#ifdef HTTS_LANG_EX
		if(!strcmp(lang,"ex")){
			u = t2u_ex->output(&flush);
		}else{
		#endif
			u = t2u->output(&flush);	
		#ifdef HTTS_LANG_EX	
		}
		#endif
	#else
		u = t2u->output(&flush);	
	#endif
	if (u) {  // estupendo, obtuvimos una utt
		lingp->utt_lingp(u);  // la procesamos
#ifdef HTTS_METHOD_HTS
			if(hts){
				ret=u2w->input(u);
			}
			else{
#endif
#ifdef HTTS_METHOD_TACO
			if(taco){
				ret=u2w->input(u);
			}
			else{
#endif
#ifdef HTTS_METHOD_VITS
			if(vits){
				ret=u2w->input(u);
			}
			else{
#endif

#ifdef HTTS_METHOD_VITS
				}
#endif
#ifdef HTTS_METHOD_TACO
				}
#endif
#ifdef HTTS_METHOD_HTS
		}
#endif

		assert(ret);
		ackpending = TRUE;
		return TRUE;
	}
	if (flush) {  // estupendo, obtuvimos un flush
			ret=u2w->flush();
		assert(ret);
		ackpending = TRUE;
		return TRUE;
	}

#ifdef USE_TOKENIZER
	// usando tokenizer no hay mas modulos delante de t2u
	#ifdef HTTS_LANG_EX	
	if(!strcmp(lang,"ex")){
		const CHAR *s=tfil->output(&flush);
		if (s) {
			INT x=t2u_ex->input(s);
			assert(strlen(s)==x);
			tfil->outack(x);
			return x;
		}
		if (flush) {  // nos ha dado un flush, ok
			tfil->outack(t2u_ex->flush()?1:0);
			return TRUE;
		}
	}
	#endif
#else
	// si hemos llegado aqui, a ver si tfil nos da algo
	const CHAR *s=tfil->output(&flush);
	if (s) {

		tfil->outack(t2u->input(s));
		INT x=t2u->input(s);
		tfil->outack(x);
		return x;
	}
	if (flush) {  // nos ha dado un flush, ok

		tfil->outack(t2u->flush()?1:0);
		return TRUE;
	}
#endif
	
	(void)ret;
	// si llegamos aqui, no hemos avanzado nada, :(
	return FALSE;
}

/**********************************************************/

INT HTTSDo::input( const CHAR * str )
{
	assert(created);
#ifdef USE_TOKENIZER
	INT ret=0;
	#ifdef HTTS_LANG_EX	
	if(strcmp(lang,"ex")){
	#endif
		assert(t2u);
		ret=t2u->input(str);
	#ifdef HTTS_LANG_EX	
	}else{
		assert(tfil);
		ret=tfil->input(str);
	}
	#endif
#else
	assert(tfil);	
	INT ret=tfil->input(str);
	//printf("RET %d \n",ret);
#endif
	advance();
	return ret;
}

/**********************************************************/

BOOL HTTSDo::input( CHAR ch )
{
	assert(created);

#ifdef USE_TOKENIZER
	BOOL ret=0;
	#ifdef HTTS_LANG_EX	
	if(strcmp(lang,"ex")){
	#endif
		assert(t2u);
		ret=t2u->input(ch);
	#ifdef HTTS_LANG_EX	
	}else{
		assert(tfil);
		ret=tfil->input(ch);
	}
	#endif
#else
	assert(tfil);
	BOOL ret=tfil->input(ch);
#endif
	advance();
	return ret;
}

/**********************************************************/

BOOL HTTSDo::flush( VOID )
{
	assert(created);
	flushbuf++;
	advance();
	return TRUE;
}

/**********************************************************/

const DOUBLE* HTTSDo::output( INT *len, BOOL *flush, INT mode, VOID *cb_n )
{
	const DOUBLE *p = NULL;

	assert(created);
	assert(u2w);
	while (1) {
		BOOL flu=FALSE;
		p = u2w->output(len,&flu);  // leer salida
		if (flush) *flush=flu;  // *flush puede ser NULL, por eso usamos flu temporalmente

		if (p || flu) break;  // si hay salida valida, return
		// si no hay salida valida:
		if (advance()) continue;  // si hay flujo entre modulos => repite
		// si no, nada que hacer...
		if (mode != HTTS_CB_NOCALL) {  // ...salvo llamar al callback y repetir
			callback(cb_n);
			if (mode==HTTS_CB_CALL1) mode=HTTS_CB_NOCALL; // cancelar el callback si esta en modo de 1-vez
			continue;
		}
		break;
	}
	return p;
}

/**********************************************************/

BOOL HTTSDo::isFlush( VOID )
{
	assert(created);
	assert(u2w);
	return u2w->isFlush();
}

/**********************************************************/

#ifdef HTTS_INTERFACE_WAVEMARKS
const Mark1DList & HTTSDo::mrkget( VOID )
{
	assert(created);
	assert(u2w);
	return u2w->mrkget();
}
#endif

/**********************************************************/

#ifdef HTTS_INTERFACE_WAVEMARKS
VOID HTTSDo::mrkdel( VOID )
{
	assert(created);
	assert(u2w);
	u2w->mrkdel();
}
#endif

/**********************************************************/

#ifdef HTTS_INTERFACE_WAVEMARKS
BOOL HTTSDo::outack( INT n, BOOL mrkdel )
{
	assert(created);
	assert(u2w);
	return u2w->outack(n,mrkdel);
}
#else
BOOL HTTSDo::outack( INT n )
{
	assert(created);
	assert(u2w);
	return u2w->outack(n);
}
#endif

/**********************************************************/

#ifdef HTTS_TIMEEVS
INT HTTSDo::get_timeev( VOID )
{
	assert(created);
	assert(u2w);
	return u2w->get_timeev();
}
#endif

/**********************************************************/

BOOL HTTSDo::set( const CHAR* param, const CHAR* val )
{
	if (!strcmp(param,"Lang")) {
		if (created) return FALSE;
		lang= val;
#ifdef DEBUG_SHELL
		htts_warn("HTTSDo::set - Language value captured [%s]", lang.chars());
#endif
		return TRUE;
	}
	#ifdef HTTS_LANG_EX	
		if (!strcmp(param,"Langext")) {
			if (created) return FALSE;
			langext= val;
	#ifdef DEBUG_SHELL
			htts_warn("HTTSDo::set - Languagext value captured [%s]", langext.chars());
	#endif
			return TRUE;
		}
	#endif
	if (!strcmp(param,"Method")) {
		if (created) return FALSE;
		smethod= val;
#ifdef DEBUG_SHELL
		htts_warn("HTTSDo::set - Method value captured [%s]", smethod.chars());
#endif
		return TRUE;
	}

	if (!strcmp(param,"PthModel")) {
		if (created) return FALSE;
		modelpth= val;
#ifdef DEBUG_SHELL
		htts_warn("HTTSDo::set - PthModel value captured [%s]", modelpth.chars());
#endif
		return TRUE;
	}

	if (!strcmp(param,"ProsDBName")) {
		if (created) return FALSE;
		dbpros= val;
#ifdef DEBUG_SHELL
		htts_warn("HTTSDo::set - ProsDBName value captured [%s]", dbpros.chars());
#endif
		return TRUE;
	}


	if (!strcmp(param,"PowModel")) {
		if (created) return FALSE;
		modelpow= val;
#ifdef DEBUG_SHELL
		htts_warn("HTTSDo::set - PowModel value captured [%s]", modelpow.chars());
#endif
		return TRUE;
	}

	if (!strcmp(param,"DurModel")) {
		if (created) return FALSE;
		modeldur= val;
#ifdef DEBUG_SHELL
		htts_warn("HTTSDo::set - DurModel value captured [%s]", modeldur.chars());
#endif
		return TRUE;
	}

	if (!strcmp(param,"PauModel")) {
		if (created) return FALSE;
		modelpau= val;
#ifdef DEBUG_SHELL
		htts_warn("HTTSDo::set - PauModel value captured [%s]", modelpau.chars());
#endif
		return TRUE;
	}

#ifdef HTTS_DIPHONE
	if (!strcmp(param,"DBName")) {
		if (created) return FALSE;
		dbname= val;
#ifdef DEBUG_SHELL
		htts_warn("HTTSDo::set - DBName value captured [%s]", dbname.chars());
#endif
		return TRUE;
	}
#endif

#ifdef HTTS_DIPHONE
	if (!strcmp(param,"DBLoadMode")) {
		if (created) return FALSE;
		dbmode= val;
#ifdef DEBUG_SHELL
		htts_warn("HTTSDo::set - DBLoadMode value captured [%s]", dbmode.chars());
#endif
		return TRUE;
	}
#endif
#ifdef USE_TOKENIZER	
	#ifdef HTTS_LANG_EX	

	
		if (!strcmp(param,"HDicDB")) {
			if (created) return FALSE;
			hdicdbname= val;
			 //mirar esto
			#ifdef DEBUG_SHELL
				htts_warn("HTTSDo::set - HDicDB value captured [%s]", hdicdbname.chars());
			#endif
			return TRUE;
		}
	

	
		if (!strcmp(param,"LangVariant")) {
			if (created) return FALSE;
			langvariante= val;
			 //mirar esto
			#ifdef DEBUG_SHELL
				htts_warn("HTTSDo::set - LangVariant value captured [%s]", langvariante.chars());
			#endif
			return TRUE;
		}
	

	#endif
#else
	if (!strcmp(param,"SustFile")) {
		if (created) return FALSE;
		sustfn= val;
#ifdef DEBUG_SHELL
		htts_warn("HTTSDo::set - SustFile value captured [%s]", sustfn.chars());
#endif
		return TRUE;
	}
#endif

	if (!strcmp(param,"DefEmo")) { //INAKI
		if (!created) return FALSE;
#ifdef USE_TOKENIZER
		#ifdef HTTS_LANG_EX	
		if(strcmp(lang,"ex")){
		#endif
			t2u->set(param, val);
			return TRUE;
		#ifdef HTTS_LANG_EX	
		}
		#endif
#endif
	}	//INAKI

	if (!strcmp(param,"DefIntEmo")) { //INAKI
		if (!created) return FALSE;
#ifdef USE_TOKENIZER
		#ifdef HTTS_LANG_EX	
		if(!strcmp(lang,"ex")){
			t2u_ex->set(param, val);
			return TRUE;
		}
		#endif
#endif
	}	//INAKI

	BOOL ret=FALSE;

#ifdef USE_TOKENIZER
// Por ahora hdic no tiene set/get
//	if (hdic) ret = ret || hdic->set(param,val);
	#ifdef HTTS_LANG_EX	
	if(!strcmp(lang,"ex")){
		if (tfil) ret = ret || tfil->set(param,val);
		if (t2u_ex) ret = ret || t2u_ex->set(param,val);
	}else{
	#endif	
		if (t2u) ret = ret || t2u->set(param,val);
	#ifdef HTTS_LANG_EX	
	}
	#endif	
#else
	if (tfil) ret = ret || tfil->set(param,val);
#endif
	//if (t2u) ret = ret || t2u->set(param,val);  // $$$ casca

	if (lingp) ret = ret || lingp->set(param,val);

	if (u2w) ret = ret || u2w->set(param,val);

	return ret;
}

/**********************************************************/

const CHAR* HTTSDo::get( const CHAR* param )
{
	if (!strcmp(param,"QueryMethods")) return
#ifdef HTTS_METHOD_HTS
		"[HTS]"    //INAKI
#endif
#ifdef HTTS_METHOD_TACO
		"[Taco]"
#endif
#ifdef HTTS_METHOD_VITS
		"[Vits]"
#endif
	;

	if (!strcmp(param,"QueryLanguages")) return
#ifdef HTTS_LANG_ES
		"[es]"
#endif
#ifdef HTTS_LANG_EU
		"[eu]"
#endif
#ifdef HTTS_LANG_CAT
		"[ca]"
#endif
#ifdef HTTS_LANG_GAL
		"[gl]"
#endif
	;

	if (!strcmp(param,"Lang")) return lang;
	if (!strcmp(param,"DefEmo")) return emo;
	if (!strcmp(param,"DefIntEmo")) return emoint;
	if (!strcmp(param,"Method")) return smethod;
	if (!strcmp(param,"PthModel")) return lingp?lingp->get(param):(const CHAR *)modelpth;
	if (!strcmp(param,"ProsDBName")) return lingp?lingp->get(param):(const CHAR *)dbpros;
	if (!strcmp(param,"PowModel")) return lingp?lingp->get(param):(const CHAR *)modelpow;
	if (!strcmp(param,"DurModel")) return lingp?lingp->get(param):(const CHAR *)modeldur;
	if (!strcmp(param,"PauModel")) return lingp?lingp->get(param):(const CHAR *)modelpau;

#ifdef USE_TOKENIZER
	#ifdef HTTS_LANG_EX
	if(strcmp(lang,"ex")){
	#endif
		if (!strcmp(param,"HDicDB")) return hdicdbname;
	#ifdef HTTS_LANG_EX
	}
	#endif
#else
	if (!strcmp(param,"SustFile")) return sustfn;
#endif

	const CHAR *ret = NULL;

#ifdef HTTS_METHOD_HTS //INAKI
	if(hts){
		if(!strcmp(param,"SRate")){
			ret=strdup("16000");
			return ret; //INAKI CHAPUZA
		}
	}
#endif
#ifdef HTTS_METHOD_TACO
	if(taco){
		if(!strcmp(param,"SRate")){
			ret=strdup("22050");
			return ret;
		}
	}
#endif
#ifdef HTTS_METHOD_VITS
	if(vits){
		if(!strcmp(param,"SRate")){
			ret=strdup("22050");
			return ret;
		}
	}
#endif

	if (u2w) ret = u2w->get(param); if (ret) return ret;
	if (lingp) ret = lingp->get(param); if (ret) return ret;
#ifdef USE_TOKENIZER
	#ifdef HTTS_LANG_EX
	if(!strcmp(lang,"ex")){
		if (t2u_ex) ret = t2u_ex->get(param); if (ret) return ret;
	}else{
	#endif
		if (t2u) ret = t2u->get(param); if (ret) return ret;
	#ifdef HTTS_LANG_EX
	}
	#endif	
#else
	if (t2u) ret = t2u->get(param); if (ret) return ret;
#endif
#ifdef USE_TOKENIZER
// Por ahora hdic no tiene get
//	if (hdic) ret = hdic->get(param); if (ret) return ret;
	#ifdef HTTS_LANG_EX
	if(!strcmp(lang,"ex")){
		if (tfil) ret = tfil->get(param); if (ret) return ret;
	}
	#endif
#else
	if (tfil) ret = tfil->get(param); if (ret) return ret;
#endif
	return ret;
}

/**********************************************************/
/**********************************************************/
//inaki
//inaki
//devuelve número de muestras sintetizadas y las almacena en short **samples
int HTTSDo::synthesize_do_next_sentence( const CHAR *lang, short **samples) {
    int num_muestras = 0;
    Utt *u = NULL;
    BOOL flush = FALSE;
#ifdef HTTS_LANG_EX
    if (!strcmp(lang, "ex")) {
        u = t2u_ex->output(&flush);
    } else {
#endif
	u = t2u->output(&flush);
#ifdef  HTTS_LANG_EX
    }
#endif
	if (u) {  // estupendo, obtuvimos una utt
		ackpending = TRUE;
		lingp->utt_lingp(u);  // la procesamos


		#ifdef HTTS_METHOD_HTS
        String labels_string="";
        if (!strcmp(smethod,"HTS")) {
            //String labels_string_tmp;
            ((HTS_U2W *) u2w)->pho2hts((UttPh *) u, labels_string, TRUE);    //convertimos a labels
            //labels_string+=labels_string_tmp;
            t2u->outack();
            //ackpending = FALSE; //Ibon
            //	u = t2u->output(&flush);
            *samples = ((HTS_U2W *) u2w)->xinput_labels(labels_string, &num_muestras);
        }
		#endif
		#ifdef HTTS_METHOD_TACO
        if (!strcmp(smethod,"Taco")) {
            *samples = ((TACO_U2W *) u2w)->xinput_labels((UttPh *) u, &num_muestras);
			t2u->outack();
        }

        #endif
        #ifdef HTTS_METHOD_VITS
		if (!strcmp(smethod,"Vits")) {
			*samples = ((VITS_U2W *) u2w)->xinput_labels((UttPh *) u, &num_muestras);
#ifdef HTTS_LANG_EX
            if (!strcmp(lang, "ex")) {
                t2u_ex->outack();
            } else {
#endif
			t2u->outack();
#ifdef  HTTS_LANG_EX
            }
#endif
//            t2u->outack();
		}
        #endif

	}
	else
    if (flush) {
#ifdef HTTS_LANG_EX
        if (!strcmp(lang, "ex")) {
            t2u_ex->outack();           //ISC pongo esto porque parece que se queda pendient de outack cuando genera una salida en vacio, no estoy seguro de porque no es necesario en eus y spa
        }
#endif
        return -1;  // v2.4.0 Devolvemos -1 si ha habido flush para indicar fin de la síntesis, pero tras haber enviado las muestras
    }

	return num_muestras;
	//*out=strdup(Silabificado);

}



/*	return num_muestras;
	//*out=strdup(Silabificado);
	
}*/
/**********************************************************/
/**********************************************************/
//inaki
BOOL HTTSDo::synthesize_do_input( const CHAR *str, const CHAR *lang , BOOL InputIsFile /*=FALSE*/, const CHAR *data_path){

	BOOL flush=FALSE;
	assert(created);
	strcpy(DataPath, data_path);
	//para euskera y castellano usamos código ahoTTS
	


//ISC nik egiten dut JonVarenean ez baitago funtzio hau
//    assert(t2u);
//		INT ret=t2u->input(str);
    #ifdef USE_TOKENIZER
        #ifdef HTTS_LANG_EX
        if(strcmp(lang,"ex")){
        #endif
		assert(t2u);
            INT ret=t2u->input(str);
        #ifdef HTTS_LANG_EX
        }
		if(!strcmp(lang,"ex")){
			assert(tfil);
            BOOL closed=FALSE;
            INT numacceptchar=0;
            INT ret=0;
			while (!closed) {
                str+=numacceptchar;
                numacceptchar += tfil->input(str);
                if (numacceptchar>= strlen(str)) closed = TRUE;

                const CHAR *s = tfil->output(&flush);
                if (s) {
                    ret = t2u_ex->input(s);

                    assert(strlen(s) == ret);
                    tfil->outack(ret);
                } else if (flush) {
                    if (t2u_ex->flush()) {
                        flushbuf--;
                        tfil->outack(1);
                    } else
                        tfil->outack(0);
                }
            }
		}
        #endif
    #endif
		flushbuf++;
		flush=FALSE;


		String Silabificado="";
		UttI pa, pi;
	    if (ackpending) {  // solo si hace falta
	  		#ifdef USE_TOKENIZER
			#ifdef HTTS_LANG_EX
			if(strcmp(lang,"ex")){
			#endif
			t2u->outack();
			ackpending= FALSE;
			#ifdef HTTS_LANG_EX
			}else{
				t2u_ex->outack();
				ackpending= FALSE;

			}
			#endif
			#else
			t2u->outack();
			ackpending= FALSE;
			#endif
		}

		/* manejamos el buffer de flushes {flushbuf}. Lo necesitamos porque
		los flushes no llegan a t2u mientras se esta procesando una frase,
		ya que el ack() a este modulo se envia cuando se termina
		con la frase en los demas modulos, y no tras el tu2->output() */
		while (flushbuf>0) {
			#ifdef USE_TOKENIZER
				#ifdef HTTS_LANG_EX
				if(strcmp(lang,"ex")){
				#endif
			if (t2u->flush()) flushbuf--; else break;
				#ifdef HTTS_LANG_EX
				}else{
					if (t2u_ex->flush()) flushbuf--; else break;
				}
				#endif
			#else
				if (t2u->flush()) flushbuf--; else break;
			#endif
		}

		return TRUE;


	
}



/////////////////////////////////////////////////////////////////
