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

//Caracteristica::Caracteristica(const Caracteristica & ob) { *this = ob; }
//
//Caracteristica & Caracteristica::operator=(const Caracteristica & ob){
//	if (this == &ob)
//		return *this;
//
//	nome = ob.nome;
//	id = ob.id;
//	custoMonetario = ob.custoMonetario;
//	custoForca = ob.custoForca;
//
//	return *this;
//}

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

bool Caracteristica::operator==(const Caracteristica * const c) const {
	if (id == c->getId())
		return true;
	return false;
}

void Bandeira::efeito(Ser * s, Colonia * c,  Planicie * p){
	
}

Caracteristica * Bandeira::duplica() const{ return new Bandeira(*this); }

//SUPERIOR
Superior::Superior() : Caracteristica("Superior", 2, 1, 1, false), saudeMax(1), 
incrementou(false) { }

int Superior::getSaudeMaxima() const { return saudeMax; }

int Superior::getAtaque() { return 0; }

int Superior::getDefesa() const { return 0; }

int Superior::getVelocidade() const { return 0; }

void Superior::efeito(Ser * s, Colonia * c,  Planicie * p){

	if (!incrementou) {
		s->aumentaSaudeMaxima(saudeMax);
		incrementou = true;
	}

}

Caracteristica * Superior::duplica() const{ return new Superior(*this); }


//PELEDURA
PeleDura::PeleDura() : Caracteristica("PeleDura", 3, 2, 2, false), defesa(1),
incrementou(false) { }

int PeleDura::getSaudeMaxima() const { return 0; }

int PeleDura::getAtaque() { return 0; }

int PeleDura::getDefesa() const { return defesa; }

int PeleDura::getVelocidade() const { return 0; }

void PeleDura::efeito(Ser * s, Colonia * c,  Planicie * p) {

	if (!incrementou) {
		s->setDefesa(s->getTotalDefesa() + 1);
		incrementou = true;
	}
}

Caracteristica * PeleDura::duplica() const{ return new PeleDura(*this); }


//ARMADURA
Armadura::Armadura() : Caracteristica("Armadura", 4, 2, 3, false), defesa(2),
incrementou(false) { }

int Armadura::getSaudeMaxima() const { return 0; }

int Armadura::getAtaque() { return 0; }

int Armadura::getDefesa() const { return defesa; }

int Armadura::getVelocidade() const { return 0; }

void Armadura::efeito(Ser * s, Colonia * c,  Planicie * p) {
	if (!incrementou) {
		s->setDefesa(s->getTotalDefesa() + 2);
		incrementou = true;
	}
}

Caracteristica * Armadura::duplica() const{ return new Armadura(*this); }


//FACA
Faca::Faca() : Caracteristica("Faca", 5, 1, 1, false), ataque(1),
incrementou(false) { }

int Faca::getSaudeMaxima() const { return 0; }

int Faca::getAtaque() { return ataque; }

int Faca::getDefesa() const { return 0; }

int Faca::getVelocidade() const { return 0; }

void Faca::efeito(Ser * s, Colonia * c,  Planicie * p) {
	if (!incrementou) {
		s->setAtaque(s->getTotalAtaque() + 1);
		incrementou = true;
	}
}

Caracteristica * Faca::duplica() const{ return new Faca(*this); }


//ESPADA
Espada::Espada() : Caracteristica("Espada",6, 2, 2, false), ataque(2),
ataqueIncremento(1), decrementou(false){ }

int Espada::getSaudeMaxima() const { return 0; }

int Espada::getAtaque() { return ataque; }

int Espada::getDefesa() const { return 0; }

int Espada::getVelocidade() const { return 0; }

void Espada::efeito(Ser * s, Colonia * c,  Planicie * p) {

	if (!jaUsou()) {
		if (s->getNumAtaques() == 1) {
			s->setAtaque(s->getTotalAtaque() + ataqueIncremento);
		}
		else if (s->getNumAtaques() == 2) {
			setUsou(true);
		}
	}
	else {
		if (!decrementou) {
			s->setAtaque(s->getTotalAtaque() - ataqueIncremento);
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

	for (int k = 0; k < p->getNumColonias(); k++) {
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
							int posP = col->pesquisaParia(j, i);
							if (posS != -1) {
								Ser *s = col->pesquisaSerPorIndice(posS);
								if (s == nullptr)
									return;
								s->recebeAtaque(s->getTotalAtaque());
								s->aumentaNumAtaques(1);
							}
							else if (posP != -1) {
								Ser *s = col->pesquisaPariaPorIndice(posP);
								if (s == nullptr)
									return;
								s->recebeAtaque(s->getTotalAtaque());
								s->aumentaNumAtaques(1);
							}
						}
					}
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

	for (int k = 0; k < p->getNumColonias(); k++) {
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
							int posE = col->pesquisaEdificio(j, i);
							if (posE != -1) {
								Edificio *e = col->pesquisaEdificioPorIndice(posE);
								if (e == nullptr)
									return;
								e->recebeAtaque(s->getTotalAtaque());
								s->aumentaNumAtaques(1);
							}
						}
					}
				}
			}
		}
	}
}

