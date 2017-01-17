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

Interface::Interface() : iniciouJogo(false), definiuDimensao(false), x(0), y(0), 
erro(""), fimJogo(false) { }

Interface::~Interface() { /*delete planicie;*/ }

int Interface::guardaJogo(string nome){
	
	if (planicie != nullptr) {
		planicie->setNome(nome);
		Planicie *copia = new Planicie(*planicie);
		if (copia == nullptr)
			return -1;

		jogosGuardados.push_back(copia);
		return 14;
	}
	return -1;
}

int Interface::pesquisaJogoGuardado(string nome){
	for (unsigned int i = 0; i < jogosGuardados.size(); i++){
		if (jogosGuardados[i]->getNome() == nome)
			return i;
	}

	return -1;
}

int Interface::apagaJogoGuardado(string nome){
	int i = pesquisaJogoGuardado(nome);
	if (i == -1)
		return 15;

	delete jogosGuardados[i];
	jogosGuardados.erase(jogosGuardados.begin() + i);
	return 16;
}

int Interface::carregaJogoGuardado(string nome){
	int i = pesquisaJogoGuardado(nome);
	if (i == -1)
		return 15;

	if (jogosGuardados[i] == nullptr)
		return -1;

	delete planicie;
	planicie = nullptr;
	planicie = new Planicie(*jogosGuardados[i]);
	return 17;
}

void Interface::interpretaLinha(string linha) {
	if (linha == "")
		return;

	istringstream in(linha);
	string comando;
	int resultado = -1;

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
				erro = "Tens de primeiro definir a dimensao da planicie!";
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
				erro = "Comando errado!";
				return;
			}
		}
	}
	else { //Ja comecou o jogo 		
		if (comando == "next") {
			int num;
			in >> num;
			if (!in)
				planicie->aumentaInstantes(1);
			else
				planicie->aumentaInstantes(num);
			//Os computadores vao fazer as suas jogadas
			//planicie->incrementaVezJogada();
			//Funcao que vai mandar todos os comandos
			planicie->atua();
		}
		else if(comando == "ser") {
			int num;
			char letraPerfil;
			in >> num >> letraPerfil;
			if (!in)
				return;
			resultado = planicie->fabricaSeres(num, letraPerfil);
		}
		else if (comando == "foco") {
			int x, y;
			in >> y >> x;
			if (!in)
				return;
			this->x = x;
			this->y = y;
		}
		else if (comando == "build") {
			int id, x, y;
			in >> id >> y >> x;
			if (!in)
				return;
			resultado = planicie->constroiEdificio(id, y, x);
		}
		else if (comando == "mkbuild") {
			int id, x, y;
			char letra;
			in >> id >> y >> x >> letra;
			if (!in)
				return;
			resultado = planicie->constroiEdificio(id, y, x, letra);
		}
		else if (comando == "setmoedas") {
			int moedas;
			char letra;
			in >> letra >> moedas;
			if (!in)
				return;
			resultado = planicie->setMoedas(letra, moedas);
		}
		else if (comando == "listp") {
			char letra;
			in >> letra;
			if (!in)
				return;
			listaCaracteristicasPerfil(letra);
		}
		else if (comando == "listallp") {
			listaCaracteristicasPerfilColonias();
		}
		else if (comando == "list") {
			char letra;
			in >> letra;
			if (!in)
				return;
			listaColonia(letra);
		}
		else if (comando == "repair") {
			int eid;
			in >> eid;
			if (!in)
				return;
			resultado = planicie->reparaEdificio(eid);
		}
		else if (comando == "upgrade") {
			int eid;
			in >> eid;
			if (!in)
				return;
			resultado = planicie->updgradeEdificio(eid);
		}
		else if (comando == "sell") {
			int eid;
			in >> eid;
			if (!in)
				return;
			resultado = planicie->venderEdificio(eid);
		}
		else if (comando == "save") {
			string nome;
			in >> nome;
			if (!in)
				return;
			resultado = guardaJogo(nome);
		}
		else if (comando == "restore") {
			string nome;
			in >> nome;
			if (!in)
				return;
			resultado = carregaJogoGuardado(nome);
		}
		else if (comando == "erase") {
			string nome;
			in >> nome;
			if (!in)
				return;
			resultado = apagaJogoGuardado(nome);
		}
		else if (comando == "fim") {
			iniciouJogo = false;
			definiuDimensao = false;
			x = 0;
			y = 0;
			erro = "";
			Edificio::reiniciaContador();
			Colonia::reiniciaCor();
			if (planicie != nullptr) {
				delete planicie;
				planicie = nullptr;
			}
			fimJogo = true;
		}
	}
	imprimeErros(resultado);
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

