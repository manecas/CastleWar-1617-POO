#ifndef _PLANICIE
#define _PLANICIE

#include <vector>
#include <string>
#include "Posicao.h"

using std::vector;
using std::string;

class Colonia;
class Perfil;
class Caracteristica;

class Planicie {
	string nomeJogo;
	int nLinhas;
	int nColunas;
	vector<Colonia*> colonias;
	vector<Perfil*> perfis;
	int instante;
	int vezJogada;

public:
	Planicie(int lin, int col);
	Planicie(const Planicie & ob);
	Planicie & operator=(const Planicie & ob);
	bool addColonias(int num);
	virtual ~Planicie();
	void atua();
	void setNome(string nome);
	string getNome()const;
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
	int pesquisaPerfil(char letra)const;
	Perfil *pesquisaPerfilPorLetra(char letra)const;

	void getPosicoesAdjacentes(vector<Posicao> & pos, int x, int y);

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
	int setMoedas(char letra, int moedas);
	int constroiEdificio(int id, int lin, int col);
	int constroiEdificio(int id, int lin, int col, char letra);
	int reparaEdificio(int eid);
	int updgradeEdificio(int eid);
	int venderEdificio(int eid);

};

#endif // !_PLANICIE