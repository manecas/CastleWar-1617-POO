#include "Interface.h"
#include "Planicie.h"
#include "Consola.h"
#include "Perfil.h"
#include "Caracteristica.h"
#include "Edificio.h"
#include "Ser.h"
#include "Colonia.h"
#include "Constantes.h"

using namespace Constantes;

Interface::Interface() : iniciouJogo(false), definiuDimensao(false) { }

Interface::~Interface() { /*delete planicie;*/ }

void Interface::interpretaLinha(string linha) {
	if (linha == "")
		return;

	istringstream in(linha);
	string comando;

	in >> comando;
	if (!in)
		return;

	if (!iniciouJogo) { //Nao comecou o jogo ainda

		if (!definiuDimensao) { //Ainda nao definiu dimensoes
			if (comando == "dim") {
				int lin, col;
				in >> lin >> col;
				if (!in)
					return;
				planicie = new Planicie(lin, col);
				if (planicie == nullptr)
					return;
				definiuDimensao = true;
			}
			else {
				Consola::gotoxy(4, 38);
				cout << "Tens de primeiro definir a dimensao da planicie!";
			}
		}
		else { //Ja definiu dimensoes
			if (comando == "moedas") {
				int moedas;
				in >> moedas;
				if (!in)
					return;
				planicie->setMoedas(moedas);
			}
			else if (comando == "oponentes") {
				int num;
				in >> num;
				if (!in)
					return;
				planicie->addColonias(num);
			}
			else if (comando == "castelo") {
				char letraCol;
				int lin, col;
				in >> letraCol >> lin >> col;
				if (!in)
					return;
				planicie->mudaCastelo(letraCol, lin, col);
			}
			else if (comando == "mkperfil") {
				char letraPerfil;
				in >> letraPerfil;
				if (!in)
					return;
				planicie->criaPerfil(letraPerfil);
			}
			else if (comando == "addperfil") {
				char letraPerfil;
				int idCarac;
				in >> letraPerfil >> idCarac;
				if (!in)
					return;
				planicie->addCaracteristica(idCarac, letraPerfil);
			}
			else if (comando == "subperfil") {
				char letraPerfil;
				int idCarac;
				in >> letraPerfil >> idCarac;
				if (!in)
					return;
				planicie->removeCaracteristica(idCarac, letraPerfil);
			}
			else if (comando == "rmperfil") {
				char letraPerfil;
				in >> letraPerfil;
				if (!in)
					return;
				planicie->removePerfil(letraPerfil);
			}
			else if (comando == "inicio") {
				iniciouJogo = true; //Aqui sabemos que ja comecou o jogo
				iniciaJogo();
			}
			else {
				Consola::gotoxy(4, 38);
				cout << "Comando errado!";
				return;
			}
		}
	}
	else { //Ja comecou o jogo 		
		if (comando == "next") {
			int num;
			in >> num;
			if (!in)
				return;
			//Os computadores vao fazer as suas jogadas
			//planicie->incrementaVezJogada();
			//Funcao que vai mandar todos os comandos
			planicie->aumentaInstantes(num);
			planicie->atua();
		}
		else if(comando == "ser") {
			int num;
			char letraPerfil;
			in >> num >> letraPerfil;
			if (!in)
				return;
			int resultado = planicie->fabricaSeres(num, letraPerfil);
			Consola::gotoxy(4, 38);
			cout << "Resultado ao fabricar seres: " << resultado;
		}
	}
}

bool Interface::lerComandosDeFicheiroDeTexto(string nomeFicheiro) {
	ifstream dados(nomeFicheiro);
	string linha;

	if (!dados.is_open()) {
		return false;
	}

	// ler dados de todos os produtos
	// um produto por linha

	while (!dados.eof()) {
		// ler string com os dados do produto
		getline(dados, linha);
		// a funcao interpretaLinha chama-se para uma linha da dados
		// lida do teclado ou do ficheiro de texto
		interpretaLinha(linha);
	}
	dados.close();
	return true;
}

