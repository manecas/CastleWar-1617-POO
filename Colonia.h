#ifndef _COLONIA
#define _COLONIA

#include <vector>
#include <string>
#include "Posicao.h"

using std::string;
using std::vector;

class Ser;
class Edificio;
class Planicie;
class Perfil;

class Colonia {
	int moedas;
	char letra;
	bool modoAtaque; //Recolher & Atacar
	static int incrementaCor;
	int cor;
	vector<Ser*> seres; //Ponteiro porque os varios seres não cabem num vector<Ser>
	vector<Edificio*> edificios; //Ponteiro porque os varios edificios não cabem num vector<Edificio>

	bool verificaInterseccaoCastelo(int xNovo, int yNovo, Planicie * p)const;
	bool verificaLimitePlanicie(int xNovo, int yNovo, Planicie * p)const;
	bool verificaLimiteColonia(int xNovo, int yNovo, Planicie * p)const;	

public:
	Colonia(char l , Planicie * p);
	Colonia(const Colonia & ob);
	Colonia & operator=(const Colonia & ob);
	virtual ~Colonia();
	bool addSer(Ser * s);
	void removeSeres(int x, int y);
	bool addEdificio(Edificio * e);
	bool estaEmModoAtaque()const;
	Edificio * pesquisaEdificioPorEid(int eid)const;
	Edificio * pesquisaEdificioPorTipo(int id)const; //Atencao nome
	Ser * pesquisaSerPorIndice(int indice)const; //Atencao nome
	Edificio * pesquisaEdificioPorIndice(int indice)const;
	static void reiniciaCor();
	int pesquisaSer(int x, int y)const;
	int pesquisaEdificio(int x, int y)const;
	void removeEdificios(int x, int y);
	int getMoedas()const;
	void setMoedas(int m);
	char getLetra()const;
	int getCor()const;

	bool verificaMovimentoSerXY(int xDest, int yDest);
	bool atacaSeresEdificiosAdjacentes(int x, int y, int forcaAta, Colonia * c);
	bool atacaSeresAdjacentes(int x, int y, int forcaAta, Colonia * c);
	bool atacaEdificiosAdjacentes(int x, int y, int forcaAta, Colonia * c);
	bool getPosicoesAdjacentes(int x, int y, vector<Posicao> & pos);
	void getSeresInimigos(vector<Ser*> & inimigos, Colonia * c);
	void getEdificiosInimigos(vector<Edificio*> & inimigos, Colonia * c);

	void getSeres(vector<Ser*> & ss);
	void getEdificios(vector<Edificio*> & ee);

	int fabricaSeres(int num, Perfil * p, Planicie * planicie);
	int constroiEdificio(int id, int lin, int col, Planicie * p, bool debug);

	int mudaCastelo(int x, int y, Planicie * p);
	void atuaAtaqueEdificio(Planicie * p);
	void atuaAtaqueSer(Planicie * p);
	int reparaEdificio(int eid);
	int updgradeEdificio(int eid);
	int venderEdificio(int eid);
	void elimina();
	int setModoRecolhe();
	int setModoAtaque();

	string toString()const;
};

#endif // !_COLONIA

