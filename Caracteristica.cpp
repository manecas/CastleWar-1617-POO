#include "Constantes.h"
using namespace Constantes;

#include "Caracteristica.h"
#include "Ser.h"
#include "Planicie.h"
#include "Edificio.h"
#include "Colonia.h"

#include <sstream>
using std::ostringstream;

Caracteristica::Caracteristica(const string & n, int iden, int custoM, int custoF, bool us):
	nome(n), id(iden), custoMonetario(custoM), custoForca(custoF), usou(us) { }

string Caracteristica::getNome() const { return nome; }

int Caracteristica::getId() const { return id; }

int Caracteristica::getCustoMonetario() const { return custoMonetario; }

int Caracteristica::getCustoForca() const { return custoForca; }

bool Caracteristica::jaUsou() const { return usou; }

void Caracteristica::setUsou(bool us) { usou = us; }

string Caracteristica::toString() const{
	ostringstream out;
	out << id << " - " << nome << " custo monetario: " << custoMonetario
		<< " custo forca: " << custoForca << "\n";
	return out.str();
}

//BANDEIRA
Bandeira::Bandeira() : Caracteristica("Bandeira" , 1, 1, 0, false){ }

int Bandeira::getSaudeMaxima() const{ return 0; }

int Bandeira::getAtaque(){ return 0; }

int Bandeira::getDefesa() const { return 0; }

int Bandeira::getVelocidade() const{ return 0; }

//bool Caracteristica::operator==(const Caracteristica * const c) const {
//	if (id == c->getId())
//		return true;
//	return false;
//}

void Bandeira::efeito(Ser * s, Colonia * c,  Planicie * p){
	
}

Caracteristica * Bandeira::duplica() const{ return new Bandeira(*this); }

//SUPERIOR
Superior::Superior() : Caracteristica("Superior", 2, 1, 1, false), saudeMax(1){ }

int Superior::getSaudeMaxima() const { return saudeMax; }

int Superior::getAtaque() { return 0; }

int Superior::getDefesa() const { return 0; }

int Superior::getVelocidade() const { return 0; }

void Superior::efeito(Ser * s, Colonia * c,  Planicie * p){ }

Caracteristica * Superior::duplica() const{ return new Superior(*this); }


//PELEDURA
PeleDura::PeleDura() : Caracteristica("PeleDura", 3, 2, 2, false), defesa(1){ }

int PeleDura::getSaudeMaxima() const { return 0; }

int PeleDura::getAtaque() { return 0; }

int PeleDura::getDefesa() const { return defesa; }

int PeleDura::getVelocidade() const { return 0; }

void PeleDura::efeito(Ser * s, Colonia * c,  Planicie * p) { }

Caracteristica * PeleDura::duplica() const{ return new PeleDura(*this); }


//ARMADURA
Armadura::Armadura() : Caracteristica("Armadura", 4, 2, 3, false), defesa(2){ }

int Armadura::getSaudeMaxima() const { return 0; }

int Armadura::getAtaque() { return 0; }

int Armadura::getDefesa() const { return defesa; }

int Armadura::getVelocidade() const { return 0; }

void Armadura::efeito(Ser * s, Colonia * c,  Planicie * p) { }

Caracteristica * Armadura::duplica() const{ return new Armadura(*this); }


//FACA
Faca::Faca() : Caracteristica("Faca", 5, 1, 1, false), ataque(1) { }

int Faca::getSaudeMaxima() const { return 0; }

int Faca::getAtaque() { return ataque; }

int Faca::getDefesa() const { return 0; }

int Faca::getVelocidade() const { return 0; }

void Faca::efeito(Ser * s, Colonia * c,  Planicie * p) { }

Caracteristica * Faca::duplica() const{ return new Faca(*this); }


//ESPADA
Espada::Espada() : Caracteristica("Espada",6, 2, 2, false), ataque(2),
ataqueIncremento(1), decrementou(false){ }

int Espada::getSaudeMaxima() const { return 0; }

int Espada::getAtaque() { return ataque; }

int Espada::getDefesa() const { return 0; }

int Espada::getVelocidade() const { return 0; }

void Espada::efeito(Ser * s, Colonia * c,  Planicie * p) {

	if (s == nullptr || c == nullptr)
		return;

	if (!jaUsou()) {
		if (s->getNumAtaques() == 1) {
			s->aumentaAtaque(ataqueIncremento);
			decrementou = false;
		}
		else if (s->getNumAtaques() == 2) {
			setUsou(true);
		}
	}
	else {
		if (!decrementou) {
			s->diminuiAtaque(ataqueIncremento);
			decrementou = true;
		}
	}
}

Caracteristica * Espada::duplica() const{ return new Espada(*this); }


//AGRESSAO
Agressao::Agressao() : Caracteristica("Agressao", 7, 1, 1, false), distAtaque(1) { }

int Agressao::getSaudeMaxima() const { return 0; }

int Agressao::getAtaque() { return 0; }

int Agressao::getDefesa() const { return 0; }