void Interface::listaCaracteristicas()const {
	Consola::gotoxy(110, 1);
	cout << "Id" << "    Nome" << "     Custo Monetário" << "     Custo Força";
	Consola::gotoxy(110, 2);
	cout << "1" << "   Bandeira" << "         1" << "                  0";
	Consola::gotoxy(110, 3);
	cout << "2" << "   Superior" << "         1" << "                  1";
	Consola::gotoxy(110, 4);
	cout << "3" << "   PeleDura" << "         2" << "                  2";
	Consola::gotoxy(110, 5);
	cout << "4" << "   Armadura" << "         2" << "                  3";
	Consola::gotoxy(110, 6);
	cout << "5" << "   Faca" << "             1" << "                  1";
	Consola::gotoxy(110, 7);
	cout << "6" << "   Espada" << "           2" << "                  2";
	Consola::gotoxy(110, 8);
	cout << "7" << "   Agressao" << "         1" << "                  1";
	Consola::gotoxy(110, 9);
	cout << "8" << "   Ecologico" << "        1" << "                  1";
	Consola::gotoxy(110, 10);
	cout << "9" << "   HeatSeeker" << "       1" << "                  1";
	Consola::gotoxy(110, 11);
	cout << "10" << "  BuildSeeker" << "      1" << "                  1";
	Consola::gotoxy(110, 12);
	cout << "11" << "  Walker" << "           1" << "                  1";
	Consola::gotoxy(110, 13);
	cout << "12" << "  Remedio" << "          2" << "                  1";
	Consola::gotoxy(110, 14);
	cout << "13" << "  SecondChance" << "     3" << "                  0";
	Consola::gotoxy(110, 15);
	cout << "14" << "  Aluno" << "            ?" << "                  ?";
}

void Interface::listaCaracteristicasPefil(){

	vector<Perfil*> p;
	vector<Caracteristica*> c;
	planicie->getPerfis(p);
	int k = 1;
	//Percorrer o vector de perfis
	for (unsigned int i = 0; i < p.size(); i++, k += 15){
		Consola::gotoxy(k, 1);
		cout << "Perfil '" <<  p[i]->getLetra() << "'";

		p[i]->getCaracteristicas(c);
		//Para cada perfil percorrer o vector das suas caracteristicas
		for (unsigned int j = 0; j < c.size(); j++){	
			Consola::gotoxy(k , j + 3);
			cout << c[j]->getNome();
		}
		c.clear();
	}
}

void Interface::listaCoordenadasCastelos() const{

	Consola::gotoxy(1, 14);
	cout << "Castelo" << "  Coordenada";
	for (int i = 0; i < planicie->getNumColonias(); i++) {
		Consola::gotoxy(2, i + 16);
		cout << " '" << planicie->pesquisaColonia(i)->getLetra() << "'";
		Consola::gotoxy(10, i + 16);
		int x = planicie->pesquisaColonia(i)->pesquisaEdificioPorTipo(1)->getX();
		int y = planicie->pesquisaColonia(i)->pesquisaEdificioPorTipo(1)->getY();
		cout << "(" << x << "," << y << ")";
	}

}

void Interface::desenhaPlanicie(int x, int y, int lin, int col) const{

	int c = 1;

	for (int i = y; i <= lin + y; i++){
		for (int j = x; j <= col + x; j++){
			Consola::gotoxy(j, i);
			if (c % 2 == 0) {
				Consola::setBackgroundColor(Consola::BRANCO);
				cout << " ";
			}
			else {
				Consola::setBackgroundColor(Consola::AMARELO);
				cout << " ";
			}
			c++;
		}
		if ((col + x) % 2 == 0)
			c++;
	}

	Consola::setBackgroundColor(Consola::PRETO);
}

void Interface::desenhaSeresEdificios(int x, int y, int lin, int col) const{

	vector<Ser*> seres;
	vector<Edificio*> edi;

	for (int i = 0; i < planicie->getNumColonias(); i++){
		Colonia *c = planicie->pesquisaColonia(i);
		if (c == nullptr)
			return;
		Consola::setTextColor(c->getCor());
		c->getSeres(seres);
		c->getEdificios(edi);

		for (unsigned int j = 0; j < seres.size(); j++){
			if (seres[j]->getX() < col && seres[j]->getY() < lin) {
				Consola::gotoxy(seres[j]->getX() + x, seres[j]->getY() + y);
				cout << seres[j]->getLetraPerfil();
				
			}
		}

		for (unsigned int k = 0; k < edi.size(); k++) {
			if (edi[k]->getX() < col && edi[k]->getY() < lin) {
				Consola::gotoxy(edi[k]->getX() + x, edi[k]->getY() + y);
				cout << edi[k]->getId();
			}
		}
		seres.clear();
		edi.clear();
	}

}