Caracteristica * Ecologico::duplica() const{ return new Ecologico(*this); }


//HEATSEEKER
HeatSeeker::HeatSeeker() : Caracteristica("HeatSeeker", 9, 1, 1, false), velocidade(1) { }

int HeatSeeker::getSaudeMaxima() const { return velocidade; }

int HeatSeeker::getAtaque() { return 0; }

int HeatSeeker::getDefesa() const { return 0; }

int HeatSeeker::getVelocidade() const { return 1; }

void HeatSeeker::efeito(Ser * s, Colonia * c,  Planicie * p) {
	if (s == nullptr || p == nullptr)
		return;

	int x = s->getX();
	int y = s->getY();
	vector<Posicao> pos;
	vector<Ser*> seres;

	for (int k = 0; k < p->getNumColonias(); k++) {
		Colonia *col = p->pesquisaColonia(k);
		if (col == nullptr)
			return;
		if (col != c) {
			col->getSeres(seres);
		}
	}

	for each (Ser *ser in seres) {
		if (ser == nullptr)
			return;
		Posicao p(ser->getX(), ser->getY());
		pos.push_back(p);
	}

	if (pos.size() == 0) {
		Edificio *e = c->pesquisaEdificioPorTipo(ID_CASTELO);
		if (e == nullptr)
			return;

		for (int k = 0; k < p->getNumColonias(); k++) {
			Colonia *col = p->pesquisaColonia(k);
			if (col == nullptr)
				return;
			if (e->getY() > y) {
				int posS = col->pesquisaSer(x, y + 1);
				int posE = col->pesquisaEdificio(x, y + 1);
				if (posS == -1 && posE == -1) {
					s->setY(s->getY() + 1);
				}
			}
			else if (e->getY() < y) {
				int posS = col->pesquisaSer(x, y - 1);
				int posE = col->pesquisaEdificio(x, y - 1);
				if (posS == -1 && posE == -1) {
					s->setY(s->getY() - 1);
				}
			}
			else if (e->getX() > x) {
				int posS = col->pesquisaSer(x + 1, y);
				int posE = col->pesquisaEdificio(x + 1, y);
				if (posS == -1 && posE == -1) {
					s->setX(s->getX() + 1);
				}
			}
			else if (e->getX() < x) {
				int posS = col->pesquisaSer(x - 1, y);
				int posE = col->pesquisaEdificio(x - 1, y);
				if (posS == -1 && posE == -1) {
					s->setX(s->getX() - 1);
				}
			}
		}
	}

	int indexMaisProxima;
	double aux = 2000;
	double maisProxima = 0;
	for (unsigned int z = 0; z < pos.size(); z++) {
		maisProxima = sqrt(pow(x - pos[z].getX(), 2) + pow(y - pos[z].getY(), 2));
		if (maisProxima < aux) {
			aux = maisProxima;
			indexMaisProxima = x;
		}
	}

	Posicao p1 = pos[indexMaisProxima];

	for (int k = 0; k < p->getNumColonias(); k++) {
		Colonia *col = p->pesquisaColonia(k);
		if (col == nullptr)
			return;

		if (p1.getY() > y) {
			int posS = col->pesquisaSer(x, y + 1);
			int posE = col->pesquisaEdificio(x, y + 1);
			if (posS == -1 && posE == -1) {
				s->setY(s->getY() + 1);
			}
		}
		else if (p1.getY() < y) {
			int posS = col->pesquisaSer(x, y - 1);
			int posE = col->pesquisaEdificio(x, y - 1);
			if (posS == -1 && posE == -1) {
				s->setY(s->getY() - 1);
			}
		}
		else if (p1.getX() > x) {
			int posS = col->pesquisaSer(x + 1, y);
			int posE = col->pesquisaEdificio(x + 1, y);
			if (posS == -1 && posE == -1) {
				s->setX(s->getX() + 1);
			}
		}
		else if (p1.getX() < x) {
			int posS = col->pesquisaSer(x - 1, y);
			int posE = col->pesquisaEdificio(x - 1, y);
			if (posS == -1 && posE == -1) {
				s->setX(s->getX() - 1);
			}
		}
	}
}

Caracteristica * HeatSeeker::duplica() const{ return new HeatSeeker(*this); }


//BUILDSEEKER
BuildSeeker::BuildSeeker() : Caracteristica("BuildSeeker", 10, 1 ,1, false), velocidade(1) { }

int BuildSeeker::getSaudeMaxima() const { return velocidade; }

int BuildSeeker::getAtaque() { return 0; }

int BuildSeeker::getDefesa() const { return 0; }

int BuildSeeker::getVelocidade() const { return 1; }

