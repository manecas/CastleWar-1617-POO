#include "Ser.h"
#include "Colonia.h"
#include "Planicie.h"

#include <sstream>

using std::ostringstream;

//--------------------------SER-----------------------------------------
Ser::Ser(const Perfil & p): saudeMaxima(10), perfil(p), numAtaques(0) {
	ataque += p.getTotalAtaque();
	defesa += p.getTotalDefesa();
	saudeMaxima += p.getSaudeMaxima();
	saude = saudeMaxima;
}

void Ser::atua(Colonia * c, Planicie * p) { perfil.atua(this, c, p); }

Ser * Ser::duplica() const{ return new Ser(*this); }

int Ser::getTotalPreco() const{ return perfil.getTotalPreco(); }

int Ser::getSaude() const { return saude; }

int Ser::getSaudeMaxima() const { return saudeMaxima; }

int Ser::getNumAtaques() const { return numAtaques; }

char Ser::getLetraPerfil() const { return perfil.getLetra(); }

void Ser::reiniciaCaracteristicas(){ perfil.reiniciaCaracteristicas(); }

void Ser::verificaSaude(Colonia * c, Planicie * p){
	if (saude == 0) {
		if (c != nullptr)
			c->removeSeres(x, y);
		else if(p != nullptr)
			p->removeParias(x, y);
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

void Ser::aumentaSaudeMaxima(int saudeMax){ saudeMaxima += saudeMax; }

void Ser::aumentaNumAtaques(int num){ numAtaques += num; }

void Ser::setY(int yy){ y = yy; }

void Ser::setX(int xx) { x = xx; }

void Ser::setNumAtaques(int ataques){
	if (ataques < 0) {
		numAtaques = 0;
		return;
	}

	numAtaques = ataques;
}

void Ser::setAtaque(int at){ ataque = at; }

void Ser::setDefesa(int def) { defesa = def; }

void Ser::recebeAtaque(int forcaAtaque){

	if(forcaAtaque > getTotalDefesa())
		diminuiSaude(forcaAtaque - getTotalDefesa());
	else
		diminuiSaude(1);

}

void Ser::aumentaDefesa(int d) { defesa += d; }

void Ser::diminuiAtaque(int a){
	if (ataque - a < 0) {
		ataque = 0;
		return;
	}

	ataque -= a;
}

void Ser::aumentaAtaque(int a) { ataque += a; }

void Ser::aumentaSaude(int s) {
	if (saude + s >= saudeMaxima) {
		saude = saudeMaxima;
		return;
	}
	saude += s;
}

void Ser::diminuiSaude(int s){
	if (saude - s < 0) {
		saude = 0;
		return;
	}

	saude -= s;
}
