#ifndef _PLANICIE
#define _PLANICIE

#include <vector>

using std::vector;

class Colonia;
class Perfil;
class Caracteristica;

class Planicie {
	int nLinhas;
	int nColunas;
	vector<Colonia*> colonias;
	vector<Perfil*> perfis;
	int instante;
	int vezJogada;

	int pesquisaPerfil(char letra)const;
public:
	Planicie(int lin, int col);
	Planicie(const Planicie & ob);
	Planicie & operator=(const Planicie & ob);
	bool addColonias(int num);
	virtual ~Planicie();
	void atua();
	void setNLinhas(int lin);
	void setNColunas(int col);
	void incrementaVezJogada();
	int getNLinhas()const;
	int getNColunas()const;
	int getNumColonias()const;
	int getInstantes()const;
	Colonia *pesquisaColonia(char letra)const;
	Colonia *pesquisaColonia(int indice)const;
	bool verificaLimitePlanicie(int xNovo, int yNovo)const;

	//Comandos configuracao
	void getPerfis(vector<Perfil*> & perf);
	bool criaPerfil(char letra);
	bool removePerfil(char letra);
	bool addCaracteristica(int id, char letraPerfil);
	bool removeCaracteristica(int id, char letraPerfil);
	void setMoedas(int moedas);
	//Verificar depois
	bool mudaCastelo(char letra, int lin, int col);

	//Comandos simulacao
	void aumentaInstantes(int num);
	int fabricaSeres(int num, char letraPerfil);

	
};

#endif // !_PLANICIE