//Por fazer...
void Interface::listaCaracteristicasPerfilColonias(){
	//vector<Perfil*> p;
	//vector<Caracteristica*> c;
	//planicie->getPerfis(p);
	//int k = 1;
	////Percorrer o vector de perfis
	//for (unsigned int i = 0; i < p.size(); i++, k += 15) {
	//	Consola::gotoxy(k, 1);
	//	cout << "Perfil '" << p[i]->getLetra() << "'";

	//	p[i]->getCaracteristicas(c);
	//	//Para cada perfil percorrer o vector das suas caracteristicas
	//	for (unsigned int j = 0; j < c.size(); j++) {
	//		Consola::gotoxy(k, j + 3);
	//		cout << c[j]->getNome();
	//	}
	//	c.clear();
	//}
}

void Interface::listaCaracteristicasPerfil(){

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

void Interface::listaCaracteristicasPerfil(char letra) {
	limpa();
	Perfil * p = planicie->pesquisaPerfilPorLetra(letra);
	if (p == nullptr)
		return;

	vector<Caracteristica*> c;
	p->getCaracteristicas(c);

	//Percorrer o vector de perfis
	Consola::gotoxy(135, 1);
	cout << "Perfil '" << p->getLetra() << "'";
	Consola::gotoxy(130, 3);
	cout << "A(" << p->getTotalAtaque() << ") " <<
		"D(" << p->getTotalDefesa() << ") " <<
		"V(" << p->getTotalVelocidade() << ") " <<
		"C(" << p->getTotalPreco() << ")";

	//Para cada perfil percorrer o vector das suas caracteristicas
	for (unsigned int j = 0; j < c.size(); j++) {
		Consola::gotoxy(135, j + 5);
		cout << c[j]->getNome();
	}
}

void Interface::listaColonia(char letra){
	vector<Ser*> s;
	vector<Edificio*> e;
	Colonia *c = planicie->pesquisaColonia(letra);
	if (c == nullptr)
		return;

	limpa();
	c->getEdificios(e);
	c->getSeres(s);
	Consola::gotoxy(65, 1);
	cout << "      SERES";
	Consola::gotoxy(60, 3);
	cout << "Per  C  (x,y)  S   SM   A   D   V";
	int k = 5;
	for (unsigned int i = 0; i < s.size(); i++, k+=1) {
		Consola::gotoxy(60, k);
		cout << "'" << s[i]->getLetraPerfil() << "' ";
		cout << "'" << s[i]->getTotalPreco() << "' ";
		cout << "(" << s[i]->getX() << "," << s[i]->getY() << ") ";
		cout << "'" << s[i]->getSaude() << "' ";
		cout << "'" << s[i]->getSaudeMaxima() << "' ";
		cout << "'" << s[i]->getTotalAtaque() << "' ";
		cout << "'" << s[i]->getTotalDefesa() << "' ";
		cout << "'" << s[i]->getTotalVelocidade() << "' ";
	}

	Consola::gotoxy(115, 1);
	cout << "     EDIFICIOS";
	Consola::gotoxy(110, 3);
	cout << "EID   Nome     C  (x,y)  S    SM   A   D   C(UP)";
	k = 5;
	for (unsigned int i = 0; i < e.size(); i++, k += 1) {
		Consola::gotoxy(110, k);
		cout << "'" << e[i]->getEid() << "' ";
		cout << "'" << e[i]->getNome() << "' ";
		cout << "'" << e[i]->getCusto() << "' ";
		cout << "(" << e[i]->getX() << "," << e[i]->getY() << ") ";
		cout << "'" << e[i]->getSaude() << "' ";
		cout << "'" << e[i]->getSaudeMaxima() << "' ";
		cout << "'" << e[i]->getAtaque() << "' ";
		cout << "'" << e[i]->getDefesa() << "' ";
		cout << "'" << e[i]->getCustoUpgrade() << "' ";
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

void Interface::limpa() const{

	for (int i = 1; i < 39 ; i++){
		for (int j = 55; j < 159; j++){
			Consola::gotoxy(j, i);
			cout << " ";
		}

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
	}
	Consola::setBackgroundColor(Consola::PRETO);
	Colonia *colonia = planicie->pesquisaColonia(LETRAS[0]);
	if (colonia == nullptr)
		return;
	Consola::gotoxy(11, 30);
	cout << " \t \t";
	Consola::gotoxy(4, 30);
	cout << "Moedas: " << colonia->getMoedas();
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
			if (seres[j]->getX() <= col + x && seres[j]->getX() >= x 
				&& seres[j]->getY() <= lin + y && seres[j]->getY() >= y) {
				Consola::gotoxy(seres[j]->getX() - x + 4, seres[j]->getY() - y + 4);
				cout << seres[j]->getLetraPerfil();
				
			}
		}

		for (unsigned int k = 0; k < edi.size(); k++) {
			if (edi[k]->getX() <= col + x && edi[k]->getX() >= x && 
				edi[k]->getY() <= lin + y && edi[k]->getY() >= y) {
				Consola::gotoxy(edi[k]->getX() - x + 4, edi[k]->getY() - y + 4);
				cout << edi[k]->getEid();
			}
		}
		seres.clear();
		edi.clear();
	}

}

void Interface::imprimeErros(int codigo){

	switch (codigo){
		case NUM_SERES_INVALIDO:
			erro = "Introduz um numero valido de seres";
			break;
		case SEM_MOEDAS:
			erro = "Nao tens moedas suficientes";
			break;
		case FABRICO_SERES_OK:
			erro = "Conseguiste fabricar os seres";
			break;
		case SEM_CASTELO:
			erro = "O teu castelo foi destruido";
			break;
		case FORA_LIMITES_CASTELO:
			erro = "Fora do limite do castelo";
			break;
		case NUM_MOEDAS_INVALIDO:
			erro = "Numero de moedas invalido";
			break;
		case MOEDAS_OK:
			erro = "Processo efetuado com sucesso";
			break;
		case LIMITE_PLANICIE_INVALIDO:
			erro = "Limite da planicia invalido";
			break;
		case EDIFICIO_INVALIDO:
			erro = "Esse edificio nao existe";
			break;
		case EDIFICIO_OK:
			erro = "Processo efetuado com sucesso";
			break;
		case POSICAO_OCUPADA:
			erro = "Ja existe um ser ou um edificio nesse posicao";
			break;
		case LIMITE_COLONIA_INVALIDO:
			erro = "Fora dos limites da tua colonia";
			break;
		case NAO_PODE_REPARAR:
			erro = "Nao podes reparar o edifico porque ja esta no maximo";
			break;
		case VENDESTE_OK:
			erro = "Vendeste o edificio, estas rico";
			break;
		case JOGO_GUARDADO_OK:
			erro = "Guardaste o jogo com sucesso";
			break;
		case NOME_INVALIDO:
			erro = "Nao existe um jogo com esse nome";
			break;
		case JOGO_REMOVIDO:
			erro = "Removeste o jogo com sucesso";
			break;
		case JOGO_CARREGADO:
			erro = "Carregaste o jogo com sucesso";
			break;
		default:
			erro = "Erro de ponteiros..";
			break;
	}
}

void Interface::iniciaJogo(){
	Consola::clrscr();
	Consola::setScreenSize(40, 160); //X Y
	Consola::setTextColor(Consola::VERMELHO_CLARO);
	Consola::setBackgroundColor(Consola::PRETO);
	string linha, comando;

	while (true) {
		if (fimJogo) {
			return;
		}

		//listaCaracteristicas();
		desenhaPlanicie(4, 4, LINHAS, COLUNAS);
		desenhaSeresEdificios(x, y, LINHAS, COLUNAS);

		Consola::setTextColor(Consola::VERMELHO_CLARO);
		Consola::setBackgroundColor(Consola::PRETO);

		Consola::gotoxy(4, 38);
		cout << erro;

		Consola::gotoxy(13, 35);
		cout << " \t \t \t \t \t \t \t \t \t \t";

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
			lerComandosDeFicheiroDeTexto(nomeFich);
		}
		else {
			interpretaLinha(linha);
		}
	}
}