int Agressao::getVelocidade() const { return 0; }

void Agressao::efeito(Ser * s, Colonia * c,  Planicie * p) {
	if (c == nullptr || p == nullptr)
		return;

	int x = s->getX();
	int y = s->getY();

	for (int i = y - distAtaque; i <= y + distAtaque; i++) { //Linhas
		for (int j = x - distAtaque; j <= x + distAtaque; j++) { //Colunas
			if (i == y && j == x)
				continue;
			else {
				if (p->atacaSeresAdjacentes(j, i, s->getTotalDefesa(), c)) {
					s->aumentaNumAtaques(1);
					return;
				}
			}
		}
	}
}

Caracteristica * Agressao::duplica() const{ return new Agressao(*this); }


//ECOLOGICO
Ecologico::Ecologico() : Caracteristica("Ecologico", 8, 1, 1, false), distAtaque(1) { }

int Ecologico::getSaudeMaxima() const { return 0; }

int Ecologico::getAtaque() { return 0; }

int Ecologico::getDefesa() const { return 0; }

int Ecologico::getVelocidade() const { return 0; }

void Ecologico::efeito(Ser * s, Colonia * c,  Planicie * p) {
	if (c == nullptr || p == nullptr)
		return;

	int x = s->getX();
	int y = s->getY();

	for (int i = y - distAtaque; i <= y + distAtaque; i++) { //Linhas
		for (int j = x - distAtaque; j <= x + distAtaque; j++) { //Colunas
			if (i == y && j == x)
				continue;
			else {
				if (p->atacaEdificiosAdjacentes(j, i, s->getTotalAtaque(), c)) {
					s->aumentaNumAtaques(1);
					return;
				}
			}
		}
	}
}

Caracteristica * Ecologico::duplica() const{ return new Ecologico(*this); }


//HEATSEEKER
HeatSeeker::HeatSeeker() : Caracteristica("HeatSeeker", 9, 1, 1, false), velocidade(1) { }

int HeatSeeker::getSaudeMaxima() const { return 0; }

int HeatSeeker::getAtaque() { return 0; }

int HeatSeeker::getDefesa() const { return 0; }

int HeatSeeker::getVelocidade() const { return velocidade; }

void HeatSeeker::efeito(Ser * s, Colonia * c,  Planicie * p) {
	if (s == nullptr || p == nullptr)
		return;

	int x = s->getX();
	int y = s->getY();
	vector<Posicao> pos;
	vector<Ser*> inimigos;

	p->getSeresInimigos(inimigos, c);

	if (inimigos.size() == 0) {
		Edificio *e = c->pesquisaEdificioPorTipo(ID_CASTELO);
		if (e == nullptr)
			return;

		Posicao *posicao = Posicao::getPosicaoMovimento(x, y, e->getX(), e->getY());
		if (posicao == nullptr)
			return;

		if (posicao->getX() == e->getX() && posicao->getY() == e->getY()) {
			s->setX(posicao->getX());
			s->setY(posicao->getY());
		}
		else if (p->verificaMovimentoSerXY(posicao->getX(), posicao->getY())) {
			s->setX(posicao->getX());
			s->setY(posicao->getY());
		}
		return;
	}

	Posicao::getPosicoesSeres(inimigos, pos);
	Posicao *maisPro = Posicao::inimigoMaisProximo(pos, s->getX(), s->getY());

	if (maisPro == nullptr)
		return;
	
	Posicao *posicao = Posicao::getPosicaoMovimento(x, y, maisPro->getX(), maisPro->getY());
	if (posicao == nullptr)
		return;

	if (p->verificaMovimentoSerXY(posicao->getX(), posicao->getY())) {
		s->setX(posicao->getX());
		s->setY(posicao->getY());
	}
}

Caracteristica * HeatSeeker::duplica() const{ return new HeatSeeker(*this); }


//BUILDSEEKER
BuildSeeker::BuildSeeker() : Caracteristica("BuildSeeker", 10, 1 ,1, false), velocidade(1) { }

int BuildSeeker::getSaudeMaxima() const { return 0; }

int BuildSeeker::getAtaque() { return 0; }

int BuildSeeker::getDefesa() const { return 0; }

int BuildSeeker::getVelocidade() const { return velocidade; }

