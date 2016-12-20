#ifndef _SER
#define _SER

#include <string>

using std::string;

#include "Perfil.h"
class Colonia;
class Planicie;

class Ser {
	Perfil perfil;
	bool entrouCastelo;
	int numAtaques; //Aqui ou nas caracteristicas?
	int saudeMaxima;
	int saude;
	int x;
	int y;
public:
	Ser(const Perfil & p);
	virtual ~Ser() = default;
	int getX()const;
	int getY()const;
	int getTotalPreco()const;
	int getTotalAtaque()const;
	int getTotalDefesa()const;
	int getTotalVelocidade()const;
	int getSaude()const;
	int getSaudeMaxima()const;
	int getNumAtaques()const;
	char getLetraPerfil()const;

	bool getEntrouCastelo()const;
	void setEntrouCastelo(bool val);

	void aumentaSaude(int s);
	void aumentaSaudeMaxima(int saudeMax);
	void aumentaNumAtaques(int num);

	void setY(int yy);
	void setX(int xx);
	void setSaude(int s);
	void atua(Colonia * c, Planicie * p);
	Ser * duplica()const;

	//Verificar destruicao seres
	void verificaSaude(Colonia * c);
	string toString()const;
};
#endif // !_SER

