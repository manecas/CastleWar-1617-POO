#include "Planicie.h"
#include "Colonia.h"
#include "Perfil.h"
#include "Caracteristica.h"
#include "Ser.h"
#include "FabricaCaracteristicas.h"
#include "FabricaEdificios.h"
#include "Edificio.h"

int Planicie::pesquisaPerfil(char letra) const{
	for (unsigned int i = 0; i < perfis.size(); i++) {
		if (perfis[i]->getLetra() == letra)
			return i;
	}
	return -1;
}

Perfil * Planicie::pesquisaPerfilPorLetra(char letra) const{
	
	for each (Perfil *p in perfis){
		if (p->getLetra() == letra)
			return p;
	}

	return nullptr;
}

void Planicie::getSeres(vector<Ser*> & ss) {
	for each (Colonia *c in colonias){
		c->getSeres(ss);
	}
}

void Planicie::getSeresInimigos(vector<Ser*>& inimigos, Colonia * c){
	for each (Colonia *col in colonias) {
		col->getSeresInimigos(inimigos, c);
	}

	for each (Ser *s in parias) {
		inimigos.push_back(s);
	}
}

void Planicie::getEdificiosInimigos(vector<Edificio*>& inimigos, Colonia * c){
	for each (Colonia *col in colonias) {
		col->getEdificiosInimigos(inimigos, c);
	}
}

void Planicie::getParias(vector<Ser*>& pp){
	for each (Ser *s in parias) {
		pp.push_back(s);
	}
}

void Planicie::getEdificios(vector<Edificio*> & ee) {
	for each (Colonia *c in colonias) {
		c->getEdificios(ee);
	}
}

bool Planicie::verificaMovimentoSerXY(int xDest, int yDest){
	for each (Colonia *c in colonias) {
		if (!c->verificaMovimentoSerXY(xDest, yDest))
			return false;
	}

	if (pesquisaParia(xDest, yDest) != -1) {
		return false;
	}

	return true;
}

bool Planicie::atacaSeresEdificiosAdjacentes(int x, int y, int forcaAta, Colonia * c){
	if (x < 0 || y < 0 || forcaAta < 0 || c == nullptr)
		return false;

	if (verificaLimitePlanicie(x, y)) {
		for each (Colonia *col in colonias){
			if (col->atacaSeresEdificiosAdjacentes(x, y, forcaAta, c))
				return true;
		}

		int posP = pesquisaParia(x, y);
		if (posP != -1) {
			Ser * s = pesquisaPariaPorIndice(posP);
			if (s == nullptr)
				return false;
			s->recebeAtaque(forcaAta);
			return true;
		}

	}
	return false;
}

bool Planicie::atacaSeresAdjacentes(int x, int y, int forcaAta, Colonia * c){
	if (x < 0 || y < 0 || forcaAta < 0 || c == nullptr)
		return false;

	if (verificaLimitePlanicie(x, y)) {
		for each (Colonia *col in colonias) {
			if (col->atacaSeresAdjacentes(x, y, forcaAta, c))
				return true;
		}

		int posP = pesquisaParia(x, y);
		if (posP != -1) {
			Ser * s = pesquisaPariaPorIndice(posP);
			if (s == nullptr)
				return false;
			s->recebeAtaque(forcaAta);
			return true;
		}
	}
	return false;

}

bool Planicie::atacaEdificiosAdjacentes(int x, int y, int forcaAta, Colonia * c){
	if (x < 0 || y < 0 || forcaAta < 0 || c == nullptr)
		return false;

	if (verificaLimitePlanicie(x, y)) {
		for each (Colonia *col in colonias) {
			if (col->atacaEdificiosAdjacentes(x, y, forcaAta, c))
				return true;
		}
	}
	return false;

}

