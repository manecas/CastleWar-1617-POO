#ifndef _POSICAO
#define _POSICAO

#include <vector>
using std::vector;

class Ser;
class Edificio;

class Posicao {
	int x;
	int y;
public:
	Posicao(int xx, int yy);
	Posicao(int xx, int yy, bool vaz);
	int getX()const;
	int getY()const;
	void setX(int xx);
	void setY(int yy);
	static void getPosicoesSeres(vector<Ser*> & edificios, vector<Posicao> & pos);
	static void getPosicoesEdificios(vector<Edificio*> & seres, vector<Posicao> & pos);
	static Posicao *getPosicaoMovimento(int xSer, int ySer, int xDest, int yDest);
	static Posicao *inimigoMaisProximo(vector<Posicao> & pos, int xOri, int yOri);
};



#endif // _POSICAO