void BuildSeeker::efeito(Ser * s, Colonia * c,  Planicie * p) {
	if (s == nullptr || p == nullptr)
		return;

	int x = s->getX();
	int y = s->getY();
	vector<Posicao> pos;
	vector<Edificio*> inimigos;

	p->getEdificiosInimigos(inimigos, c);

	if (inimigos.size() == 0) {
		Edificio *e = c->pesquisaEdificioPorTipo(ID_CASTELO);
		if (e == nullptr)
			return;
		Posicao *posicao = Posicao::getPosicaoMovimento(x, y, e->getX(), e->getY());
		if (posicao == nullptr)
			return;

		if (posicao->getX() == e->getX() && posicao->getY() == e->getY()) {
			s->setX(posicao->getX());
			s->setY(posicao->getY());
		}
		else if (p->verificaMovimentoSerXY(posicao->getX(), posicao->getY())) {
			s->setX(posicao->getX());
			s->setY(posicao->getY());
		}
		return;
	}

	Posicao::getPosicoesEdificios(inimigos, pos);
	Posicao *maisPro = Posicao::inimigoMaisProximo(pos, s->getX(), s->getY());
	if (maisPro == nullptr)
		return;

	Posicao *posicao = Posicao::getPosicaoMovimento(x, y, maisPro->getX(), maisPro->getY());
	if (posicao == nullptr)
		return;

	if (p->verificaMovimentoSerXY(posicao->getX(), posicao->getY())) {
		s->setX(posicao->getX());
		s->setY(posicao->getY());
	}
}

Caracteristica * BuildSeeker::duplica() const{ return new BuildSeeker(*this); }


//WALKER
Walker::Walker() : Caracteristica("Walker", 11, 1, 1, false), velocidade(1) { }

int Walker::getSaudeMaxima() const { return 0; }

int Walker::getAtaque() { return 0; }

int Walker::getDefesa() const { return 0; }

int Walker::getVelocidade() const { return velocidade; }

void Walker::efeito(Ser * s, Colonia * c,  Planicie * p) {
	if (s == nullptr || p == nullptr)
		return;

	int x = s->getX();
	int y = s->getY();
	
	vector<Posicao> pos;

	for (int i = y - velocidade; i <= y + velocidade; i++) { //Linhas
		for (int j = x - velocidade; j <= x + velocidade; j++) { //Colunas
			if (p->verificaLimitePlanicie(j, i)) {
				if (i == y && j == x)
					continue;
				else {
					p->getPosicoesAdjacentes(j, i, pos);
				}
			}
		}
	}

	if (pos.size() == 0) //Ñ tem posicoes livres, nao se move
		return;

	//Vai buscar a posicao random e mudas as coordenadas do ser para as coordenadas da posicao
	int randomPos = random(0, pos.size() - 1);
	s->setX(pos[randomPos].getX());
	s->setY(pos[randomPos].getY());
}

Caracteristica * Walker::duplica() const{ return new Walker(*this); }


//REMEDIO
Remedio::Remedio() : Caracteristica("Remedio", 12, 2, 1, false), saudeRecuperacao(2){ }

int Remedio::getSaudeMaxima() const { return 0; }

int Remedio::getAtaque() { return 0; }

int Remedio::getDefesa() const { return 0; }

int Remedio::getVelocidade() const { return 0; }

void Remedio::efeito(Ser * s, Colonia * c,  Planicie * p) { 

	if (s == nullptr)
		return;

	if (!jaUsou()) {
		if (s->getSaude() <= 3) {
			s->aumentaSaude(2);
			setUsou(true);
		}
	}

}

Caracteristica * Remedio::duplica() const { return new Remedio(*this); }


//SECONDCHANCE
SecondChance::SecondChance() : Caracteristica("SecondChance", 13, 3, 0, false), morreu(false) { }

int SecondChance::getSaudeMaxima() const { return 0; }

int SecondChance::getAtaque() { return 0; }

int SecondChance::getDefesa() const { return 0; }

int SecondChance::getVelocidade() const { return 0; }

void SecondChance::efeito(Ser * s, Colonia * c,  Planicie * p) {

	if (s == nullptr)
		return;

	if (!morreu) {
		if (s->getSaude() == 0) {
			if (c == nullptr)
				return;
			s->aumentaSaude(s->getSaudeMaxima());
			Edificio *e = c->pesquisaEdificioPorTipo(ID_CASTELO);
			if (e == nullptr)
				return;
			s->setX(e->getX());
			s->setY(e->getY());
			morreu = true;
		}
	}
}

Caracteristica * SecondChance::duplica() const { return new SecondChance(*this); }


//ALUNO
Aluno::Aluno() : Caracteristica("Aluno", 14, 10, 4, false), morreu(false), nMortes(0) { }

int Aluno::getSaudeMaxima() const { return 0; }

int Aluno::getAtaque() { return 0; }

int Aluno::getDefesa() const { return 0; }

int Aluno::getVelocidade() const { return 0; }

void Aluno::efeito(Ser * s, Colonia * c,  Planicie * p) {
	if (s == nullptr)
		return;

	if (!morreu) {
		if (s->getSaude() == 0) {
			if (c == nullptr)
				return;
			s->aumentaSaude(s->getSaudeMaxima());
			s->aumentaAtaque(5);
			s->aumentaDefesa(5);
			Edificio *e = c->pesquisaEdificioPorTipo(ID_CASTELO);
			if (e == nullptr)
				return;
			s->setX(e->getX());
			s->setY(e->getY());
			nMortes++;
			if(nMortes == 3)
				morreu = true;
		}
	}
}

Caracteristica * Aluno::duplica() const { return new Aluno(*this); }