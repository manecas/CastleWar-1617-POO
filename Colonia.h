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
	bool recolheu;
	static int incrementaCor;
	int cor;
	vector<Ser*> seres; //Ponteiro porque os varios seres não cabem num vector<Ser>
	vector<Ser*> parias;
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
	bool addParia(Ser * s);
	void removeParias(int x, int y);
	void removeSeres(int x, int y);
	bool addEdificio(Edificio * e);
	bool mandouRecolher()const;
	void setMandouRecolher(bool mandouR);
	Edificio * pesquisaEdificioPorEid(int eid)const;
	Edificio * pesquisaEdificioPorTipo(int id)const; //Atencao nome
	Ser * pesquisaSerPorIndice(int indice)const; //Atencao nome
	Ser * pesquisaPariaPorIndice(int indice)const; //Atencao nome
	Edificio * pesquisaEdificioPorIndice(int indice)const;
	static void reiniciaCor();
	int pesquisaSer(int x, int y)const;
	int pesquisaParia(int x, int y)const;
	int pesquisaEdificio(int x, int y)const;
	void removeEdificios(int x, int y);
	int getMoedas()const;
	void setMoedas(int m);
	char getLetra()const;
	int getCor()const;

	void getPosicoesAdjacentes(vector<Posicao> & pos, int x, int y, Planicie * p);

	void getSeres(vector<Ser*> & ss);
	void getEdificios(vector<Edificio*> & ee);

	int fabricaSeres(int num, Perfil * p);
	int constroiEdificio(int id, int lin, int col, Planicie * p, bool debug);

	bool mudaCastelo(int x, int y, Planicie * p);
	void atuaAtaqueEdificio(Planicie * p);
	void atuaAtaqueSer(Planicie * p);
	int reparaEdificio(int eid);
	int updgradeEdificio(int eid);
	int venderEdificio(int eid);
	void elimina();

	string toString()const;
};

#endif // !_COLONIA

