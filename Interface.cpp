#include "Interface.h"
#include "Planicie.h"
#include "Consola.h"
#include "Perfil.h"
#include "Caracteristica.h"
#include "Edificio.h"
#include "Ser.h"
#include "Colonia.h"

Interface::Interface() : iniciouJogo(false), definiuDimensao(false), x(0), y(0), 
erro(""), fimJogo(false), usarEid(true) { }

Interface::~Interface() { 
	if(planicie != nullptr)
		delete planicie;

	for (unsigned i = 0; i < jogosGuardados.size(); i++) {
		delete jogosGuardados[i];
	}
	jogosGuardados.clear();
}

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
				resultado = 22;
			}
			else {
				resultado = 23;
			}
		}
		else { //Ja definiu dimensoes
			if (comando == "moedas") {
				int moedas;
				in >> moedas;
				if (!in)
					return;
				resultado = planicie->setMoedas(moedas);
			}
			else if (comando == "oponentes") {
				int num;
				in >> num;
				if (!in)
					return;
				resultado = planicie->addColonias(num);
			}
			else if (comando == "castelo") {
				char letraCol;
				int lin, col;
				in >> letraCol >> lin >> col;
				if (!in)
					return;
				resultado = planicie->mudaCastelo(letraCol, lin, col);
			}
			else if (comando == "mkperfil") {
				char letraPerfil;
				in >> letraPerfil;
				if (!in)
					return;
				resultado = planicie->criaPerfil(letraPerfil);
			}
			else if (comando == "addperfil") {
				char letraPerfil;
				int idCarac;
				in >> letraPerfil >> idCarac;
				if (!in)
					return;
				resultado = planicie->addCaracteristica(idCarac, letraPerfil);
			}
			else if (comando == "subperfil") {
				char letraPerfil;
				int idCarac;
				in >> letraPerfil >> idCarac;
				if (!in)
					return;
				resultado = planicie->removeCaracteristica(idCarac, letraPerfil);
			}
			else if (comando == "rmperfil") {
				char letraPerfil;
				in >> letraPerfil;
				if (!in)
					return;
				resultado = planicie->removePerfil(letraPerfil);
			}
			else if (comando == "inicio") {
				iniciouJogo = true; //Aqui sabemos que ja comecou o jogo
				planicie->sortearPerfisComputador();
				iniciaJogo();
			}
			else {
				resultado = 101;
			}
		}
	}
	else { //Ja comecou o jogo 		
		if (comando == "next") {
			int num;
			in >> num;
			if (!in) {
				planicie->sortearComandoComputador();
				resultado = planicie->atua();
			}
			else {
				for (int i = 0; i < num; i++){
					planicie->sortearComandoComputador();
					resultado = planicie->atua();
				}
			}
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
			resultado = 36;
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
		else if (comando == "changecarac") {
			if (usarEid)
				usarEid = false;
			else
				usarEid = true;
		}
		else if (comando == "listparias") {
			listaParias();
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
		else if (comando == "ataca") {
			resultado = planicie->setModoAtaque();
		}
		else if (comando == "recolhe") {
			resultado = planicie->setModoRecolhe();
		}
		else if (comando == "fim") {
			fimJogo = true;
		}
		else {
			resultado = 101;
		}
	}
	imprimeMensagens(resultado);
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

void Interface::desenhaRetanguloVazio(int x, int y, int lin, int col)const{

	for (int i = y; i <= lin; i++) {
		for (int j = x; j <= col; j++) {
			Consola::gotoxy(j, i);
			if (i == y || i == lin)
				cout << char(205);
			else if (j == x || j == col)
				cout << char(186);

			Consola::gotoxy(j, i);
			if (i == y && j == x)
				cout << char(201);
			else if (i == y && j == col)
				cout << char(187);
			else if (i == lin && j == col)
				cout << char(188);
			else if (i == lin && j == x)
				cout << char(200);
		}
	}
}

void Interface::listaCaracteristicas()const {
	Consola::gotoxy(110, 2);
	cout << "CARACTERISTICAS";
	Consola::gotoxy(82, 4);
	cout << "Id" << "    Nome" << "     $(In-game)" << "  $(Forca)";
	Consola::gotoxy(82, 5);
	cout << "1" << "   Bandeira" << "       1" << "          0";
	Consola::gotoxy(82, 6);
	cout << "2" << "   Superior" << "       1" << "          1" << "   +1 SaudeM";
	Consola::gotoxy(82, 7);
	cout << "3" << "   PeleDura" << "       2" << "          2" << "   +1 Defesa";
	Consola::gotoxy(82, 8);
	cout << "4" << "   Armadura" << "       2" << "          3" << "   +2 Defesa";
	Consola::gotoxy(82, 9);
	cout << "5" << "   Faca" << "           1" << "          1" << "   +1 Ataque";
	Consola::gotoxy(82, 10);
	cout << "6" << "   Espada" << "         2" << "          2" << "   +2 Ataque  +1 nos dois primeiros Ataques";
	Consola::gotoxy(82, 11);
	cout << "7" << "   Agressao" << "       1" << "          1" << "   Ataca seres inimigos";
	Consola::gotoxy(82, 12);
	cout << "8" << "   Ecologico" << "      1" << "          1" << "   Ataca edificios inimigos";
	Consola::gotoxy(82, 13);
	cout << "9" << "   HeatSeeker" << "     1" << "          1" << "   Procura ser inigimo mais proximo";
	Consola::gotoxy(82, 14);
	cout << "10" << "  BuildSeeker" << "    1" << "          1" << "   Procura edificio inigimo mais proximo";
	Consola::gotoxy(82, 15);
	cout << "11" << "  Walker" << "         1" << "          1" << "   Anda ao calhas";
	Consola::gotoxy(82, 16);
	cout << "12" << "  Remedio" << "        2" << "          1" << "   +2 Saude quando ser tem <= 3 Saude";
	Consola::gotoxy(82, 17);
	cout << "13" << "  SecondChance" << "   3" << "          0" << "   Segunda vida quando morre";
	Consola::gotoxy(82, 18);
	cout << "14" << "  Aluno" << "          10" << "         4" << "   Tem 3 vidas. Quando morre +5(A) e +5(Def)";

	desenhaRetanguloVazio(80, 0, 20, 159);
}

void Interface::listaComandosConfiguracao() const{
	Consola::gotoxy(95, 23);
	cout << "COMANDOS";
	Consola::gotoxy(82, 25);
	cout << "dim linhas colunas ";
	Consola::gotoxy(82, 26);
	cout << "moedas numero";
	Consola::gotoxy(82, 27);
	cout << "dim linhas colunas";
	Consola::gotoxy(82, 28);
	cout << "castelo colonia lin col";
	Consola::gotoxy(82, 29);
	cout << "mkperfil letra";
	Consola::gotoxy(82, 30);
	cout << "addperfil letra caracteristica(id)";
	Consola::gotoxy(82, 31);
	cout << "subperfil letra caracteristica(id)";
	Consola::gotoxy(82, 32);
	cout << "rmperfil letra";
	Consola::gotoxy(82, 33);
	cout << "load ficheiro(nome)";

	desenhaRetanguloVazio(80, 21, 35, 121);
}

void Interface::listaParias() const{

	limpa();
	vector<Ser*> s;
	planicie->getParias(s);
	Consola::gotoxy(65, 1);
	cout << "      PARIAS";
	Consola::gotoxy(60, 3);
	cout << "Per  C   (x,y)  S    SM   A   D";
	int k = 1;
	for (unsigned int i = 0; i < s.size(); i++, k += 1) {
		Consola::gotoxy(60, k + 5);
		cout << "'" << s[i]->getLetraPerfil() << "' ";
		cout << "'" << s[i]->getTotalPreco() << "' ";
		cout << "(" << s[i]->getX() << "," << s[i]->getY() << ") ";
		cout << "'" << s[i]->getSaude() << "' ";
		cout << "'" << s[i]->getSaudeMaxima() << "' ";
		cout << "'" << s[i]->getTotalAtaque() << "' ";
		cout << "'" << s[i]->getTotalDefesa() << "' ";
	}
}

void Interface::listaCaracteristicasPerfilColonias(){

	limpa();
	vector<Perfil*> p;
	vector<Caracteristica*> c;
	planicie->getPerfis(p);

	Consola::gotoxy(105, 1);
	cout << "PERFIS JOGADOR";
	int k = 70;
	//Percorrer o vector de perfis
	for (unsigned int i = 0; i < p.size(); i++, k += 17) {
		Consola::gotoxy(k, 3);
		cout << "Perfil '" << p[i]->getLetra() << "'";
		Consola::gotoxy(k - 2, 5);
		cout << "A(" << p[i]->getTotalAtaque() << ") ";
		cout << "D(" << p[i]->getTotalDefesa() << ") ";
		cout << "V(" << p[i]->getTotalVelocidade() <<") ";
		Consola::gotoxy(k, 6);
		cout << "SM(" << p[i]->getSaudeMaxima() << ") ";
		cout << "C(" << p[i]->getTotalPreco() << ")";
		p[i]->getCaracteristicas(c);
		//Para cada perfil percorrer o vector das suas caracteristicas
		for (unsigned int j = 0; j < c.size(); j++) {
			Consola::gotoxy(k, j + 8);
			cout << c[j]->getNome();
		}
		c.clear();
	}
	desenhaRetanguloVazio(65, 0, 19, 155);

	p.clear();
	planicie->getPerfisComputador(p);
	Consola::gotoxy(105, 21);
	cout << "PERFIS COMPUTADOR";
	k = 70;
	//Percorrer o vector de perfis
	for (unsigned int i = 0; i < p.size(); i++, k += 17) {
		Consola::gotoxy(k, 23);
		cout << "Perfil '" << p[i]->getLetra() << "'";
		Consola::gotoxy(k - 2, 25);
		cout << "A(" << p[i]->getTotalAtaque() << ") ";
		cout << "D(" << p[i]->getTotalDefesa() << ") ";
		cout << "V(" << p[i]->getTotalVelocidade() << ") ";
		Consola::gotoxy(k, 26);
		cout << "SM(" << p[i]->getSaudeMaxima() << ") ";
		cout << "C(" << p[i]->getTotalPreco() << ")";
		p[i]->getCaracteristicas(c);
		//Para cada perfil percorrer o vector das suas caracteristicas
		for (unsigned int j = 0; j < c.size(); j++) {
			Consola::gotoxy(k, j + 28);
			cout << c[j]->getNome();
		}
		c.clear();
	}
	desenhaRetanguloVazio(65, 20, 39, 155);
}

void Interface::listaCaracteristicasPerfil(){

	vector<Perfil*> p;
	vector<Caracteristica*> c;
	planicie->getPerfis(p);

	if(p.size() != 0)
		desenhaRetanguloVazio(0, 0, 15, 78);

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
	Consola::gotoxy(120, 3);
	cout << "Perfil '" << p->getLetra() << "'";
	Consola::gotoxy(115, 5);
	cout << "A(" << p->getTotalAtaque() << ") " <<
		"D(" << p->getTotalDefesa() << ") " <<
		"V(" << p->getTotalVelocidade() << ") " <<
		"SM(" << p->getSaudeMaxima() << ") " <<
		"C(" << p->getTotalPreco() << ")";

	//Para cada perfil percorrer o vector das suas caracteristicas
	for (unsigned int j = 0; j < c.size(); j++) {
		Consola::gotoxy(120, j + 7);
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
	cout << "Per  C   (x,y)  S    SM   A   D";
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
	}

	Consola::gotoxy(110, 1);
	cout << "     EDIFICIOS";
	Consola::gotoxy(100, 3);
	cout << "EID   Nome     C  (x,y)  S    SM   A   D   C(UP)";
	k = 5;
	for (unsigned int i = 0; i < e.size(); i++, k += 1) {
		Consola::gotoxy(100, k);
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

	Consola::gotoxy(87, 38);
	cout << " \t \t";
	Consola::gotoxy(80, 38);
	cout << "Moedas: " << c->getMoedas();
	Consola::gotoxy(92, 39);
	cout << " \t \t";
	Consola::gotoxy(80, 39);
	if (c->estaEmModoAtaque())
		cout << "Modo: Ataque";
	else
		cout << "Modo: Recolha";

}

void Interface::listaCoordenadasCastelos() const{

	Consola::gotoxy(1, 17);
	cout << "Castelo" << "  (x,y) / (col,lin)";
	for (int i = 0; i < planicie->getNumColonias(); i++) {
		Consola::gotoxy(2, i + 18);
		cout << " '" << planicie->pesquisaColonia(i)->getLetra() << "'";
		Consola::gotoxy(14, i + 18);
		int x = planicie->pesquisaColonia(i)->pesquisaEdificioPorTipo(1)->getX();
		int y = planicie->pesquisaColonia(i)->pesquisaEdificioPorTipo(1)->getY();
		cout << "(" << x << "," << y << ")";
	}
	desenhaRetanguloVazio(0, 16, 33, 60);
}

void Interface::finalJogo(int codigo) {
	Consola::clrscr();
	Consola::setScreenSize(40, 160); //X Y
	Consola::setBackgroundColor(Consola::PRETO);
	Consola::gotoxy(75, 20);
	if (codigo == GANHASTE) {
		Consola::setTextColor(Consola::VERDE_CLARO);
		cout << "GANHASTE O JOGO";
		Consola::gotoxy(70, 24);
		cout << "Pressiona uma tecla para continuar...";
	}
	else {
		Consola::setTextColor(Consola::VERMELHO_CLARO);
		cout << "PERDESTE O JOGO";
		Consola::gotoxy(70, 24);
		cout << "Pressiona uma tecla para continuar...";
	}
	fimJogo = true;
	Consola::getch();
}

void Interface::limpa() const{

	for (int i = 0; i < 40 ; i++){
		for (int j = 55; j < 159; j++){
			Consola::gotoxy(j, i);
			cout << " ";
		}

	}
}

void Interface::reiniciaVariaveis(){
	x = 0;
	y = 0;
	erro = "";
	Edificio::reiniciaContador();
	Colonia::reiniciaCor();
	if (planicie != nullptr) {
		delete planicie;
		planicie = nullptr;
	}
	fimJogo = false;
	iniciouJogo = false;
	definiuDimensao = false;
}

void Interface::desenhaPlanicie(int x, int y, int lin, int col) const {

	Consola::gotoxy(18, 2);
	cout << "MAPA DO JOGO";

	for (int i = y; i <= lin + y; i++) {
		for (int j = x; j <= col + x; j++) {
			Consola::gotoxy(j - x + 4, i - y + 4);
			if (planicie->verificaLimitePlanicie(j, i)) {
				if (i % 2 == 0 && j % 2 == 0) {
					Consola::setBackgroundColor(Consola::BRANCO);
					cout << " ";
				}
				else if(i % 2 == 0 && j % 2 != 0){
					Consola::setBackgroundColor(Consola::BRANCO_CLARO);
					cout << " ";
				}
				else if (i % 2 != 0 && j % 2 == 0) {
					Consola::setBackgroundColor(Consola::BRANCO_CLARO);
					cout << " ";
				}
				else if (i % 2 != 0 && j % 2 != 0) {
					Consola::setBackgroundColor(Consola::BRANCO);
					cout << " ";
				}
			}
			else {
				Consola::setBackgroundColor(Consola::CINZENTO);
				cout << " ";
			}
		}
	}
	Consola::setBackgroundColor(Consola::PRETO);
	Colonia *colonia = planicie->pesquisaColonia(LETRAS[0]);
	if (colonia == nullptr)
		return;
	Consola::gotoxy(11, 26);
	cout << " \t \t";
	Consola::gotoxy(4, 26);
	cout << "Moedas: " << colonia->getMoedas();
	Consola::gotoxy(16, 27);
	cout << " \t \t";
	Consola::gotoxy(4, 27);
	if (colonia->estaEmModoAtaque())
		cout << "Modo: Ataque";
	else
		cout << "Modo: Recolha";
}

void Interface::desenhaSeresEdificios(int x, int y, int lin, int col) const{

	vector<Ser*> seres;
	vector<Ser*> parias;
	vector<Edificio*> edi;

	planicie->getParias(parias);
	for (unsigned int j = 0; j < parias.size(); j++) {
		if (parias[j]->getX() <= col + x && parias[j]->getX() >= x
			&& parias[j]->getY() <= lin + y && parias[j]->getY() >= y) {

			if ((parias[j]->getY() - y + 4) % 2 == 0 && (parias[j]->getX() - x + 4) % 2 == 0) {
				Consola::setBackgroundColor(Consola::BRANCO);
			}
			else if ((parias[j]->getY() - y + 4) % 2 == 0 && (parias[j]->getX() - x + 4) % 2 != 0) {
				Consola::setBackgroundColor(Consola::BRANCO_CLARO);
			}
			else if ((parias[j]->getY() - y + 4) % 2 != 0 && (parias[j]->getX() - x + 4) % 2 == 0) {
				Consola::setBackgroundColor(Consola::BRANCO_CLARO);
			}
			else if ((parias[j]->getY() - y + 4) % 2 != 0 && (parias[j]->getX() - x + 4) % 2 != 0) {
				Consola::setBackgroundColor(Consola::BRANCO);
			}

			Consola::gotoxy(parias[j]->getX() - x + 4, parias[j]->getY() - y + 4);
			cout << parias[j]->getLetraPerfil();
		}
	}

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

				if ((seres[j]->getY() - y + 4) % 2 == 0 && (seres[j]->getX() - x + 4) % 2 == 0) {
					Consola::setBackgroundColor(Consola::BRANCO);
				}
				else if ((seres[j]->getY() - y + 4) % 2 == 0 && (seres[j]->getX() - x + 4) % 2 != 0) {
					Consola::setBackgroundColor(Consola::BRANCO_CLARO);
				}
				else if ((seres[j]->getY() - y + 4) % 2 != 0 && (seres[j]->getX() - x + 4) % 2 == 0) {
					Consola::setBackgroundColor(Consola::BRANCO_CLARO);
				}
				else if ((seres[j]->getY() - y + 4) % 2 != 0 && (seres[j]->getX() - x + 4) % 2 != 0) {
					Consola::setBackgroundColor(Consola::BRANCO);
				}

				Consola::gotoxy(seres[j]->getX() - x + 4, seres[j]->getY() - y + 4);
				cout << seres[j]->getLetraPerfil();
			}
		}

		for (unsigned int j = 0; j < edi.size(); j++) {
			if (edi[j]->getX() <= col + x && edi[j]->getX() >= x && 
				edi[j]->getY() <= lin + y && edi[j]->getY() >= y) {

				if ((edi[j]->getY() - y + 4) % 2 == 0 && (edi[j]->getX() - x + 4) % 2 == 0) {
					Consola::setBackgroundColor(Consola::BRANCO);
				}
				else if ((edi[j]->getY() - y + 4) % 2 == 0 && (edi[j]->getX() - x + 4) % 2 != 0) {
					Consola::setBackgroundColor(Consola::BRANCO_CLARO);
				}
				else if ((edi[j]->getY() - y + 4) % 2 != 0 && (edi[j]->getX() - x + 4) % 2 == 0) {
					Consola::setBackgroundColor(Consola::BRANCO_CLARO);
				}
				else if ((edi[j]->getY() - y + 4) % 2 != 0 && (edi[j]->getX() - x + 4) % 2 != 0) {
					Consola::setBackgroundColor(Consola::BRANCO);
				}

				Consola::gotoxy(edi[j]->getX() - x + 4, edi[j]->getY() - y + 4);
				if (usarEid)
					cout << edi[j]->getEid();
				else
					cout << edi[j]->getNome().at(0);
			}
		}
		seres.clear();
		edi.clear();
	}
}

