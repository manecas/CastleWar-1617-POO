#include "Ser.h"
#include "Colonia.h"

#include <sstream>

using std::ostringstream;

//--------------------------SER-----------------------------------------
Ser::Ser(const Perfil & p):saude(10), saudeMaxima(10), perfil(p), 
entrouCastelo(true), numAtaques(0) {
	
}

void Ser::atua(Colonia * c, Planicie * p) {
	perfil.atua(this, c, p);

	//if (c == nullptr)
	//	return;
}

Ser * Ser::duplica() const{ return new Ser(*this); }

int Ser::getTotalPreco() const{ return perfil.getTotalPreco(); }

int Ser::getSaude() const { return saude; }

int Ser::getSaudeMaxima() const { return saudeMaxima + perfil.getSaudeMaxima(); }

int Ser::getNumAtaques() const { return numAtaques; }

char Ser::getLetraPerfil() const { return perfil.getLetra(); }

bool Ser::getEntrouCastelo() const { return entrouCastelo; }

void Ser::setEntrouCastelo(bool val) { entrouCastelo = val; }

void Ser::mandarRecolher(Colonia * c){

}

void Ser::verificaSaude(Colonia * c){
	if (c == nullptr)
		return;

	if (saude == 0) {
		c->removeSeres(x, y);
	}
}

string Ser::toString() const {
	ostringstream out;

	out << perfil.toString() << "\n";
	out << "Saude: " << saude << " ataque: " << getTotalAtaque()
		<< " defesa: " << getTotalDefesa() << "localizacao: (" << x << "," << y << ")" << "\n";

	return out.str();
}

int Ser::getY() const{ return y; }

int Ser::getX() const{ return x; }

int Ser::getTotalAtaque() const { return ataque; }

int Ser::getTotalDefesa() const { return defesa; }

int Ser::getTotalVelocidade() const { return velocidade; }

void Ser::aumentaSaude(int s){
	if (saude + s >= saudeMaxima) {
		saude = saudeMaxima;
		return;
	}
	saude += s;
}

void Ser::aumentaSaudeMaxima(int saudeMax){ saudeMaxima += saudeMax; }

void Ser::aumentaNumAtaques(int num){ 
	if (numAtaques + num == 3) {
		numAtaques = 0;
		return;
	}

	numAtaques += num; 
}

void Ser::setY(int yy){ y = yy; }

void Ser::setX(int xx) { x = xx; }

void Ser::setAtaque(int at){ ataque = at; }

void Ser::setDefesa(int def) { defesa = def; }

void Ser::recebeAtaque(int forcaAtaque){

	if(forcaAtaque > getTotalDefesa())
		diminuiSaude(forcaAtaque - getTotalDefesa());
	else
		diminuiSaude(1);

}

void Ser::diminuiSaude(int s){
	if (saude - s < 0) {
		saude = 0;
		return;
	}

	saude -= s;
}