void Interface::iniciaJogo(){
	Consola::clrscr();
	Consola::setScreenSize(40, 160); //X Y
	Consola::setTextColor(Consola::VERMELHO_CLARO);
	Consola::setBackgroundColor(Consola::PRETO);
	string linha, comando, erro = "";

	while (true) {
		Consola::clrscr();

		//listaCaracteristicas();
		desenhaPlanicie(5, 5, 20, 101);
		desenhaSeresEdificios(5, 5, 20, 100);

		Consola::setTextColor(Consola::VERMELHO_CLARO);
		Consola::setBackgroundColor(Consola::PRETO);

		Consola::gotoxy(4, 38);
		cout << erro;

		Consola::gotoxy(4, 35);
		cout << "Comando: ";
		getline(cin, linha);

		istringstream in(linha);
		in >> comando;

		if (!in) {
			erro = "Comando Errado!";
			continue;
		}

		interpretaLinha(linha);
	}
}

void Interface::configuraJogo() {
	Consola::clrscr();
	Consola::setScreenSize(40, 160); //X Y
	Consola::setTextColor(Consola::VERMELHO_CLARO);
	Consola::setBackgroundColor(Consola::PRETO);

	string linha, comando, erro = "";

	while (true) {
		Consola::clrscr();
		Consola::setTextColor(Consola::VERMELHO_CLARO);
		Consola::setBackgroundColor(Consola::PRETO);

		listaCaracteristicas();
		if (definiuDimensao) {
			listaCaracteristicasPefil();
			listaCoordenadasCastelos();
		}

		Consola::gotoxy(4, 30);
		cout << "Castle War\n";
		Consola::gotoxy(4, 31);
		cout << "Podes configurar o jogo através de um ficheiro de texto";
		Consola::gotoxy(4, 32);
		cout << "Podes configurar jogo manualmente";
		Consola::gotoxy(4, 33);
		cout << "Podes pedir ajuda";

		Consola::gotoxy(4, 38);
		cout << erro;

		Consola::gotoxy(4, 35);
		cout << "Comando: ";
		getline(cin, linha);

		istringstream in(linha);
		in >> comando;

		if (!in) {
			erro = "Comando Errado!";
			continue;
		}

		if (comando == "load") {
			string nomeFich;
			in >> nomeFich;
			if (!in) {
				erro = "Erro: Precisas de escrever o nome do ficheiro!";
				return;
			}
			if (planicie == nullptr)
				lerComandosDeFicheiroDeTexto(nomeFich);
			else {
				delete planicie;
				definiuDimensao = false;
				iniciouJogo = false;
				lerComandosDeFicheiroDeTexto(nomeFich);
			}
		} //Comando nao e load
		else {
			interpretaLinha(linha);
		}
	}
}

void Interface::menuInicial(){
	Consola::clrscr();
	Consola::setScreenSize(90, 50);
	Consola::setBackgroundColor(Consola::PRETO);
	Consola::setTextColor(Consola::VERDE_CLARO);

	Consola::gotoxy(50, 5);
	cout << "Castle War\n";
	Consola::gotoxy(51, 8);
	cout << "1 - Jogar";
	Consola::gotoxy(51, 9);
	cout << "2 - Ajuda";
	Consola::gotoxy(51, 10);
	cout << "3 - Sair";
	int opcao;

	while(true){
		Consola::gotoxy(58, 13);
		cout << " \t\t\t\t\t\t";
		Consola::gotoxy(50, 13);
		cout << "Comando:";
		cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX);
			Consola::gotoxy(50, 15);
			cout << "Insira um número de 1 a 3 \t\t\t\t\t\t\t\t";
			continue;
		}

		switch (opcao){
			case 1: configuraJogo(); break;
			case 2: break; //Ajuda
			case 3: return;
			default:
				Consola::gotoxy(50, 15);
				cout << "Comando errado \t\t\t\t\t\t\t\t\t\t\t";
				continue;
		}
	}
}
