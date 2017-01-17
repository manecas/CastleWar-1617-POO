#include "Colonia.h"
#include "Edificio.h"
#include "Ser.h"
#include "Planicie.h"
#include "Perfil.h"
#include "FabricaEdificios.h"

#include <sstream>
#include "Constantes.h"

using namespace Constantes;
using std::ostringstream;


int Colonia::incrementaCor = 1;

Colonia::Colonia(char l, Planicie * p):letra(l), cor(incrementaCor++){
	if (p == nullptr)
		return;

	int x = -1, y = -1;
	//Enquanto houver intersecção continua a gerar coordenadas

	do {
		y = random(0, p->getNLinhas());
		x = random(0, p->getNColunas());
	} while (!verificaInterseccaoCastelo(x, y, p));

		Edificio *c = new Castelo(x, y, ID_CASTELO);
	if (c != nullptr)
		edificios.push_back(c);
}

Colonia::Colonia(const Colonia & ob) { *this = ob; }

Colonia & Colonia::operator=(const Colonia & ob){
	if (this == &ob)
		return *this;

	//Destruir seres
	for (unsigned i = 0; i < seres.size(); i++) {
		delete seres[i];
	}
	seres.clear();

	for (unsigned i = 0; i < ob.seres.size(); i++) {
		Ser *s = ob.seres[i]->duplica();
		seres.push_back(s);
	}

	//Destruir parias
	for (unsigned i = 0; i < parias.size(); i++) {
		delete parias[i];
	}
	parias.clear();

	for (unsigned i = 0; i < ob.parias.size(); i++) {
		Ser *s = ob.parias[i]->duplica();
		parias.push_back(s);
	}

	//Destruir edificios
	for (unsigned i = 0; i < edificios.size(); i++) {
		delete edificios[i];
	}
	edificios.clear();

	for (unsigned i = 0; i < ob.edificios.size(); i++) {
		Edificio *e = ob.edificios[i]->duplica();
		edificios.push_back(e);
	}

	moedas = ob.moedas;
	letra = ob.letra;
	cor = ob.cor;

	return *this;
}

Colonia::~Colonia(){
	for (unsigned int i = 0; i < seres.size(); i++) {
		delete seres[i];
	}
	seres.clear();

	for (unsigned int i = 0; i < parias.size(); i++) {
		delete parias[i];
	}
	parias.clear();

	for (unsigned int i = 0; i < edificios.size(); i++) {
		delete edificios[i];
	}
	edificios.clear();
}

bool Colonia::addSer(Ser * s){
	if (s == nullptr)
		return false;

	seres.push_back(s);
	return true;
}

bool Colonia::addParia(Ser * s){
	if (s == nullptr)
		return false;

	parias.push_back(s);
	return true;
}

void Colonia::removeParias(int x, int y){

	int i = pesquisaParia(x, y);
	if (i == -1)
		return;

	delete parias[i];
	parias.erase(parias.begin() + i);

}

bool Colonia::verificaInterseccaoCastelo(int xNovo, int yNovo, Planicie * p) const{

	if (p == nullptr || xNovo == -1 || yNovo == -1)
		return false;

	int x1N = xNovo + LIMITE_CASTELO;
	int x2N = xNovo - LIMITE_CASTELO;
	int y1N = yNovo + LIMITE_CASTELO;
	int y2N = yNovo - LIMITE_CASTELO;

	if (p->getNumColonias() == 0)
		return true;

	int conta = 0;

	for (int i = 0; i < p->getNumColonias(); i++) {
		//Buscar os outros castelos das outras colonias
		const Colonia *c = p->pesquisaColonia(i);
		if (c == nullptr) //1 - AZUL
			return false;

		/*if (c->getCor() == 1)
			return true;*/

		Edificio *e = c->pesquisaEdificioPorTipo(ID_CASTELO);
		if (e == nullptr)
			return false;

		int x1 = e->getX() + LIMITE_CASTELO;
		int x2 = e->getX() - LIMITE_CASTELO;
		int y1 = e->getY() + LIMITE_CASTELO;
		int y2 = e->getY() - LIMITE_CASTELO;

		//Comparar se dois retangulos se intersetam
		if ( !(x1N < x2 || x2N > x1 || y1N < y2 || y2N > y1) )
			conta++; //intersecta
	}
	
	if (conta > 0)
		return false;

	return true;
}

