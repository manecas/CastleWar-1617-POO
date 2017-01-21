#ifndef _CARACTERISTICA
#define _CARACTERISTICA

#include <string>

using std::string;

class Ser;
class Planicie;
class Colonia;

class Caracteristica {
	string nome;
	int id;
	int custoMonetario;
	int custoForca;
	bool usou;
public:
	Caracteristica(const string & n, int iden, int custoM, int custoF, bool us);
	virtual ~Caracteristica() = default;
	string getNome()const;
	int getId()const;
	int getCustoMonetario()const;
	int getCustoForca()const;
	bool jaUsou()const;
	void setUsou(bool us);

	virtual string toString()const;
	// = 0 (abstracta ou seja não podem ser criados objectos desta classe)
	virtual void efeito(Ser * s, Colonia * c, Planicie * p) = 0; //Recebe um ponteiro para 
	//ser para ir modificar algum atributo ao proprio  ser
	virtual Caracteristica * duplica()const = 0;
	virtual int getSaudeMaxima()const = 0;
	virtual int getAtaque() = 0;
	virtual int getDefesa()const = 0; 
	virtual int getVelocidade()const = 0;
};

class Bandeira : public Caracteristica {
	Colonia *c;
public:
	Bandeira();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Superior : public Caracteristica {
	int saudeMax;
public:
	Superior();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class PeleDura : public Caracteristica {
	int defesa;
public:
	PeleDura();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Armadura : public Caracteristica {
	int defesa;
public:
	Armadura();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Faca : public Caracteristica {
	int ataque;
public:
	Faca();
	virtual int getSaudeMaxima()const ;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Espada : public Caracteristica {
	int ataque;
	int ataqueIncremento;
	bool decrementou;
public:
	Espada();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Agressao : public Caracteristica {
	int distAtaque;
public:
	Agressao();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Ecologico : public Caracteristica {
	int distAtaque;
public:
	Ecologico();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class HeatSeeker : public Caracteristica {
	int velocidade;
public:
	HeatSeeker();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class BuildSeeker : public Caracteristica {
	int velocidade;
public:
	BuildSeeker();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Walker : public Caracteristica {
	int velocidade;
public:
	Walker();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Remedio : public Caracteristica {
	int saudeRecuperacao;
public:
	Remedio();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class SecondChance : public Caracteristica {
	bool morreu;
public:
	SecondChance();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};

class Aluno : public Caracteristica {
	bool morreu;
	int nMortes;
public:
	Aluno();
	virtual int getSaudeMaxima()const;
	virtual int getAtaque();
	virtual int getDefesa()const;
	virtual int getVelocidade()const;
	virtual void efeito(Ser * s, Colonia * c, Planicie * p);
	virtual Caracteristica * duplica()const;
};
#endif // !_CARACTERISTICA
