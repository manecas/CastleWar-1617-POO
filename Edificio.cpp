#include "Edificio.h"
#include "Colonia.h"
#include "Perfil.h"
#include "Ser.h"
#include "Planicie.h"

#include "Constantes.h"
using namespace Constantes;

#include <sstream>
using std::ostringstream;

int Edificio::contador = 0;

//-----------------EDIFICIO---------------------------
Edificio::Edificio(string n, int c, int s, int d, int xx, int yy, int id):
	nome(n), custo(c), saude(s), defesa(d), x(xx), y(yy), eid(contador++), 
	id(id){ }

Edificio::Edificio(const Edificio & ob) { *this = ob; }

Edificio & Edificio::operator=(const Edificio & ob){
	if (this == &ob)
		return *this;

	contador = ob.contador;
	eid = ob.eid;
	nome = ob.nome;
	id = ob.id;
	custo = ob.custo;
	saude = ob.saude;
	defesa = ob.defesa;
	x = ob.x;
	y = ob.y;

	return *this;
}

string Edificio::getNome() const{ return nome; }

int Edificio::getId() const { return id; }

int Edificio::getCusto() const { return custo; }

int Edificio::getSaude() const { return saude; }

int Edificio::getDefesa() const { return defesa; }

void Edificio::setDefesa(int d) { defesa = d; }

string Edificio::toString() const {
	ostringstream out;

	out << id << " - " << nome << " saude: " << saude << " custo: " << custo
		<< " defesa: " << defesa << "localizacao: (" << x << "," << y << ")" << "\n";

	return out.str();
}

void Edificio::verificaDestruicao(Colonia * c){
	if (c == nullptr)
		return;

	if (saude == 0) {
		c->removeEdificios(x, y);
	}
}

int Edificio::getY() const { return y; }

int Edificio::getX() const { return x; }

int Edificio::getEid() const { return eid; }

void Edificio::setY(int yy) { y = yy; }

void Edificio::setX(int xx) { x = xx; }

//-----------------CASTELO---------------------------
Castelo::Castelo(int xx, int yy, int id) 
	: Edificio("Castelo", 0, 50, 10, xx, yy, id) { }

//Retorna um inteiro consoante o erro
int Castelo::fabricaSeres(Colonia * c, int num, Perfil * p){

	if (num <= 0 || p == nullptr)
		return 0;
	 
	//Se ele tem moedas para criar num seres
	if (c->getMoedas() < p->getTotalPreco() * num)
		return 2;

	//Verificar se existe ou nao castelo (pode estar destruido)
	const Edificio *temp = c->pesquisaEdificioPorTipo(ID_CASTELO);
	if (temp == nullptr)
		return 3;

	for (int i = 0; i < num; i++) {
		Ser * s = new Ser(*p);
		if (s == nullptr)
			return 5;
		s->setX(temp->getX());
		s->setY(temp->getY());
		c->addSer(s);
		c->setMoedas(c->getMoedas() - p->getTotalPreco());
	}

	return 4;
}

bool Castelo::upgrade(Colonia * c){ return true; }

void Castelo::efeito(Colonia * c, Planicie * p){ }

Edificio * Castelo::duplica() const { return new Castelo(*this); }

//------------------TORRE-----------------------------
Torre::Torre(int xx, int yy, int id)
	:Edificio("Torre", 30, 20, 10, xx, yy, id), ataque(3){ }

int Torre::getAtaque() const { return ataque; }

string Torre::toString() const{
	ostringstream out;

	out << Edificio::toString() << " ataque: " << ataque << "\n";

	return out.str();
}

bool Torre::upgrade(Colonia * c){
	if (c->getMoedas() - 10 >= 0) {
		c->setMoedas(c->getMoedas() - 10);
		setDefesa(getDefesa() + 2);
		ataque++;
		return true;
	}
	return false;
}

void Torre::efeito(Colonia * c, Planicie * p){
	if (c == nullptr)
		return;

	//Atacar

}

Edificio * Torre::duplica() const { return new Torre(*this); }

int Torre::fabricaSeres(Colonia * c, int num, Perfil * p){ return 0; }

//-------------------QUINTA-------------------------
Quinta::Quinta(int xx, int yy, int id)
:Edificio("Quinta", 20, 20, 10, xx ,yy, id), moedas(2){ }

int Quinta::getMoedas() const{ return moedas; }

string Quinta::toString() const{
	ostringstream out;

	out << Edificio::toString() << " moedas: " << moedas << "\n";

	return out.str();
}

bool Quinta::upgrade(Colonia * c){
	if (c->getMoedas() - 10 >= 0) {
		c->setMoedas(c->getMoedas() - 10);
		setDefesa(getDefesa() + 1);
		moedas++;
		return true;
	}
	return false;
}

void Quinta::efeito(Colonia * c, Planicie * p){
	if (c == nullptr)
		return;

	//Incrementar moedas

}

Edificio * Quinta::duplica() const { return new Quinta(*this); }

int Quinta::fabricaSeres(Colonia * c, int num, Perfil * p) { return 0; }

