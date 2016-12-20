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

using std::string;
using std::istringstream;
using std::vector;
using std::cout;
using std::cin;
using std::ifstream;
using std::stoi;
using std::vector;

class Planicie;

class Interface {
	Planicie *planicie;
	bool iniciouJogo;
	bool definiuDimensao;

public:
	Interface();
	virtual ~Interface();
	void interpretaLinha(string linha);
	bool lerComandosDeFicheiroDeTexto(string nomeFicheiro);

	void listaCaracteristicas()const;
	void listaCaracteristicasPefil();
	void listaCoordenadasCastelos()const;

	void desenhaPlanicie(int x, int y, int lin, int col)const;
	void desenhaSeresEdificios(int x, int y, int lin, int col)const;

	void iniciaJogo();
	void configuraJogo();
	void menuInicial();

};

#endif // !_INTERFACE