//Planicie
bool Colonia::verificaLimitePlanicie(int xNovo, int yNovo, Planicie * p) const{
	if (p->verificaLimitePlanicie(xNovo, yNovo))
		return true;

	return false;
}

bool Colonia::verificaLimiteColonia(int xNovo, int yNovo, Planicie * p) const{
	const Edificio *e = pesquisaEdificioPorTipo(ID_CASTELO);
	if (e == nullptr)
		return false;

	int x1 = e->getX() + LIMITE_CASTELO;
	int x2 = e->getX() - LIMITE_CASTELO;
	int y1 = e->getY() + LIMITE_CASTELO;
	int y2 = e->getY() - LIMITE_CASTELO;

	if (xNovo <= x1 && xNovo >= x2 && yNovo >= y2 && yNovo <= y1)
		return true;

	return false;
}

int Colonia::pesquisaSer(int x, int y) const{
	for (unsigned int i = 0; i < seres.size(); i++){
		if (seres[i]->getX() == x && seres[i]->getY() == y)
			return i;
	}
	return -1;
}

int Colonia::pesquisaParia(int x, int y) const{
	for (unsigned int i = 0; i < parias.size(); i++) {
		if (parias[i]->getX() == x && parias[i]->getY() == y)
			return i;
	}
	return -1;
}

void Colonia::removeSeres(int x, int y){
	int i = pesquisaSer(x, y);
	if (i == -1)
		return;

	delete seres[i];
	seres.erase(seres.begin() + i);
}

bool Colonia::addEdificio(Edificio * e){
	if (e == nullptr)
		return false;

	edificios.push_back(e);
	return true;
}

bool Colonia::mandouRecolher() const{ return recolheu; }

void Colonia::setMandouRecolher(bool mandouR) { recolheu = mandouR; }

int Colonia::pesquisaEdificio(int x, int y) const{
	for (unsigned int i = 0; i < edificios.size(); i++) {
		if (edificios[i]->getX() == x && edificios[i]->getY() == y)
			return i;
	}
	return -1;
}

Edificio * Colonia::pesquisaEdificioPorEid(int eid) const{
	for (Edificio *e : edificios) {
		if (e->getEid() == eid)
			return e;
	}
	return nullptr;
}

Edificio * Colonia::pesquisaEdificioPorTipo(int id) const{
	for (Edificio *e : edificios) {
		if (e->getId() == id)
			return e;
	}
	return nullptr;
}

Ser * Colonia::pesquisaSerPorIndice(int indice) const{ 
	if (indice < 0)
		return nullptr;

	return seres[indice]; 
}

Ser * Colonia::pesquisaPariaPorIndice(int indice) const{
	if (indice < 0)
		return nullptr;

	return parias[indice];
}

Edificio * Colonia::pesquisaEdificioPorIndice(int indice) const { 
	if (indice < 0) 
		return nullptr;

	return edificios[indice]; 
}

void Colonia::reiniciaCor() { incrementaCor = 1; }

void Colonia::removeEdificios(int x, int y){
	int i = pesquisaEdificio(x, y);
	if (i == -1)
		return;

	delete edificios[i];
	edificios.erase(edificios.begin() + i);
}

int Colonia::getMoedas() const{ return moedas; }

void Colonia::setMoedas(int m) { 
	if (m < 0)
		moedas = 0;

	moedas = m; 
}

char Colonia::getLetra() const{ return letra; }

int Colonia::getCor() const{ return cor; }

void Colonia::getPosicoesAdjacentes(vector<Posicao> & pos, int x, int y, Planicie * p){

	if (p == nullptr)
		return;

	
}