void Interface::imprimeMensagens(int codigo){

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
			erro = "Fora dos limites da planicie";
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
		case MODO_RECOLHE_OK:
			erro = "Mandaste recolher os teus seres";
			break;
		case MODO_RECOLHE_INVALIDO:
			erro = "Os teus seres ja estao em modo recolhe";
			break;
		case MODO_ATAQUE_OK:
			erro = "Mandaste os teus seres atacarem";
			break;
		case MODO_ATAQUE_INVALIDO:
			erro = "Os teus seres ja estao em modo ataque";
			break;
		case DIM_DEFINIDO:
			erro = "Definiste a dimensao da planicie com sucesso";
			break;
		case DIM_POR_DEFINIR:
			erro = "Tens de primeiro definir a dimensao da planicie!";
			break;
		case NUM_OPONENTES_INVALIDO:
			erro = "O numero de oponentes que introduziste e invalido";
			break;
		case OPONENTES_OK:
			erro = "Os oponentes foram adicionados ao jogo, em cima podes ver os seus castelos";
			break;
		case MAX_PERFIS_ATINGIGO:
			erro = "Nao podes criar mais perfis, o maximo e 5";
			break;
		case PERFIL_JA_EXISTE:
			erro = "Ja existe um perfil com esse nome";
			break;
		case PERFIL_OK:
			erro = "Criaste o teu perfil com sucesso";
			break;
		case SEM_FORCA:
			erro = "Nao tens mais forca para adicionar caracteristicas";
			break;
		case ADD_CARACTERISTICA_OK:
			erro = "Adicionaste a caracteristica com sucesso";
			break;
		case PERFIL_NAO_EXISTE:
			erro = "Esse perfil nao existe";
			break;
		case REMOVE_CARACTERISTICA_OK:
			erro = "Removeste a caracteristica com sucesso";
			break;
		case CARACTERISTICA_NAO_EXISTE:
			erro = "Essa caracteristica nao existe";
			break;
		case REMOVE_PERFIL_OK:
			erro = "Removeste o perfil com sucesso";
			break;
		case FOCO_OK:
			erro = "Focaste o mapa para as nova linha e coluna inserida";
			break;
		case VENDER_CASTELO_INVALIDO:
			erro = "Nao podes vender o castelo";
			break;
		case PERDESTE:
			finalJogo(PERDESTE);
			break;
		case GANHASTE:
			finalJogo(GANHASTE);
			break;
		case LETRA_PERFIL_INVALIDA:
			erro = "Nao podes criar perfis com a letra 'i' ou 'j'";
			break;

		case COMANDO_NAO_RECONHECIDO:
			erro = "Comando não reconhecido";
			break;
		default:
			erro = "Mensagem nao conhecida..";
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

		desenhaPlanicie(x, y, LINHAS, COLUNAS);
		desenhaSeresEdificios(x, y, LINHAS, COLUNAS);

		Consola::setTextColor(Consola::VERMELHO_CLARO);
		Consola::setBackgroundColor(Consola::PRETO);

		Consola::gotoxy(4, 38);
		cout << erro << " \t \t \t \t \t";

		Consola::gotoxy(13, 35);
		cout << " \t \t \t \t \t \t \t";

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
			erro = "Carregaste os comandos do ficheiro!";
			lerComandosDeFicheiroDeTexto(nomeFich);
		}
		else {
			interpretaLinha(linha);
		}
	}
}

