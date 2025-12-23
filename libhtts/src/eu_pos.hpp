#ifndef __EU_POS_HPP__
#define __EU_POS_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ eu_pos.hpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Inma Sardon
.............................



======================== Contenido ========================
<DOC>
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

//#include "eu_lingp.hpp"
#include "eu_hdic.hpp"
#include "uttws.hpp"

#define MAX_TAM_WORD 100	//20 no es suficiente
/**********************************************************/

class LangEU_Categ {
	//	int num_Word;
	//	LangEU_HDicDB db;
	private:
		BOOL created;
	protected:
		String dbName;

	public:
		LangEU_Categ( VOID );
		~LangEU_Categ();
		BOOL create(VOID);

		BOOL set( const CHAR *param, const CHAR *val );
		const CHAR *get( const CHAR *param );

		VOID utt_categ(UttWS &ut);

	public:
		BOOL encontrado;
		VOID posdic(UttWS &u, UttI p);
		VOID aditudu(UttWS &u,UttI p,char *word_act);
//		BOOL babait(UttWS &u,UttI p, char *word_act,LangEU_HDicDB &db);
		VOID babait(UttWS &u,UttI p, char *word_act,LangEU_HDicDB &db);
		VOID atzize(UttWS &u,UttI p, char *word_act,LangEU_HDicDB &db);

		VOID atzadi(UttWS &u,UttI p, char *word_act,LangEU_HDicDB &db);

		VOID adit(UttWS &u,UttI p, char *adi,LangEU_HDicDB &db);
		VOID auxt(UttWS &u,UttI p, char *adi,LangEU_HDicDB &db);
		void detaux(UttWS &u, UttI p);
		void detior(UttWS &u, UttI p);
		void trnlgn(UttWS &u, UttI p);
		void jntazk(UttWS &u, UttI p,int numWord);
		void izejok(UttWS &u, UttI p);
		void adjjok(UttWS &u, UttI p);

};


/**********************************************************/


class LangEU_GF {
	private:
		BOOL created;
	protected:
		String dbName;

	public:
		LangEU_GF( VOID );
		~LangEU_GF();
		BOOL create(VOID);

		BOOL set( const CHAR *param, const CHAR *val );
		const CHAR *get( const CHAR *param );

		VOID utt_gf( UttWS &ut );

	public:
		typedef struct {
			char word[MAX_TAM_WORD];  //INMASS
			UttI p;		//puntero a celda
			unsigned long	word_POS,word_GF;
		} word_info;
	typedef struct{
		word_info prev;
		word_info act;
		word_info	next;
		word_info	nextn;
	}gf_info;

	typedef struct{
		BOOL phrase_last;	//detecta final de frase
		BOOL phrase_prev_last;
		BOOL utt_last;	//detecta final de utterance
		BOOL utt_prev_last;
		BOOL phrase_first; //detecta comienzo de frase
		BOOL utt_first;
	}up_flag;

	int indice2;
	int gf;
	BOOL encontrado;
	gf_info inf;
	up_flag u_p_flag;
	VOID set_inf(UttWS &u, UttI p);
	VOID set_up_flag(UttWS &u, UttI p);

	VOID enk(UttWS &u, UttI p, int *gf);
	VOID detize(UttWS &u, UttI p, int *gf);
	VOID izedet(UttWS &u, UttI p, int *gf);
	VOID izeadb(UttWS &u, UttI p, int *gf);
	VOID adbadj(UttWS &u, UttI p, int *gf);
	VOID izeize(UttWS &u, UttI p, int *gf);
	VOID baitadi(UttWS &u, UttI p, int *gf);
	VOID joklgn(UttWS &u, UttI p, int *gf);
	VOID jokjok(UttWS &u, UttI p, int *gf);
	VOID trn(UttWS &u, UttI p, int *gf);
	VOID invpau(UttWS &u, UttI p, int *gf);
	VOID jnt(UttWS &u, UttI p, int *gf);
	void galdeg(UttWS &u);
};

#endif

/**********************************************************/

/*class LangEU_Pos : public Pos {
private:
	LangEU_Categ  categ;
	LangEU_GF	grupof;

public:
	virtual ~LangEU_Pos() {}; //needed to remove a warning
	BOOL create( VOID );

	VOID utt_pos( Utt *u );
	VOID utt_categ( Utt *u );
	VOID utt_gf( Utt *u );

	BOOL set( const CHAR *param, const CHAR *val );
	const CHAR *get( const CHAR *param );
};

#endif*/