void Colonia::getSeres(vector<Ser*> & ss){
	for each(Ser *s in seres)
		ss.push_back(s);
}

void Colonia::getEdificios(vector<Edificio*> & ee){
	for each(Edificio *e in edificios)
		ee.push_back(e);
}

int Colonia::fabricaSeres(int num, Perfil * p){

	Edificio * e = pesquisaEdificioPorTipo(ID_CASTELO);

	if (e == nullptr)
		return 3;

	return e->fabricaSeres(this, num, p); 
}

int Colonia::constroiEdificio(int id, int lin, int col, Planicie * p, bool debug){

	if (p == nullptr)
		return -1;

	if (!p->verificaLimitePlanicie(col, lin))
		return -1;

	Edificio *e = FabricaEdificios::cria(id, col, lin);

	if (e == nullptr)
		return -1;

	for (int i = 0; i < p->getNumColonias(); i++){
		Colonia * c = p->pesquisaColonia(i);
		if (c == nullptr)
			return -1;

		if (c->pesquisaEdificio(col, lin) != -1 || c->pesquisaSer(col, lin) != -1)
			return 10;
	}

	if (!verificaLimiteColonia(col, lin, p))
		return 11;

	if (!debug) { //Build
		if (moedas - e->getCusto() < 0)
			return 2;
		else 
			moedas -= e->getCusto();
	}

	addEdificio(e);
	return 9;
}

bool Colonia::mudaCastelo(int x, int y, Planicie * p){
	if (p == nullptr)
		return false;

	if (/*!verificaInterseccaoCastelo(x, y, p) || */!verificaLimitePlanicie(x, y, p))
		return false;

	Edificio *e = pesquisaEdificioPorTipo(ID_CASTELO);
	if (e == nullptr) 
		return false;

	e->setX(x);
	e->setY(y);

	return true;
}

void Colonia::atuaAtaqueEdificio(Planicie * p){
	if (p == nullptr)
		return;

	for (Edificio *e : edificios)
		e->efeito(this, p);
}

void Colonia::atuaAtaqueSer(Planicie * p){
	if (p == nullptr)
		return;

	if (!mandouRecolher()) {
		for (Ser *s : seres)
			s->atua(this, p);
	}
	else {
		for (Ser *s : seres)
			s->mandarRecolher(this);
	}
}

int Colonia::reparaEdificio(int eid){
	Edificio * e = pesquisaEdificioPorEid(eid);
	if (e == nullptr)
		return -1;;

	if (e->getSaude() == e->getSaudeMaxima())
		return 12;

	int custo = (e->getCusto() * (e->getSaude() * 100) / e->getSaudeMaxima()) / 100;

	if (moedas - custo < 0)
		return 2;

	return 6;
}

int Colonia::updgradeEdificio(int eid){
	Edificio * e = pesquisaEdificioPorEid(eid);
	if (e == nullptr)
		return -1;;

	return e->upgrade(this);
}

int Colonia::venderEdificio(int eid) {
	Edificio * e = pesquisaEdificioPorEid(eid);
	if (e == nullptr)
		return -1;;

	if (e->getId() == ID_CASTELO)
		return 12;

	moedas += (e->getCusto() * e->getNumUpgrades()) / 2;
	removeEdificios(e->getX(), e->getY());
	return 13;
}

void Colonia::elimina(){
	vector<Ser*> copiaS = seres;
	for (Ser *s : copiaS)
		s->verificaSaude(this);
	
	vector<Ser*> copiaP = parias;
	for (Ser *s : copiaP)
		s->verificaSaude(this);

	vector<Edificio*> copiaE = edificios;
	for (Edificio *e : copiaE)
		e->verificaDestruicao(this);
}

string Colonia::toString() const {
	ostringstream out;

	out << "Colonia: " << letra << "\nCor: " << cor << "\n";

	for (Edificio *e : edificios)
		out << e->toString();
	out << "\n";
	for (Ser *s : seres)
		out << s->toString();
	out << "\n";

	return out.str();
}
