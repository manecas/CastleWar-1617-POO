#ifndef _COLONIA
#define _COLONIA

#include <vector>
#include <string>

using std::string;
using std::vector;

class Ser;
class Edificio;
class Planicie;
class Perfil;

class Colonia {
	int moedas;
	char letra;
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
	bool addEdificio(int id, int x, int y);
	Edificio * pesquisaEdificioPorEid(int eid)const;
	Edificio * pesquisaEdificioPorTipo(int id)const; //Atencao nome
	int pesquisaSer(int x, int y)const;
	int pesquisaEdificio(int x, int y)const;
	void removeEdificios(int x, int y);
	int getMoedas()const;
	void setMoedas(int m);
	char getLetra()const;
	int getCor()const;

	void getSeres(vector<Ser*> & ss);
	void getEdificios(vector<Edificio*> & ee);

	int fabricaSeres(int num, Perfil * p);

	bool mudaCastelo(int x, int y, Planicie * p);
	void atuaAtaqueEdificio(Planicie * p);
	void atuaAtaqueSer(Planicie * p);
	void elimina();

	string toString()const;
};

#endif // !_COLONIA

