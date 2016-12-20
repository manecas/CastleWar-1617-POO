#include "Planicie.h"
#include "Colonia.h"
#include "Perfil.h"
#include "Caracteristica.h"

#include "Constantes.h"
using namespace Constantes;

int Planicie::pesquisaPerfil(char letra) const{
	for (unsigned int i = 0; i < perfis.size(); i++) {
		if (perfis[i]->getLetra() == letra)
			return i;
	}
	return -1;
}

Planicie::Planicie(int lin, int col) : nLinhas(lin), nColunas(col), instante(0), vezJogada(0){
	Colonia *c = new Colonia(LETRAS[0], this);
	if (c == nullptr)
		return;
	colonias.push_back(c);
}

Planicie::Planicie(const Planicie & ob){ *this = ob; }

Planicie & Planicie::operator=(const Planicie & ob)
{
	if (this == &ob)
		return *this;

	//Destruir colonias
	for (unsigned i = 0; i < colonias.size(); i++) {
		delete colonias[i];
	}
	colonias.clear();

	for (unsigned i = 0; i < ob.colonias.size(); i++) {
		Colonia *c = ob.colonias[i];
		colonias.push_back(new Colonia(*c));
	}

	//Destruir perfis
	for (unsigned i = 0; i < perfis.size(); i++) {
		delete perfis[i];
	}
	perfis.clear();

	for (unsigned i = 0; i < ob.perfis.size(); i++) {
		Perfil *p = ob.perfis[i];
		perfis.push_back(new Perfil(*p));
	}

	nLinhas = ob.nLinhas;
	nColunas = ob.nColunas;

	return *this;
}

bool Planicie::addColonias(int num){
	if (num <= 0 || num >= 15)
		return false;

	for (int i = 0; i < num; i++){
		Colonia *c = new Colonia(LETRAS[i + 1], this);
		if (c == nullptr)
			return false;
		colonias.push_back(c);
	}
	return true;
}

Planicie::~Planicie(){
	for (unsigned int i = 0; i < colonias.size(); i++) {
		delete colonias[i];
	}
	colonias.clear();

	for (unsigned int i = 0; i < perfis.size(); i++) {
		delete perfis[i];
	}
	perfis.clear();
}

void Planicie::atua(){
	for (Colonia *c : colonias)
		c->atuaAtaqueEdificio(this);

	for (Colonia *c : colonias)
		c->atuaAtaqueSer(this);

	for (Colonia *c : colonias)
		c->elimina();

	//Verificar se uma colonia foi destruida
}

void Planicie::setNLinhas(int lin){ 
	if (lin > 0)
		nLinhas = lin;
}

void Planicie::setNColunas(int col){
	if (col > 0)
		nColunas = col;
}

void Planicie::incrementaVezJogada() { 
	if (vezJogada == colonias.size() - 1) {
		vezJogada = 0;
	}
	vezJogada++; 
}

int Planicie::getNLinhas() const { return nLinhas; }

int Planicie::getNColunas() const{ return nColunas; }

int Planicie::getNumColonias() const { return colonias.size(); }

int Planicie::getInstantes() const { return instante; }

void Planicie::aumentaInstantes(int num){
	if (num <= 0)
		return;

	instante += num;
}

Colonia * Planicie::pesquisaColonia(char letra)const{
	for (Colonia *c : colonias) {
		if (c->getLetra() == letra) {
			return c;
		}
	}
	return nullptr;
}

Colonia * Planicie::pesquisaColonia(int indice)const{
	int tam = colonias.size();
	if (indice >= 0 || indice <= tam)
		return colonias[indice];

	return nullptr;
}

bool Planicie::verificaLimitePlanicie(int xNovo, int yNovo) const{
	if (xNovo < X_MIN || yNovo < Y_MIN || xNovo > nColunas || yNovo > nLinhas)
		return false;

	return true;
}

void Planicie::getPerfis(vector<Perfil*>& perf){
	for (Perfil *p : perfis)
		perf.push_back(p);
}

bool Planicie::criaPerfil(char letra){
	if (perfis.size() >= MAX_PERFIS || pesquisaPerfil(letra) != -1)
		return false;

	perfis.push_back(new Perfil(letra));
	return true;
}

bool Planicie::removePerfil(char letra){
	int i = pesquisaPerfil(letra);
	if (i == -1)
		return false;

	delete perfis[i];
	perfis.erase(perfis.begin() + i);
	return true;
}

bool Planicie::addCaracteristica(int id, char letraPerfil){
	int i = pesquisaPerfil(letraPerfil);
	if (i == -1)
		return false;

	perfis[i]->addCaracteristica(id);
	return true;
}

bool Planicie::removeCaracteristica(int id, char letraPerfil){
	int i = pesquisaPerfil(letraPerfil);
	if (i == -1)
		return false;

	return perfis[i]->removeCaracteristica(id);
}

void Planicie::setMoedas(int moedas){
	for (Colonia *c : colonias)
		c->setMoedas(moedas);
}

int Planicie::fabricaSeres(int num, char letraPerfil){
	int i = pesquisaPerfil(letraPerfil);
	if (i == -1 || num <= 0)
		return -1;

	Perfil *p = perfis[i];
	Colonia *c = pesquisaColonia(LETRAS[vezJogada]);
	if (p == nullptr || c == nullptr)
		return -1;

	return c->fabricaSeres(num, p);
}

bool Planicie::mudaCastelo(char letra, int lin, int col){
	Colonia *c = pesquisaColonia(letra);
	if (c == nullptr)
		return false;

	return c->mudaCastelo(col, lin, this);
	
}
