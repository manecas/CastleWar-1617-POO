#include "Perfil.h"
#include "Caracteristica.h"
#include "FabricaCaracteristicas.h"

#include <sstream>

using std::ostringstream;

//--------------------------------PERFIL--------------------------------
Perfil::Perfil(char l) :letra(l), preco(0), forca(10) { }

//VER ISTO CÓPIA CAMPO A CAMPO
Perfil::Perfil(const Perfil & ob){ *this = ob; }

Perfil & Perfil::operator=(const Perfil & ob){
	if (this == &ob)
		return *this;

	for (unsigned i = 0; i < caracteristicas.size(); i++){
		delete caracteristicas[i];
	}

	caracteristicas.clear();

	for (unsigned i = 0; i < ob.caracteristicas.size(); i++) {
		Caracteristica *c = ob.caracteristicas[i]->duplica();
		caracteristicas.push_back(c);
	}

	preco = ob.preco;
	forca = ob.forca;
	letra = ob.letra;

	return *this;
}

Perfil::~Perfil() {
	for (unsigned int i = 0; i < caracteristicas.size(); i++) {
		delete caracteristicas[i];
	}
	caracteristicas.clear();
}

int Perfil::getForca() const { return forca; }

int Perfil::getTotalPreco() const { return preco; }

int Perfil::getTotalAtaque() const{
	int totalAtaque = 0;
	for (Caracteristica *c : caracteristicas)
		totalAtaque += c->getAtaque();

	return totalAtaque;
}

int Perfil::getTotalDefesa() const{
	int totalDefesa = 0;
	for (Caracteristica *c : caracteristicas)
		totalDefesa += c->getDefesa();

	return totalDefesa;
}

int Perfil::getTotalVelocidade() const{
	int totalVelocidade = 0;
	for (Caracteristica *c : caracteristicas)
		totalVelocidade += c->getVelocidade();

	return totalVelocidade;
}

void Perfil::getCaracteristicas(vector<Caracteristica*> & carac){
	for (Caracteristica *c : caracteristicas)
		carac.push_back(c);
}

char Perfil::getLetra() const { return letra; }

int Perfil::pesquisaCaracteristica(int id){

	for (unsigned int i = 0; i < caracteristicas.size(); i++) {
		if (caracteristicas[i]->getId() == id)
			return i;
	}
	return -1;
}

bool Perfil::addCaracteristica(int id) {
	Caracteristica *c = FabricaCaracteristicas::cria(id);

	if (forca - c->getCustoForca() >= 0 && c != nullptr) {
		forca -= c->getCustoForca();
		preco += c->getCustoMonetario();
		caracteristicas.push_back(c);
		return true;
	}

	return false;
}

bool Perfil::removeCaracteristica(int id){
	int i = pesquisaCaracteristica(id);
	if (i == -1)
		return false;

	delete caracteristicas[i];
	caracteristicas.erase(caracteristicas.begin() + i);
	return true;

}

void Perfil::atua(Ser * s, Planicie * p) {
	if (s == nullptr)
		return;

	for each (Caracteristica *c in caracteristicas) {
		c->efeito(s, p);
	}
}

string Perfil::toString() const{
	ostringstream out;
	out << "Letra: " << letra << " forca: " << forca << " preco: " << preco << "\n";

	for (Caracteristica *c : caracteristicas)
		out << c->toString();

	return out.str();
}