void Interface::configuraJogo() {
	Consola::clrscr();
	Consola::setScreenSize(40, 160); //X Y
	Consola::setTextColor(Consola::VERMELHO_CLARO);
	Consola::setBackgroundColor(Consola::PRETO);

	string linha, comando;

	while (true) {
		if (fimJogo) {
			return;
		}
		Consola::clrscr();
		Consola::setTextColor(Consola::VERMELHO_CLARO);
		Consola::setBackgroundColor(Consola::PRETO);

		listaCaracteristicas();
		if (definiuDimensao) {
			listaCaracteristicasPerfil();
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
			lerComandosDeFicheiroDeTexto(nomeFich);
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
	
	int opcao;

	while(true){
		if (fimJogo) {
			Consola::clrscr();
			Consola::setScreenSize(90, 50);
			Consola::setBackgroundColor(Consola::PRETO);
			Consola::setTextColor(Consola::VERDE_CLARO);
			fimJogo = false;
		}
		Consola::gotoxy(50, 5);
		cout << "Castle War\n";
		Consola::gotoxy(51, 8);
		cout << "1 - Jogar";
		Consola::gotoxy(51, 9);
		cout << "2 - Ajuda";
		Consola::gotoxy(51, 10);
		cout << "3 - Sair";

		Consola::gotoxy(58, 13);
		cout << " \t \t \t \t \t \t";
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
