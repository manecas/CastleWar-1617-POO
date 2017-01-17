#ifndef _EDIFICIO
#define _EDIFICIO

#include <string>
#include <iostream>

using std::string;
using std::cout;

class Colonia;
class Perfil;
class Planicie;

class Edificio {
	static int contador;
	int eid;
	string nome;
	int id;
	int custo;
	int saudeMaxima;
	int saude;
	int defesa;
	int x;
	int y;
	int custoUpgrade;
	int numUpgrades;
public:
	Edificio(string n, int c, int s, int d, int xx, int yy, int id, int saudeM, 
		int custoUpgrade, int numUpgrades);
	/*Edificio(const Edificio & ob);
	Edificio & operator=(const Edificio & ob);*/
	string getNome()const;
	int getId()const;
	int getCusto()const;
	int getSaude()const;
	int getDefesa()const;
	int getCustoUpgrade()const;
	int getNumUpgrades()const;
	int getY()const;
	int getX()const;
	int getEid()const;
	int getSaudeMaxima()const;
	void aumentaSaudeMaxima(int saudeMax);
	void aumentaSaude(int s);
	void diminuiSaude(int s);
	void recebeAtaque(int forcaAtaque);

	void aumentaUpgrades(int num);
	static void reiniciaContador();
	void setY(int yy);
	void setX(int xx);
	void setDefesa(int d);

	virtual int getAtaque()const = 0;
	virtual string toString()const;
	virtual int upgrade(Colonia * c) = 0; //Ir ver se existe moedas
	virtual void efeito(Colonia * c, Planicie * p) = 0;
	virtual void verificaDestruicao(Colonia * c);
	virtual Edificio * duplica()const = 0;
	virtual int fabricaSeres(Colonia * c, int num, Perfil * p) = 0;
};

//CASTELO
class Castelo : public Edificio{
public:
	Castelo(int xx, int yy, int id);
	virtual int upgrade(Colonia * c);
	virtual void efeito(Colonia * c, Planicie * p);
	virtual Edificio * duplica()const;
	virtual int fabricaSeres(Colonia * c, int num, Perfil * p);
	virtual int getAtaque()const;
};

//TORRE
class Torre : public Edificio {
	int ataque;
	int distAtaque;
public:
	Torre(int xx, int yy, int id);
	virtual string toString()const;
	virtual int upgrade(Colonia * c);
	virtual void efeito(Colonia * c, Planicie * p);
	virtual Edificio * duplica()const;
	virtual int fabricaSeres(Colonia * c, int num, Perfil * p);
	virtual int getAtaque()const;
};

//QUINTA
class Quinta : public Edificio {
	int moedas;
public:
	Quinta(int xx, int yy, int id);
	int getMoedas()const;
	virtual string toString()const;
	virtual int upgrade(Colonia * c);
	virtual void efeito(Colonia * c, Planicie * p);
	virtual Edificio * duplica()const;
	virtual int fabricaSeres(Colonia * c, int num, Perfil * p);
	virtual int getAtaque()const;
};

#endif // !_EDIFICIO

