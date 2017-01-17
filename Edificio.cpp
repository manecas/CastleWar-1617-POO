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

//Edificio::Edificio(const Edificio & ob) { *this = ob; }
//
//Edificio & Edificio::operator=(const Edificio & ob){
//	if (this == &ob)
//		return *this;
//
//	contador = ob.contador;
//	eid = ob.eid;
//	nome = ob.nome;
//	id = ob.id;
//	custo = ob.custo;
//	saude = ob.saude;
//	defesa = ob.defesa;
//	x = ob.x;
//	y = ob.y;
//
//	return *this;
//}

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
	: Edificio("Castelo", 0, 50, 10, xx, yy, id, 50, 0, 0) { }

//Retorna um inteiro consoante o erro
int Castelo::fabricaSeres(Colonia * c, int num, Perfil * p){

	if (p == nullptr)
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
			c->addParia(s);
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
	:Edificio("Torre", 30, 20, 10, xx, yy, id, 20, 10, 0), ataque(3), distAtaque(2){ }

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

	for (int k = 0; k < p->getNumColonias(); k++){
		Colonia *col = p->pesquisaColonia(k);
		if (col == nullptr)
			return;

		if (col != c) {
			for (int i = y - distAtaque; i <= y + distAtaque; i++) { //Linhas
				for (int j = x - distAtaque; j <= x + distAtaque; j++) { //Colunas
					if (i == y && j == x)
						continue;
					else {
						if (p->verificaLimitePlanicie(j, i)) {
							int posS = col->pesquisaSer(j, i);
							int posE = col->pesquisaEdificio(j, i);
							if (posS != -1) {
								Ser * s = col->pesquisaSerPorIndice(posS);
								if (s == nullptr)
									return;
								s->recebeAtaque(ataque);
							}
							else if (posE != -1) {
								Edificio *e = col->pesquisaEdificioPorIndice(posE);
								if (e == nullptr)
									return;
								e->recebeAtaque(ataque);
							}
						}
					}
				}
			}
		}
	}

}

Edificio * Torre::duplica() const { return new Torre(*this); }

int Torre::fabricaSeres(Colonia * c, int num, Perfil * p){ return 4; }

//-------------------QUINTA-------------------------
Quinta::Quinta(int xx, int yy, int id)
:Edificio("Quinta", 20, 20, 10, xx ,yy, id, 20, 10, 0), moedas(2){ }

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

int Quinta::fabricaSeres(Colonia * c, int num, Perfil * p) { return 4; }

int Quinta::getAtaque() const { return 0; }

