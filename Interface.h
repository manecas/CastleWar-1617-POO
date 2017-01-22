#ifndef _INTERFACE
#define _INTERFACE

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <locale.h>
#include <cstdlib> //Ver isto
#include <vector>
#include "Erros.h"
#include "Constantes.h"

using std::string;
using std::istringstream;
using std::vector;
using std::cout;
using std::cin;
using std::ifstream;
using std::stoi;
using std::vector;

using namespace Erros;
using namespace Constantes;

class Planicie;

class Interface {
	Planicie *planicie;
	vector<Planicie*> jogosGuardados;
	bool iniciouJogo;
	bool definiuDimensao;
	bool definiuOponentes;
	bool definiuPerfil;
	int x, y; //Foco do utilizador
	string erro;
	bool usarEid;
	bool fimJogo;

public:
	Interface();
	virtual ~Interface();

	int pesquisaJogoGuardado(string nome);
	int guardaJogo(string nome);
	int apagaJogoGuardado(string nome);
	int carregaJogoGuardado(string nome);

	void interpretaLinha(string linha);
	bool lerComandosDeFicheiroDeTexto(string nomeFicheiro);

	void desenhaRetanguloVazio(int x, int y, int lin, int col)const;
	void listaCaracteristicas()const;
	void listaComandosConfiguracao()const;
	void listaParias()const;
	void listaCaracteristicasPerfilColonias();
	void listaCaracteristicasPerfil(); //Todos os perfis
	void listaCaracteristicasPerfil(char letra); //Por letra
	void listaColonia(char letra);
	void listaCoordenadasCastelos()const;
	void finalJogo(int codigo);
	void limpa()const;
	void reiniciaVariaveis();

	void desenhaPlanicie(int x, int y, int lin, int col)const;
	void desenhaSeresEdificios(int x, int y, int lin, int col)const;

	void imprimeMensagens(int codigo);

	void iniciaJogo();
	void configuraJogo();
	void menuInicial();
};

#endif // !_INTERFACE

