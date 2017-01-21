#include "Posicao.h"
#include "Ser.h"
#include "Edificio.h"

Posicao::Posicao(int xx, int yy) : x(xx), y(yy){ }

Posicao::Posicao(int xx, int yy, bool vaz) : x(xx), y(yy){ }

int Posicao::getX() const { return x; }

int Posicao::getY() const { return y; }

void Posicao::setX(int xx){ x = xx; }

void Posicao::setY(int yy){ y = yy; }

void Posicao::getPosicoesSeres(vector<Ser*>& seres, vector<Posicao> & pos){
	for each (Ser *ser in seres) {
		if (ser == nullptr)
			continue;;
		Posicao p(ser->getX(), ser->getY());
		pos.push_back(p);
	}
}

void Posicao::getPosicoesEdificios(vector<Edificio*>& edificios, vector<Posicao> & pos) {
	for each (Edificio *edi in edificios) {
		if (edi == nullptr)
			continue;;
		Posicao p(edi->getX(), edi->getY());
		pos.push_back(p);
	}
}

Posicao *Posicao::getPosicaoMovimento(int xOri, int yOri, int xDest, int yDest){
	if (xDest < xOri && yDest < yOri) {
		return new Posicao(xOri - 1, yOri - 1);
	}
	else if (xDest > xOri && yDest < yOri) {
		return new Posicao(xOri + 1, yOri - 1);
	}
	else if (xDest > xOri && yDest < yOri) {
		return new Posicao(xOri + 1, yOri - 1);
	}
	else if (xDest > xOri && yDest > yOri) {
		return new Posicao(xOri + 1, yOri + 1);
	}
	else if (xDest < xOri && yDest > yOri) {
		return new Posicao(xOri - 1, yOri + 1);
	}
	else if (yDest > yOri) {
		return new Posicao(xOri, yOri + 1);
	}
	else if (yDest < yOri) {
		return new Posicao(xOri, yOri - 1);
	}
	else if (xDest > xOri) {
		return new Posicao(xOri + 1, yOri);
	}
	else if (xDest < xOri) {
		return new Posicao(xOri - 1, yOri);
	}
	return new Posicao(xOri, yOri);
}

Posicao * Posicao::inimigoMaisProximo(vector<Posicao>& pos, int xOri, int yOri){
	if (pos.size() > 0) {
		int indexMaisProxima;
		double aux = 2000;
		double distancia = 0;
		for (unsigned int i = 0; i < pos.size(); i++) {
			distancia = sqrt(pow(xOri - pos[i].getX(), 2) + pow(yOri - pos[i].getY(), 2));
			if (distancia < aux) {
				aux = distancia;
				indexMaisProxima = i;
			}
		}
		return &pos[indexMaisProxima];
	}

	return nullptr;
}