void Interface::configuraJogo() {
	Consola::clrscr();
	Consola::setScreenSize(42, 160); //X Y
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
		listaComandosConfiguracao();
		if (definiuDimensao) {
			listaCaracteristicasPerfil();
			listaCoordenadasCastelos();

			Colonia *colonia = planicie->pesquisaColonia(LETRAS[0]);
			if (colonia == nullptr)
				return;
			Consola::gotoxy(42, 17);
			cout << " \t";
			Consola::gotoxy(35, 17);
			cout << "Moedas: " << colonia->getMoedas();
		}

		Consola::gotoxy(4, 35);
		cout << "Podes configurar o jogo através de um ficheiro de texto";
		Consola::gotoxy(4, 36);
		cout << "Podes configurar jogo manualmente";

		Consola::gotoxy(4, 40);
		cout << erro;

		Consola::gotoxy(4, 38);
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
			reiniciaVariaveis();
		}

		Consola::gotoxy(50, 5);
		cout << "Castle War\n";
		Consola::gotoxy(51, 8);
		cout << "1 - Jogar";
		Consola::gotoxy(51, 9);
		cout << "2 - Sair";

		Consola::gotoxy(60, 13);
		cout << " \t \t \t \t";
		Consola::gotoxy(50, 13);
		cout << char(196) << char(62) << "Comando: ";
		cin >> opcao;

		while (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			Consola::gotoxy(50, 15);
			cout << "Opcao invalida \t";
			Consola::gotoxy(60, 13);
			cout << " \t \t \t \t";
			Consola::gotoxy(59, 13);
			cin >> opcao;
		}

		switch (opcao){
			case 1: configuraJogo(); break;
			case 2: return;
			default:
				Consola::gotoxy(50, 15);
				cout << "Opcao invalida \t";
				break;
		}
	}
}
