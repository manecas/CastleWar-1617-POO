#ifndef _POSICAO
#define _POSICAO


class Posicao {
	int x;
	int y;
	bool vazia;
public:
	Posicao(int xx, int yy);
	Posicao(int xx, int yy, bool vaz);
	int getX()const;
	int getY()const;
	bool estaVazia()const;
	void setVazia(bool vaz);
	void setX(int xx);
	void setY(int yy);
};



#endif // _POSICAO

