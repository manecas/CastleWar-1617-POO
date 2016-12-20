#ifndef _CARACTERISTICA
#define _CARACTERISTICA

#include <string>

using std::string;

class Ser;
class Planicie;

class Caracteristica {
	string nome;
	int id;
	int custoMonetario;
	int custoForca;
public:
	Caracteristica(const string & n, int iden, int custoM, int custoF);
	Caracteristica(const Caracteristica & ob);
	Caracteristica & operator=(const Caracteristica & ob);
	virtual ~Caracteristica() = default;
	string getNome()const;
	int getId()const;
	int getCustoMonetario()const;
	int getCustoForca()const;

	virtual string toString()const;
	// = 0 (abstracta ou seja não podem ser criados objectos desta classe)
	virtual void efeito(Ser * s, Planicie * p) = 0; //Recebe um ponteiro para 
	//ser para ir modificar algum atributo ao proprio  ser
	virtual Caracteristica * duplica()const = 0;
	virtual int getVelocidade()const = 0;
	virtual int getAtaque()const = 0;
	virtual int getDefesa()const = 0; 

	bool operator==(const Caracteristica * const c)const;
};

class Bandeira : public Caracteristica {

public:
	Bandeira();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Superior : public Caracteristica {
	int saudeMax;
public:
	Superior();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class PeleDura : public Caracteristica {
	int defesa;
public:
	PeleDura();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Armadura : public Caracteristica {
	int defesa;
public:
	Armadura();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Faca : public Caracteristica {
	int ataque;
public:
	Faca();
	virtual int getVelocidade()const ;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Espada : public Caracteristica {
	int ataque;
	int ataqueIncremento;
public:
	Espada();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Agressao : public Caracteristica {
	
public:
	Agressao();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Ecologico : public Caracteristica {

public:
	Ecologico();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};


class HeatSeeker : public Caracteristica {
	int velocidade;
public:
	HeatSeeker();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class BuildSeeker : public Caracteristica {
	int velocidade;
public:
	BuildSeeker();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Walker : public Caracteristica {
	int velocidade;
public:
	Walker();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Remedio : public Caracteristica {
	int saudeRecuperacao;
	bool usado;
public:
	Remedio();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class SecondChance : public Caracteristica {
	bool morreu;
public:
	SecondChance();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Aluno : public Caracteristica {

public:
	Aluno();
	virtual int getVelocidade()const;
	virtual int getAtaque()const;
	virtual int getDefesa()const;
	virtual void efeito(Ser * s, Planicie * p);
	virtual Caracteristica * duplica()const;
};
#endif // !_CARACTERISTICA
