#include "Constantes.h"
using namespace Constantes;

#include "Caracteristica.h"
#include "Ser.h"
#include "Planicie.h"
#include "Edificio.h"
#include "Colonia.h"

#include <sstream>
using std::ostringstream;

Caracteristica::Caracteristica(const string & n, int iden, int custoM, int custoF):
	nome(n), id(iden), custoMonetario(custoM), custoForca(custoF) { }

Caracteristica::Caracteristica(const Caracteristica & ob) { *this = ob; }

Caracteristica & Caracteristica::operator=(const Caracteristica & ob){
	if (this == &ob)
		return *this;

	nome = ob.nome;
	id = ob.id;
	custoMonetario = ob.custoMonetario;
	custoForca = ob.custoForca;

	return *this;
}

string Caracteristica::getNome() const { return nome; }

int Caracteristica::getId() const { return id; }

int Caracteristica::getCustoMonetario() const { return custoMonetario; }

int Caracteristica::getCustoForca() const { return custoForca; }

string Caracteristica::toString() const{
	ostringstream out;
	out << id << " - " << nome << " custo monetario: " << custoMonetario
		<< " custo forca: " << custoForca << "\n";
	return out.str();
}

//BANDEIRA
Bandeira::Bandeira() : Caracteristica("Bandeira" , 1, 1, 0){ }

int Bandeira::getVelocidade() const{ return 0; }

int Bandeira::getAtaque() const{ return 0; }

int Bandeira::getDefesa() const { return 0; }

bool Caracteristica::operator==(const Caracteristica * const c) const {
	if (id == c->getId())
		return true;
	return false;
}

void Bandeira::efeito(Ser * s, Planicie * p){
	//Por fazer
}

Caracteristica * Bandeira::duplica() const{ return new Bandeira(*this); }

//SUPERIOR
Superior::Superior() : Caracteristica("Superior", 2, 1, 1), saudeMax(1) { }

int Superior::getVelocidade() const { return 0; }

int Superior::getAtaque() const { return 0; }

int Superior::getDefesa() const { return 0; }

void Superior::efeito(Ser * s, Planicie * p){

}

Caracteristica * Superior::duplica() const{ return new Superior(*this); }


//PELEDURA
PeleDura::PeleDura() : Caracteristica("PeleDura", 3, 2, 2), defesa(1) { }

int PeleDura::getVelocidade() const { return 0; }

int PeleDura::getAtaque() const { return 0; }

int PeleDura::getDefesa() const { return defesa; }

void PeleDura::efeito(Ser * s, Planicie * p) {

}

Caracteristica * PeleDura::duplica() const{ return new PeleDura(*this); }


//ARMADURA
Armadura::Armadura() : Caracteristica("Armadura", 4, 2, 3), defesa(2) { }

int Armadura::getVelocidade() const { return 0; }

int Armadura::getAtaque() const { return 0; }

int Armadura::getDefesa() const { return defesa; }

void Armadura::efeito(Ser * s, Planicie * p) {

}

Caracteristica * Armadura::duplica() const{ return new Armadura(*this); }


//FACA
Faca::Faca() : Caracteristica("Faca", 5, 1, 1), ataque(1) { }

int Faca::getVelocidade() const { return 0; }

int Faca::getAtaque() const { return ataque; }

int Faca::getDefesa() const { return 0; }

void Faca::efeito(Ser * s, Planicie * p) {

}

Caracteristica * Faca::duplica() const{ return new Faca(*this); }


//ESPADA
Espada::Espada() : Caracteristica("Espada",6, 2, 2), ataque(2), ataqueIncremento(1) { }

int Espada::getVelocidade() const { return 0; }

int Espada::getAtaque() const { 
	//Falta isto
	return 0;
}

int Espada::getDefesa() const { return 0; }

void Espada::efeito(Ser * s, Planicie * p) {

}

Caracteristica * Espada::duplica() const{ return new Espada(*this); }


//AGRESSAO
Agressao::Agressao() : Caracteristica("Agressao", 7, 1, 1) { }

int Agressao::getVelocidade() const { return 0; }

int Agressao::getAtaque() const { return 0; }

int Agressao::getDefesa() const { return 0; }

void Agressao::efeito(Ser * s, Planicie * p) {
	//Incrementa ataques
	/*
	vector<Ser*> seresA;
	vector<Edificio*> EdiA;
	p->pesquisaSeresAdjacentes(seresA, xSer, ySer);
	p->pesquisaEdificiosAdjacentes(EdiA, xSer, ySer);
	*/
}

Caracteristica * Agressao::duplica() const{ return new Agressao(*this); }


