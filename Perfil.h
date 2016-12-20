#ifndef _PERFIL
#define _PERFIL

#include <vector>
#include <string>

using std::string;
using std::vector;

class Caracteristica;
class Ser;
class Planicie;

class Perfil {
	int preco;
	int forca;
	char letra;
	vector<Caracteristica*> caracteristicas;
public:
	Perfil(char l);
	Perfil(const Perfil & ori);
	Perfil & operator=(const Perfil & ob);
	virtual ~Perfil();
	int getForca()const;
	int getTotalPreco()const;
	int getTotalAtaque()const;
	int getTotalDefesa()const;
	int getTotalVelocidade()const;
	void getCaracteristicas(vector<Caracteristica*> & carac);
	char getLetra()const;
	int pesquisaCaracteristica(int id);
	bool addCaracteristica(int id);
	bool removeCaracteristica(int id);
	void atua(Ser * s, Planicie * p);
	string toString()const;
};

#endif // !_PERFIL

