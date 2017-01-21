#ifndef _PLANICIE
#define _PLANICIE

#include <vector>
#include <string>
#include "Posicao.h"
#include "Constantes.h"

using std::vector;
using std::string;
using namespace Constantes;

class Colonia;
class Perfil;
class Caracteristica;
class Ser;
class Edificio;

class Planicie {
	string nomeJogo;
	int nLinhas;
	int nColunas;
	vector<Colonia*> colonias;
	vector<Ser*> parias;
	vector<Perfil*> perfis;
	vector<Perfil*> perfisComputador;

public:
	Planicie(int lin, int col);
	Planicie(const Planicie & ob);
	Planicie & operator=(const Planicie & ob);
	virtual ~Planicie();
	int atua();
	void setNome(string nome);
	string getNome()const;
	void setNLinhas(int lin);
	void setNColunas(int col);
	int getNLinhas()const;
	int getNColunas()const;
	int getNumColonias()const;
	Colonia *pesquisaColonia(char letra)const;
	Colonia *pesquisaColonia(int indice)const;
	bool verificaLimitePlanicie(int xNovo, int yNovo)const;
	int pesquisaPerfil(char letra)const;
	Perfil *pesquisaPerfilPorLetra(char letra)const;
	bool addParia(Ser * s);
	void removeParias(int x, int y);
	int pesquisaParia(int x, int y)const;
	Ser * pesquisaPariaPorIndice(int indice)const; 

	void getSeres(vector<Ser*> & ss);
	void getParias(vector<Ser*> & pp);
	void getEdificios(vector<Edificio*> & ee);

	bool verificaMovimentoSerXY(int xDest, int yDest);
	bool atacaSeresEdificiosAdjacentes(int x, int y, int forcaAta, Colonia * c);
	bool atacaSeresAdjacentes(int x, int y, int forcaAta, Colonia * c);
	bool atacaEdificiosAdjacentes(int x, int y, int forcaAta, Colonia * c);
	void getPosicoesAdjacentes(int x, int y, vector<Posicao> & pos);
	void getSeresInimigos(vector<Ser*> & inimigos, Colonia * c);
	void getEdificiosInimigos(vector<Edificio*> & inimigos, Colonia * c);

	//Comandos configuracao
	void getPerfis(vector<Perfil*> & perf);
	void getPerfisComputador(vector<Perfil*> & perf);
	int criaPerfil(char letra);
	int addColonias(int num);
	int removePerfil(char letra);
	int addCaracteristica(int id, char letraPerfil);
	int removeCaracteristica(int id, char letraPerfil);
	int setMoedas(int moedas);


	//Computador
	void sortearPerfisComputador();
	void sortearComandoComputador();
	void sortearContrucaoEdificio(Colonia * c);
	void sortearReparacaoEdificio(Colonia * c);
	void sortearUpgradeEdificio(Colonia * c);
	void sortearFabricacaoSeres(Colonia * c);
	void sortearModoAtaqueRecolhe(Colonia * c);
	void sortearVendaEdificio(Colonia * c, Edificio * e);

	int verificaFinalJogo();
	int mudaCastelo(char letra, int lin, int col);

	//Comandos simulacao
	int fabricaSeres(int num, char letraPerfil);
	int setMoedas(char letra, int moedas);
	int constroiEdificio(int id, int lin, int col);
	int constroiEdificio(int id, int lin, int col, char letra);
	int reparaEdificio(int eid);
	int updgradeEdificio(int eid);
	int venderEdificio(int eid);
	int setModoRecolhe();
	int setModoAtaque();

};

#endif // !_PLANICIE