void BuildSeeker::efeito(Ser * s, Colonia * c,  Planicie * p) {
	if (s == nullptr || p == nullptr)
		return;

	int x = s->getX();
	int y = s->getY();
	vector<Posicao> pos;
	vector<Edificio*> edi;

	for (int k = 0; k < p->getNumColonias(); k++) {
		Colonia *col = p->pesquisaColonia(k);
		if (col == nullptr)
			return;
		if (col != c) {
			col->getEdificios(edi);
		}
	}

	for each (Edificio *e in edi) {
		if (e == nullptr)
			return;
		Posicao p(e->getX(), e->getY());
		pos.push_back(p);
	}

	if (pos.size() == 0) {
		Edificio *e = c->pesquisaEdificioPorTipo(ID_CASTELO);
		if (e == nullptr)
			return;

		for (int k = 0; k < p->getNumColonias(); k++) {
			Colonia *col = p->pesquisaColonia(k);
			if (col == nullptr)
				return;
			if (e->getY() > y) {
				int posS = col->pesquisaSer(x, y + 1);
				int posE = col->pesquisaEdificio(x, y + 1);
				if (posS == -1 && posE == -1) {
					s->setY(s->getY() + 1);
				}
			}
			else if (e->getY() < y) {
				int posS = col->pesquisaSer(x, y - 1);
				int posE = col->pesquisaEdificio(x, y - 1);
				if (posS == -1 && posE == -1) {
					s->setY(s->getY() - 1);
				}
			}
			else if (e->getX() > x) {
				int posS = col->pesquisaSer(x + 1, y);
				int posE = col->pesquisaEdificio(x + 1, y);
				if (posS == -1 && posE == -1) {
					s->setX(s->getX() + 1);
				}
			}
			else if (e->getX() < x) {
				int posS = col->pesquisaSer(x - 1, y);
				int posE = col->pesquisaEdificio(x - 1, y);
				if (posS == -1 && posE == -1) {
					s->setX(s->getX() - 1);
				}
			}
		}
	}

	int indexMaisProxima;
	double aux = 2000;
	double maisProxima;
	for (unsigned int z = 0; z < pos.size(); z++) {
		maisProxima = sqrt(pow(x - pos[z].getX(), 2) + pow(y - pos[z].getY(), 2));
		if (maisProxima < aux) {
			aux = maisProxima;
			indexMaisProxima = z;
		}
	}

	if (indexMaisProxima < 0)
		return;
	Posicao p1 = pos[indexMaisProxima];

	int posS;
	int posE;
	char destino;
	for (int k = 0; k < p->getNumColonias(); k++) {
		Colonia *col = p->pesquisaColonia(k);
		if (col == nullptr)
			return;

		if (p1.getY() > y) {
			posS = col->pesquisaSer(x, y + 1);
			posE = col->pesquisaEdificio(x, y + 1);
			if (posS == -1 && posE == -1) {
				destino = 'B';
			}
		}
		else if (p1.getY() < y) {
			posS = col->pesquisaSer(x, y - 1);
			posE = col->pesquisaEdificio(x, y - 1);
			if (posS == -1 && posE == -1) {
				destino = 'C';
			}
		}
		else if (p1.getX() > x) {
			posS = col->pesquisaSer(x + 1, y);
			posE = col->pesquisaEdificio(x + 1, y);
			if (posS == -1 && posE == -1) {
				destino = 'D';
			}
		}
		else if (p1.getX() < x) {
			posS = col->pesquisaSer(x - 1, y);
			posE = col->pesquisaEdificio(x - 1, y);
			if (posS == -1 && posE == -1) {
				destino = 'E';
			}
		}
	}
	s->setY(s->getY() + 1);
	s->setY(s->getY() - 1);
	s->setX(s->getX() + 1);
	s->setX(s->getX() - 1);
}

Caracteristica * BuildSeeker::duplica() const{ return new BuildSeeker(*this); }


//WALKER
Walker::Walker() : Caracteristica("Walker", 11, 1, 1, false), velocidade(1) { }

int Walker::getSaudeMaxima() const { return velocidade; }

int Walker::getAtaque() { return 0; }

int Walker::getDefesa() const { return 0; }

int Walker::getVelocidade() const { return 1; }

void Walker::efeito(Ser * s, Colonia * c,  Planicie * p) {
	if (s == nullptr || p == nullptr)
		return;

	int x = s->getX();
	int y = s->getY();
	bool livre = true;
	vector<Posicao> pos;

	for (int i = y - velocidade; i <= y + velocidade; i++) { //Linhas
		for (int j = x - velocidade; j <= x + velocidade; j++) { //Colunas
			if (p->verificaLimitePlanicie(j, i)) {
				if (i == y && j == x)
					continue;
				else {
					for (int k = 0; k < p->getNumColonias(); k++) {
						Colonia *col = p->pesquisaColonia(k);
						if (col == nullptr)
							return;
					
							int posS = col->pesquisaSer(j, i);
							int posE = col->pesquisaEdificio(j, i);
							if (posS != -1 || posE != -1) {
								livre = false;
							}
					}
					if (livre) {
						Posicao p(j, i);
						pos.push_back(p);
						livre = true;
					}
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
			s->setAtaque(s->getTotalAtaque() + 5);
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