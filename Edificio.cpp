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
Edificio::Edificio(string n, int c, int s, int d, int xx, int yy, int id, int saudeM, 
	int custoUpgrade, int numUpgrades):
	nome(n), custo(c), saude(s), defesa(d), x(xx), y(yy), eid(contador++), 
	id(id), saudeMaxima(saudeM), custoUpgrade(custoUpgrade), numUpgrades(numUpgrades){ }

string Edificio::getNome() const{ return nome; }

int Edificio::getId() const { return id; }

int Edificio::getCusto() const { return custo; }

int Edificio::getSaude() const { return saude; }

int Edificio::getDefesa() const { return defesa; }

int Edificio::getCustoUpgrade() const { return custoUpgrade; }

int Edificio::getNumUpgrades() const { return numUpgrades; }

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

void Edificio::diminuiSaude(int s) {
	if (saude - s < 0) {
		saude = 0;
		return;
	}

	saude -= s;
}

void Edificio::recebeAtaque(int forcaAtaque) {

	if (forcaAtaque > defesa)
		diminuiSaude(forcaAtaque - defesa);
	else
		diminuiSaude(1);

}

int Edificio::getY() const { return y; }

int Edificio::getX() const { return x; }

int Edificio::getEid() const { return eid; }

int Edificio::getSaudeMaxima() const { return saudeMaxima; }

void Edificio::aumentaSaude(int s) {
	if (saude + s >= saudeMaxima) {
		saude = saudeMaxima;
		return;
	}
	saude += s;
}

void Edificio::aumentaSaudeMaxima(int saudeMax) { saudeMaxima += saudeMax; }

void Edificio::aumentaUpgrades(int num) { numUpgrades += num; }

void Edificio::reiniciaContador(){ contador = 0; }

void Edificio::setY(int yy) { y = yy; }

void Edificio::setX(int xx) { x = xx; }

//-----------------CASTELO---------------------------
Castelo::Castelo(int xx, int yy, int id) 
	: Edificio("Castelo", 0, 50, 10, xx, yy, id, 50, 0, 1) { }

//Retorna um inteiro consoante o erro
int Castelo::fabricaSeres(Colonia * c, int num, Perfil * p, Planicie * planicie){

	if (p == nullptr || planicie == nullptr)
		return -1;

	if (num <= 0)
		return 0;
	 
	//Se ele tem moedas para criar num seres
	if (c->getMoedas() - (p->getTotalPreco() * num) < 0)
		return 2;

	//Verificar se existe ou nao castelo (pode estar destruido)
	Edificio *temp = c->pesquisaEdificioPorTipo(ID_CASTELO);
	if (temp == nullptr)
		return 3;

	for (int i = 0; i < num; i++) {
		Ser * s = new Ser(*p);
		if (s == nullptr)
			return -1;
		s->setX(temp->getX());
		s->setY(temp->getY());
		if (p->bandeiraExiste())
			c->addSer(s);
		else
			planicie->addParia(s);
	}

	c->setMoedas(c->getMoedas() - (p->getTotalPreco() * num));
	return 4;
}

int Castelo::getAtaque() const { return 0; }

int Castelo::upgrade(Colonia * c){ return 8; }

void Castelo::efeito(Colonia * c, Planicie * p){ }

Edificio * Castelo::duplica() const { return new Castelo(*this); }

//------------------TORRE-----------------------------
Torre::Torre(int xx, int yy, int id)
	:Edificio("Torre", 30, 20, 10, xx, yy, id, 20, 10, 1), ataque(3), distAtaque(2){ }

int Torre::getAtaque() const { return ataque; }

string Torre::toString() const{
	ostringstream out;

	out << Edificio::toString() << " ataque: " << ataque << "\n";

	return out.str();
}

int Torre::upgrade(Colonia * c){
	if (c == nullptr)
		return -1;

	if (c->getMoedas() - getCustoUpgrade() >= 0) {
		c->setMoedas(c->getMoedas() - getCustoUpgrade());
		setDefesa(getDefesa() + 2);
		ataque++;
		aumentaUpgrades(1);
		return 9;
	}
	return 2;
}

void Torre::efeito(Colonia * c, Planicie * p){
	if (c == nullptr || p == nullptr)
		return;

	int x = getX();
	int y = getY();

	for (int i = y - distAtaque; i <= y + distAtaque; i++) { //Linhas
		for (int j = x - distAtaque; j <= x + distAtaque; j++) { //Colunas
			if (i == y && j == x)
				continue;
			else {
				if (p->atacaSeresEdificiosAdjacentes(j, i, ataque, c))
					return;
			}
		}
	}

}

Edificio * Torre::duplica() const { return new Torre(*this); }

int Torre::fabricaSeres(Colonia * c, int num, Perfil * p, Planicie * planicie){ return 4; }

//-------------------QUINTA-------------------------
Quinta::Quinta(int xx, int yy, int id)
:Edificio("Quinta", 20, 20, 10, xx ,yy, id, 20, 10, 1), moedas(2){ }

int Quinta::getMoedas() const{ return moedas; }

string Quinta::toString() const{
	ostringstream out;

	out << Edificio::toString() << " moedas: " << moedas << "\n";

	return out.str();
}

int Quinta::upgrade(Colonia * c){
	if (c == nullptr)
		return -1;

	if (c->getMoedas() - getCustoUpgrade() >= 0) {
		c->setMoedas(c->getMoedas() - getCustoUpgrade());
		setDefesa(getDefesa() + 1);
		moedas++;
		aumentaUpgrades(1);
		return 9;
	}
	return 2;
}

void Quinta::efeito(Colonia * c, Planicie * p){
	if (c == nullptr)
		return;

	c->setMoedas(c->getMoedas() + moedas);
}

Edificio * Quinta::duplica() const { return new Quinta(*this); }

int Quinta::fabricaSeres(Colonia * c, int num, Perfil * p, Planicie * planicie) { return 4; }

int Quinta::getAtaque() const { return 0; }

