#ifndef __ES_POS_HPP__
#define __ES_POS_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 2004 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ es_pos.hpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Inma Sardon
............................. inigos



======================== Contenido ========================
<DOC>
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "es_hdic.hpp"
#include "uttws.hpp"

#define MAX_TAM_WORD 100	//20 no es suficiente
typedef struct etiq{
			int pos1;
			int pos2;
			int pos3;
			int pos4;
			int pos5;
			int contador;
		}etiquetas;

typedef struct signo_posicion2{
		int pausa;
		int posicion;
		String signo;
	}signo_posic;


typedef struct estruc{
			String palab;
			bool pau;
			UttI puntero_celda;
		}palab_paus;
/**********************************************************/

class LangES_Categ {

	private:
		BOOL created;

	protected:
		String dbName;

	public:
		LangES_Categ( VOID );
		~LangES_Categ();
		BOOL create(VOID);

		BOOL set( const CHAR *param, const CHAR *val );
		const CHAR *get( const CHAR *param );

		VOID utt_categ(UttWS &ut);

	public:
		INT posdic(UttWS &u, UttI p, int i, etiquetas *pos);
		INT puede_ser_verbo(UttWS &u,UttI p,char *word_act,int i,etiquetas *pos);
		INT buscar_infinitivo(UttWS &u,UttI p, CHAR *word_act, int fin, int inicio, int longitud);
		INT es_xxeer(UttWS &u,UttI p);
		INT es_nli(UttWS &u,UttI p);
		INT es_xxponer(UttWS &u,UttI p);
		INT es_poner(UttWS &u,UttI p, CHAR *word_act);
		INT es_xxhacer(UttWS &u,UttI p);
		INT es_hacer(UttWS &u,UttI p, CHAR *word_act);
		INT es_xxvaler(UttWS &u,UttI p);
		INT es_valer(UttWS &u,UttI p, CHAR *word_act);
		INT es_xxtener(UttWS &u,UttI p);
		INT es_tener(UttWS &u,UttI p, CHAR *word_act);
		INT es_xxtraer(UttWS &u,UttI p);
		INT es_traer(UttWS &u,UttI p, CHAR *word_act);
		INT es_xxdecir(UttWS &u,UttI p);
		INT es_decir(UttWS &u,UttI p, CHAR *word_act);
		INT es_xxsalir(UttWS &u,UttI p);
		INT es_salir(UttWS &u,UttI p, CHAR *word_act);
		INT es_xxvenir(UttWS &u,UttI p);
		INT es_venir(UttWS &u,UttI p, CHAR *word_act);
		INT es_xxducir(UttWS &u,UttI p);
		INT es_verbo(UttWS &u,UttI p, CHAR *word_act, int i, etiquetas *pos);
		INT es_enclitico(UttWS &u,UttI p,int i, etiquetas *pos);
		INT es_no_personal(UttWS &u,UttI p);
		INT desambiguar(UttWS & u,etiquetas *pos);
		INT es_xxmente(UttWS &u,UttI p);
};


/**********************************************************/


class LangES_GF {
	private:
		BOOL created;
	protected:
		String dbName;

	public:
		LangES_GF( VOID );
		~LangES_GF();
		BOOL create(VOID);

		VOID set_inf(UttWS &u, UttI p);
		VOID set_up_flag(UttWS &u, UttI p);

		BOOL set( const CHAR *param, const CHAR *val );
		const CHAR *get( const CHAR *param );

		VOID utt_gf( UttWS &ut );

};

/**********************************************************/

/*class LangES_Pos : public Pos {
private:
	LangES_Categ  categ;
	LangES_GF	grupof;

public:
	virtual ~LangES_Pos() {}; //needed to remove a warning
	BOOL create( VOID );

	VOID utt_pos( Utt *u );
	VOID utt_categ( Utt *u );
	VOID utt_gf( Utt *u );

	BOOL set( const CHAR *param, const CHAR *val );
	const CHAR *get( const CHAR *param );
};*/

#endif

/**********************************************************/
