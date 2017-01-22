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

Colonia::Colonia(char l, Planicie * p):letra(l), cor(incrementaCor++), modoAtaque(false), moedas(0){
	if (p == nullptr)
		return;

	int x = -1, y = -1;
	//Enquanto houver intersecção continua a gerar coordenadas

	y = random(0, p->getNLinhas());
	x = random(0, p->getNColunas());

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
	modoAtaque = ob.modoAtaque;

	return *this;
}

Colonia::~Colonia(){
	for (unsigned int i = 0; i < seres.size(); i++) {
		delete seres[i];
	}
	seres.clear();

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

bool Colonia::estaEmModoAtaque() const{ return modoAtaque; }

int Colonia::setModoRecolhe() { 
	if (modoAtaque) {
		modoAtaque = false;
		return 18;
	}
	return 19;
}

int Colonia::setModoAtaque() {
	if (!modoAtaque) {
		modoAtaque = true;
		return 20;
	}
	return 21;
}

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

bool Colonia::verificaMovimentoSerXY(int xDest, int yDest){

	if (pesquisaSer(xDest, yDest) != -1 || pesquisaEdificio(xDest, yDest) != -1) {
		return false;
	}

	return true;
}

bool Colonia::atacaSeresEdificiosAdjacentes(int x, int y, int forcaAta, Colonia * c){

	if (this != c) {
		int posS = pesquisaSer(x, y);
		int posE = pesquisaEdificio(x, y);
		if (posS != -1) {
			Ser * s = pesquisaSerPorIndice(posS);
			if (s == nullptr)
				return false;
			s->recebeAtaque(forcaAta);
			return true;   
		}
		else if (posE != -1) {
			Edificio *e = pesquisaEdificioPorIndice(posE);
			if (e == nullptr)
				return false;
			e->recebeAtaque(forcaAta);
			return true;
		}
	}
	return false;
}

bool Colonia::atacaSeresAdjacentes(int x, int y, int forcaAta, Colonia * c){
	if (this != c) {
		int posS = pesquisaSer(x, y);
		if (posS != -1) {
			Ser * s = pesquisaSerPorIndice(posS);
			if (s == nullptr)
				return false;
			s->recebeAtaque(forcaAta);
			return true;
		}
	}
	return false;
}

bool Colonia::atacaEdificiosAdjacentes(int x, int y, int forcaAta, Colonia * c){
	if (this != c) {
		int posE = pesquisaEdificio(x, y);
		if (posE != -1) {
			Edificio *e = pesquisaEdificioPorIndice(posE);
			if (e == nullptr)
				return false;
			e->recebeAtaque(forcaAta);
			return true;
		}
	}
	return false;
}

bool Colonia::getPosicoesAdjacentes(int x, int y, vector<Posicao> & pos){

	int posS = pesquisaSer(x, y);
	int posE = pesquisaEdificio(x, y);
	if (posS != -1 || posE != -1) {
		return false;
	}
	
	return true;
}

void Colonia::getSeresInimigos(vector<Ser*>& inimigos, Colonia * c){
	if (this != c) {
		for each(Ser *s in seres)
			inimigos.push_back(s);
	}
}

void Colonia::getEdificiosInimigos(vector<Edificio*>& inimigos, Colonia * c){
	if (this != c) {
		for each(Edificio *e in edificios)
			inimigos.push_back(e);
	}
}

void Colonia::getSeres(vector<Ser*> & ss){
	for each(Ser *s in seres)
		ss.push_back(s);
}

void Colonia::getEdificios(vector<Edificio*> & ee){
	for each(Edificio *e in edificios)
		ee.push_back(e);
}

int Colonia::fabricaSeres(int num, Perfil * p, Planicie * planicie){

	Edificio * e = pesquisaEdificioPorTipo(ID_CASTELO);

	if (e == nullptr)
		return 3;

	return e->fabricaSeres(this, num, p, planicie); 
}

int Colonia::constroiEdificio(int id, int lin, int col, Planicie * p, bool debug){

	if (p == nullptr)
		return -1;

	if (!p->verificaLimitePlanicie(col, lin))
		return 7;

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

int Colonia::mudaCastelo(int x, int y, Planicie * p){
	if (p == nullptr)
		return -1;

	if (!verificaLimitePlanicie(x, y, p))
		return 7;

	Edificio *e = pesquisaEdificioPorTipo(ID_CASTELO);
	if (e == nullptr) 
		return -1;

	e->setX(x);
	e->setY(y);
	return 26;
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

	if (estaEmModoAtaque()) {
		for (Ser *s : seres)
			s->atua(this, p);
	}
	else {
		Edificio *e = pesquisaEdificioPorTipo(ID_CASTELO);
		if (e == nullptr)
			return;
		for (Ser *s : seres) {
			Posicao *posicao = Posicao::getPosicaoMovimento(s->getX(), s->getY(), e->getX(), e->getY());
			if (posicao == nullptr)
				continue;

			if (posicao->getX() == e->getX() && posicao->getY() == e->getY()) {
				s->setX(posicao->getX());
				s->setY(posicao->getY());
				s->reiniciaCaracteristicas();
				s->aumentaSaude(1);
				if (!estaEmModoAtaque()) {
					if (s->getNumAtaques() == 1 || s->getNumAtaques() == 2) {
						s->diminuiAtaque(1);
						s->setNumAtaques(0);
					}
				}
			}
			else if (p->verificaMovimentoSerXY(posicao->getX(), posicao->getY())) {
				s->setX(posicao->getX());
				s->setY(posicao->getY());
			}
		}
	}
}

int Colonia::reparaEdificio(int eid){
	Edificio * e = pesquisaEdificioPorEid(eid);
	if (e == nullptr)
		return -1;;

	if (e->getSaude() == e->getSaudeMaxima())
		return 12;

	int saudePerc = (e->getSaude() * 100) / e->getSaudeMaxima();
	int custo = 0;

	if (e->getId() == ID_CASTELO) {
		custo = (40 * (100 - saudePerc)) / 100;
	}
	else {
		custo = (e->getCusto() * (100 - saudePerc)) / 100;
	}

	if (moedas - custo < 0)
		return 2;

	moedas -= custo;
	e->aumentaSaude(e->getSaudeMaxima());
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
		return 37;

	moedas += (e->getCusto() * e->getNumUpgrades()) / 2;
	removeEdificios(e->getX(), e->getY());
	return 13;
}

void Colonia::elimina(){
	vector<Ser*> copiaS = seres;
	for (Ser *s : copiaS)
		s->verificaSaude(this, nullptr);

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
