#ifndef _EDIFICIO
#define _EDIFICIO

#include <string>

using std::string;

class Colonia;
class Perfil;
class Planicie;

class Edificio {
	static int contador;
	int eid;
	string nome;
	int id;
	int custo;
	int saude;
	int defesa;
	int x;
	int y;
public:
	Edificio(string n, int c, int s, int d, int xx, int yy, int id);
	Edificio(const Edificio & ob);
	Edificio & operator=(const Edificio & ob);
	string getNome()const;
	int getId()const;
	int getCusto()const;
	int getSaude()const;
	int getDefesa()const;
	int getY()const;
	int getX()const;
	int getEid()const;

	void setY(int yy);
	void setX(int xx);
	void setDefesa(int d);

	virtual string toString()const;
	virtual bool upgrade(Colonia * c) = 0; //Ir ver se existe moedas
	virtual void efeito(Colonia * c, Planicie * p) = 0;
	virtual void verificaDestruicao(Colonia * c);
	virtual Edificio * duplica()const = 0;
	virtual int fabricaSeres(Colonia * c, int num, Perfil * p) = 0;
};

//CASTELO
class Castelo : public Edificio{
public:
	Castelo(int xx, int yy, int id);
	virtual bool upgrade(Colonia * c);
	virtual void efeito(Colonia * c, Planicie * p);
	virtual Edificio * duplica()const;
	virtual int fabricaSeres(Colonia * c, int num, Perfil * p);
};

//TORRE
class Torre : public Edificio {
	int ataque;
public:
	Torre(int xx, int yy, int id);
	int getAtaque()const;
	virtual string toString()const;
	virtual bool upgrade(Colonia * c);
	virtual void efeito(Colonia * c, Planicie * p);
	virtual Edificio * duplica()const;
	virtual int fabricaSeres(Colonia * c, int num, Perfil * p);
};

//QUINTA
class Quinta : public Edificio {
	int moedas;
public:
	Quinta(int xx, int yy, int id);
	int getMoedas()const;
	virtual string toString()const;
	virtual bool upgrade(Colonia * c);
	virtual void efeito(Colonia * c, Planicie * p);
	virtual Edificio * duplica()const;
	virtual int fabricaSeres(Colonia * c, int num, Perfil * p);
};

#endif // !_EDIFICIO