void Planicie::getPosicoesAdjacentes(int x, int y, vector<Posicao>& pos){
	if (x < 0 || y < 0)
		return;

	if (verificaLimitePlanicie(x, y)) {
		for each (Colonia *c in colonias){
			if (!c->getPosicoesAdjacentes(x, y, pos))
				return;
		}

		int posP = pesquisaParia(x, y);
		if (posP != -1) {
			return;
		}
	}
	Posicao p(x, y);
	pos.push_back(p);
}

Planicie::Planicie(int lin, int col) : nLinhas(lin), nColunas(col), nomeJogo(""){
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

	//Destruir parias
	for (unsigned i = 0; i < parias.size(); i++) {
		delete parias[i];
	}
	parias.clear();

	for (unsigned i = 0; i < ob.parias.size(); i++) {
		Ser *s = ob.parias[i]->duplica();
		parias.push_back(s);
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

	//Destruir perfis COMPUTADOR
	for (unsigned i = 0; i < perfisComputador.size(); i++) {
		delete perfisComputador[i];
	}
	perfisComputador.clear();

	for (unsigned i = 0; i < ob.perfisComputador.size(); i++) {
		Perfil *p = ob.perfisComputador[i];
		perfisComputador.push_back(new Perfil(*p));
	}

	nomeJogo = ob.nomeJogo;
	nLinhas = ob.nLinhas;
	nColunas = ob.nColunas;

	return *this;
}

int Planicie::addColonias(int num){
	if (num <= 0 || num >= 15)
		return 24;

	if (colonias.size() == 0)
		return -1;

	Colonia *col = pesquisaColonia(LETRAS[0]);
	if (col == nullptr)
		return -1;

	if (colonias.size() == 1) {
		for (int i = 0; i < num; i++) {
			Colonia *c = new Colonia(LETRAS[i + 1], this);
			if (c == nullptr)
				return -1;
			c->setMoedas(col->getMoedas());
			colonias.push_back(c);
		}
	}
	else {
		Colonia *c = pesquisaColonia(LETRAS[0]);
		if (c == nullptr)
			return -1;
		colonias.clear();
		colonias.push_back(c);
		for (int i = 0; i < num; i++) {
			Colonia *c = new Colonia(LETRAS[i + 1], this);
			if (c == nullptr)
				return -1;
			colonias.push_back(c);
		}
	}

	return 25;
}

Planicie::~Planicie(){
	for (unsigned int i = 0; i < colonias.size(); i++) {
		delete colonias[i];
	}
	colonias.clear();

	for (unsigned int i = 0; i < parias.size(); i++) {
		delete parias[i];
	}
	parias.clear();

	for (unsigned int i = 0; i < perfis.size(); i++) {
		delete perfis[i];
	}
	perfis.clear();
}

int Planicie::atua(){
	for (Colonia *c : colonias)
		c->atuaAtaqueEdificio(this);

	for (Colonia *c : colonias)
		c->atuaAtaqueSer(this);

	for (Ser *p : parias){
		int x = p->getX();
		int y = p->getY();

		vector<Posicao> pos;

		for (int i = y - 1; i <= y + 1; i++) { //Linhas
			for (int j = x - 1; j <= x + 1; j++) { //Colunas
				if (verificaLimitePlanicie(j, i)) {
					if (i == y && j == x)
						continue;
					else {
						getPosicoesAdjacentes(j, i, pos);
					}
				}
			}
		}

		if (pos.size() == 0) //Ñ tem posicoes livres, nao se move
			return -1;

		//Vai buscar a posicao random e mudas as coordenadas do ser para as coordenadas da posicao
		int randomPos = random(0, pos.size() - 1);
		p->setX(pos[randomPos].getX());
		p->setY(pos[randomPos].getY());
	}

	for (Colonia *c : colonias)
		c->elimina();

	vector<Ser*> copiaP = parias;
	for (Ser *s : copiaP)
		s->verificaSaude(nullptr, this);

	return verificaFinalJogo();
}

void Planicie::setNome(string nome){
	if (nome.length() == 0)
		nomeJogo = "defeito";

	nomeJogo = nome;
}

string Planicie::getNome() const { return nomeJogo; }

void Planicie::setNLinhas(int lin){ 
	if (lin > 0)
		nLinhas = lin;
}

void Planicie::setNColunas(int col){
	if (col > 0)
		nColunas = col;
}

int Planicie::getNLinhas() const { return nLinhas; }

int Planicie::getNColunas() const{ return nColunas; }

int Planicie::getNumColonias() const { return colonias.size(); }

Colonia * Planicie::pesquisaColonia(char letra)const{
	for (Colonia *c : colonias) {
		if (c->getLetra() == letra) {
			return c;
		}
	}
	return nullptr;
}


bool Planicie::addParia(Ser * s) {
	if (s == nullptr)
		return false;

	parias.push_back(s);
	return true;
}

void Planicie::removeParias(int x, int y) {

	int i = pesquisaParia(x, y);
	if (i == -1)
		return;

	delete parias[i];
	parias.erase(parias.begin() + i);

}

Ser * Planicie::pesquisaPariaPorIndice(int indice) const {
	if (indice < 0)
		return nullptr;

	return parias[indice];
}

int Planicie::pesquisaParia(int x, int y) const {
	for (unsigned int i = 0; i < parias.size(); i++) {
		if (parias[i]->getX() == x && parias[i]->getY() == y)
			return i;
	}
	return -1;
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

void Planicie::getPerfisComputador(vector<Perfil*>& perf){
	for (Perfil *p : perfisComputador)
		perf.push_back(p);
}

int Planicie::criaPerfil(char letra) {
	if (perfis.size() >= MAX_PERFIS)
		return 27;

	if (letra == 'i' || letra == 'j')
		return 40;

	if (pesquisaPerfil(letra) != -1)
		return 28;

	Perfil *p = new Perfil(letra);
	if (p == nullptr)
		return -1;

	perfis.push_back(p);
	return 29;
}

int Planicie::removePerfil(char letra){
	int i = pesquisaPerfil(letra);
	if (i == -1)
		return 32;

	delete perfis[i];
	perfis.erase(perfis.begin() + i);
	return 35;
}

int Planicie::addCaracteristica(int id, char letraPerfil){
	int i = pesquisaPerfil(letraPerfil);
	if (i == -1)
		return 32;

	return perfis[i]->addCaracteristica(id);
}

int Planicie::removeCaracteristica(int id, char letraPerfil){
	int i = pesquisaPerfil(letraPerfil);
	if (i == -1)
		return 32;

	return perfis[i]->removeCaracteristica(id);
}

int Planicie::setMoedas(int moedas){
	if (moedas < 0)
		return 5;

	for (Colonia *c : colonias)
		c->setMoedas(moedas);

	return 6;
}

int Planicie::fabricaSeres(int num, char letraPerfil){
	int i = pesquisaPerfil(letraPerfil);
	if (i == -1)
		return -1;

	if (num <= 0)
		return 5;

	Perfil *p = perfis[i];

	if (p == nullptr)
		return -1;

	Colonia *c = pesquisaColonia(LETRAS[0]);
	if (c == nullptr)
		return -1;

	return c->fabricaSeres(num, p, this);
}

int Planicie::setMoedas(char letra, int moedas){
	Colonia *c = pesquisaColonia(letra);

	if (c == nullptr)
		return -1;

	if (moedas <= 0)
		return 5;

	c->setMoedas(moedas);
	return 6;
}

int Planicie::constroiEdificio(int id, int lin, int col){

	//Caso adicionemos mais edifícios, ter isto em atenção
	if (id < 2 || id > 3)
		return 8;

	Colonia *c = pesquisaColonia(LETRAS[0]);
	if (c == nullptr)
		return -1;

	return c->constroiEdificio(id, lin, col, this, false);
}

int Planicie::constroiEdificio(int id, int lin, int col, char letra){
	
	//Caso adicionemos mais edifícios, ter isto em atenção
	if (id < 2 || id > 3)
		return 8;

	Colonia *c = pesquisaColonia(letra);
	if (c == nullptr)
		return -1;

	return c->constroiEdificio(id, lin, col, this, true);

}

int Planicie::reparaEdificio(int eid){
	Colonia *c = pesquisaColonia(LETRAS[0]);
	if (c == nullptr)
		return -1;

	if (eid < 0)
		return -1;

	return c->reparaEdificio(eid);
}

int Planicie::updgradeEdificio(int eid) {
	Colonia *c = pesquisaColonia(LETRAS[0]);
	if (c == nullptr)
		return -1;

	if (eid < 0)
		return -1;

	return c->updgradeEdificio(eid);
}

int Planicie::venderEdificio(int eid){
	Colonia *c = pesquisaColonia(LETRAS[0]);
	if (c == nullptr)
		return -1;

	if (eid < 0)
		return -1;

	return c->venderEdificio(eid);
}

int Planicie::setModoRecolhe() {
	Colonia *c = pesquisaColonia(LETRAS[0]);
	if (c == nullptr)
		return -1;

	return c->setModoRecolhe();
}

int Planicie::setModoAtaque() {
	Colonia *c = pesquisaColonia(LETRAS[0]);
	if (c == nullptr)
		return -1;

	return c->setModoAtaque();
}

void Planicie::sortearPerfisComputador(){

	for each (Perfil *p in perfis){
		perfisComputador.push_back(new Perfil(*p));
	}

	if (perfis.size() == 5) {
		for (int i = 0; i < 2; i++) {
			int randomP = random(0, perfisComputador.size() - 1);
			delete perfisComputador[randomP];
			perfisComputador.erase(perfisComputador.begin() + randomP);
		}
	}
	else if(perfis.size() == 4){
		int randomP = random(0, perfisComputador.size() - 1);
		delete perfisComputador[randomP];
		perfisComputador.erase(perfisComputador.begin() + randomP);
	}

	Perfil *p1 = new Perfil('i');
	Perfil *p2 = new Perfil('j');

	if (p1 == nullptr || p2 == nullptr)
		return;

	int randomC = 0;

	do {
		randomC = random(1, 14);
	}while (p1->addCaracteristica(randomC) == 31);

	do {
		randomC = random(1, 14);
	} while (p2->addCaracteristica(randomC) == 31);
	perfisComputador.push_back(p1);
	perfisComputador.push_back(p2);
}

void Planicie::sortearComandoComputador(){
	for each (Colonia *c in colonias){
		if (c->getLetra() != LETRAS[0]) {
			sortearModoAtaqueRecolhe(c);
			int randomCommand = random(1, 4);
			switch (randomCommand) {
			case 1: sortearContrucaoEdificio(c);
			case 2: sortearReparacaoEdificio(c);
			case 3: sortearUpgradeEdificio(c);
			case 4: sortearFabricacaoSeres(c);
			default:
				break;
			}
		}
	}
}

void Planicie::sortearContrucaoEdificio(Colonia * c){
	if (c == nullptr)
		return;

	Edificio *e = c->pesquisaEdificioPorTipo(ID_CASTELO);
	if (e == nullptr)
		return;

	int x = random(e->getX() - LIMITE_CASTELO, e->getX() + LIMITE_CASTELO);
	int y = random(e->getY() - LIMITE_CASTELO, e->getY() + LIMITE_CASTELO);
	int randomId = random(2, 3);

	c->constroiEdificio(randomId, y, x, this, false);
}

void Planicie::sortearReparacaoEdificio(Colonia * c){
	if (c == nullptr)
		return;

	vector<Edificio*> edificios;
	c->getEdificios(edificios);

	for each (Edificio *e in edificios){
		if (e == nullptr)
			return;

		int percentSaude = (e->getSaude() * 100) / e->getSaudeMaxima();
		if (e->getId() == ID_QUINTA || e->getId() == ID_TORRE) {
			if (percentSaude <= 25) {
				c->reparaEdificio(e->getEid());
			}
		}
		else if (e->getId() == ID_CASTELO) {
			if (percentSaude <= 50) {
				int res = c->reparaEdificio(e->getEid());

				if (res == 2) {
					sortearVendaEdificio(c, e);
					c->reparaEdificio(e->getEid());
				}
			}
		}
	}
}

void Planicie::sortearUpgradeEdificio(Colonia * c){
	if (c == nullptr)
		return;

	vector<Edificio*> edificios;
	c->getEdificios(edificios);

	for each (Edificio *e in edificios) {
		if (e == nullptr)
			return;
		if (e->getId() == ID_QUINTA) {
			int randomUpgrade = random(1, 100);
			if(randomUpgrade <= 30)
				c->updgradeEdificio(e->getEid());
		}
		else if (e->getId() == ID_TORRE) {
			int randomUpgrade = random(1, 100);
			if (randomUpgrade <= 60)
				c->updgradeEdificio(e->getEid());
		}
	}
}

void Planicie::sortearFabricacaoSeres(Colonia * c){

	int randomP = random(0, perfisComputador.size() - 1);
	Perfil *p = perfisComputador[randomP];
	if (p == nullptr)
		return;
	if (c->getMoedas() != 0 && p->getTotalPreco() != 0) {
		int numSeres = c->getMoedas() / p->getTotalPreco();
		int randomNumSeres = random(0, numSeres);
		c->fabricaSeres(randomNumSeres, new Perfil(*p), this);
	}
}

void Planicie::sortearModoAtaqueRecolhe(Colonia * c){
	if (c == nullptr)
		return;

	vector<Ser*> seres;
	c->getSeres(seres);

	int numSeres = 0;

	for each (Ser *s in seres) {
		if (s->getSaude() != 0) {
			int percentSaude = (s->getSaude() * 100) / s->getSaudeMaxima();
			if (percentSaude <= 35)
				numSeres++;
		}
	}

	if (numSeres != 0) {
		int percentSeresSaude = (numSeres * 100) / seres.size();
		if (percentSeresSaude >= 50)
			c->setModoRecolhe();
		else
			c->setModoAtaque();
	}
	else {
		c->setModoAtaque();
	}
}

void Planicie::sortearVendaEdificio(Colonia * c, Edificio * e){
	if (c == nullptr || e == nullptr)
		return;

	vector<Edificio*> edificios;
	c->getEdificios(edificios);

	for (int i = 0; i < 2; i++){
		int randomEid = random(0, edificios.size() - 1);
		if (edificios[randomEid] != e)
			c->venderEdificio(edificios[i]->getEid());
	}

}

int Planicie::verificaFinalJogo(){
	
	vector<Ser*> seres;
	vector<Edificio*> edificios;	

	int numSeres = 0;
	int numEdificios = 0;

	for (unsigned int i = 1; i < colonias.size(); i++) {
		colonias[i]->getSeres(seres);
		colonias[i]->getEdificios(edificios);

		numSeres += seres.size();
		numEdificios += edificios.size();

		seres.clear();
		edificios.clear();
	}

	if (numSeres == 0 && numEdificios == 0)
		return 39;

	seres.clear();
	edificios.clear();

	Colonia *c = pesquisaColonia(LETRAS[0]);
	if (c == nullptr)
		return -1;

	c->getSeres(seres);
	c->getEdificios(edificios);

	if (seres.empty() && edificios.empty())
		return 38;
	
	return -1;
}

int Planicie::mudaCastelo(char letra, int lin, int col){
	Colonia *c = pesquisaColonia(letra);
	if (c == nullptr)
		return -1;

	return c->mudaCastelo(col, lin, this);
}
