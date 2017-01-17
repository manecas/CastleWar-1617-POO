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
#include "Constantes.h"
#include "Erros.h"

using std::string;
using std::istringstream;
using std::vector;
using std::cout;
using std::cin;
using std::ifstream;
using std::stoi;
using std::vector;

using namespace Constantes;
using namespace Erros;

class Planicie;

class Interface {
	Planicie *planicie;
	vector<Planicie*> jogosGuardados;
	bool iniciouJogo;
	bool definiuDimensao;
	int x, y; //Foco do utilizador
	string erro;
	bool fimJogo;

public:
	Interface();
	virtual ~Interface(); //Ver isto

	int pesquisaJogoGuardado(string nome);
	int guardaJogo(string nome);
	int apagaJogoGuardado(string nome);
	int carregaJogoGuardado(string nome);

	void interpretaLinha(string linha);
	bool lerComandosDeFicheiroDeTexto(string nomeFicheiro);

	void listaCaracteristicas()const;
	void listaCaracteristicasPerfilColonias();
	void listaCaracteristicasPerfil(); //Todos os perfis
	void listaCaracteristicasPerfil(char letra); //Por letra
	void listaColonia(char letra);
	void listaCoordenadasCastelos()const;
	void limpa()const;

	void desenhaPlanicie(int x, int y, int lin, int col)const;
	void desenhaSeresEdificios(int x, int y, int lin, int col)const;

	void imprimeErros(int codigo);

	void iniciaJogo();
	void configuraJogo();
	void menuInicial();

};

#endif // !_INTERFACE