//ECOLOGICO
Ecologico::Ecologico() : Caracteristica("Ecologico", 8, 1, 1) { }

int Ecologico::getVelocidade() const { return 0; }

int Ecologico::getAtaque() const { return 0; }

int Ecologico::getDefesa() const { return 0; }

void Ecologico::efeito(Ser * s, Planicie * p) {
	//Incrementa ataques
}

Caracteristica * Ecologico::duplica() const{ return new Ecologico(*this); }


//HEATSEEKER
HeatSeeker::HeatSeeker() : Caracteristica("HeatSeeker", 9, 1, 1), velocidade(1) { }

int HeatSeeker::getVelocidade() const { return velocidade; }

int HeatSeeker::getAtaque() const { return 0; }

int HeatSeeker::getDefesa() const { return 0; }

void HeatSeeker::efeito(Ser * s, Planicie * p) {

}

Caracteristica * HeatSeeker::duplica() const{ return new HeatSeeker(*this); }


//BUILDSEEKER
BuildSeeker::BuildSeeker() : Caracteristica("BuildSeeker", 10, 1 ,1), velocidade(1) { }

int BuildSeeker::getVelocidade() const { return velocidade; }

int BuildSeeker::getAtaque() const { return 0; }

int BuildSeeker::getDefesa() const { return 0; }

void BuildSeeker::efeito(Ser * s, Planicie * p) {

}

Caracteristica * BuildSeeker::duplica() const{ return new BuildSeeker(*this); }


//WALKER
Walker::Walker() : Caracteristica("Walker", 11, 1, 1), velocidade(1) { }

int Walker::getVelocidade() const { return velocidade; }

int Walker::getAtaque() const { return 0; }

int Walker::getDefesa() const { return 0; }

void Walker::efeito(Ser * s, Planicie * p) {

	if (p == nullptr || s == nullptr)
		return;

	int xSer = s->getX();
	int ySer = s->getY();
	int x, y;
	y = random(ySer - 1, ySer + 1);
	x = random(xSer - 1, xSer + 1);
	s->setY(y);
	s->setX(x);

	////Erro aqui
	//for (int i = ySer -1; i <= ySer + 1; i++) { //Linhas
	//	for (int j = xSer - 1; j < xSer + 1; j++) { //Colunas
	//		if (i != ySer && j != xSer) {
	//			for (int k = 0; k > p->getNumColonias(); k++){
	//				Colonia *c = p->pesquisaColonia(k);
	//				if (c == nullptr)
	//					return;
	//				if (c->pesquisaEdificio(j, i) == -1 &&
	//					c->pesquisaSer(j, i) == -1 &&
	//					p->verificaLimitePlanicie(j, i)) {

	//					do {
	//						y = random(ySer - 1, ySer + 1);
	//						x = random(xSer - 1, xSer + 1);
	//					} while (y == ySer && x == xSer && 
	//						c->pesquisaEdificio(x, y) != -1 &&
	//						c->pesquisaSer(x, y) != -1 &&
	//						!p->verificaLimitePlanicie(x, y));
	//					s->setX(x);
	//					s->setY(y);
	//					return;
	//				}
	//			}
	//		}
	//	}
	//}
}

Caracteristica * Walker::duplica() const{ return new Walker(*this); }


//REMEDIO
Remedio::Remedio() : Caracteristica("Remedio", 12, 2, 1), saudeRecuperacao(2), usado(false) { }

int Remedio::getVelocidade() const { return 0; }

int Remedio::getAtaque() const { return 0; }

int Remedio::getDefesa() const { return 0; }

void Remedio::efeito(Ser * s, Planicie * p) { 

}

Caracteristica * Remedio::duplica() const { return new Remedio(*this); }


//SECONDCHANCE
SecondChance::SecondChance() : Caracteristica("SecondChance", 13, 3, 0), morreu(false) { }

int SecondChance::getVelocidade() const { return 0; }

int SecondChance::getAtaque() const { return 0; }

int SecondChance::getDefesa() const { return 0; }

void SecondChance::efeito(Ser * s, Planicie * p) {

}

Caracteristica * SecondChance::duplica() const { return new SecondChance(*this); }


//ALUNO
Aluno::Aluno() : Caracteristica("Aluno", 14, 4, 4) { }

int Aluno::getVelocidade() const { return 0; }

int Aluno::getAtaque() const { return 0; }

int Aluno::getDefesa() const { return 0; }

void Aluno::efeito(Ser * s, Planicie * p) {

}

Caracteristica * Aluno::duplica() const { return new Aluno(*this); }