#include "Posicao.h"

Posicao::Posicao(int xx, int yy) : x(xx), y(yy){ }

Posicao::Posicao(int xx, int yy, bool vaz) : x(xx), y(yy), vazia(vaz){ }

int Posicao::getX() const { return x; }

int Posicao::getY() const { return y; }

bool Posicao::estaVazia() const { return vazia; }

void Posicao::setVazia(bool vaz){ vazia = vaz; }

void Posicao::setX(int xx){ x = xx; }

void Posicao::setY(int yy){ y = yy; }


