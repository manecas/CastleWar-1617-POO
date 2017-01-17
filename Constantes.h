#ifndef _CONSTANTES
#define _CONSTANTES

#include <cstdlib>

namespace Constantes{

	const char VERTICAL = (char)179;
	const char HORIZONTAL = (char)196;

	const int ID_CASTELO = 1;
	const int ID_TORRE = 2;
	const int ID_QUINTA = 3;

	const int ID_BANDEIRA = 1;
	const int ID_SUPERIOR = 2;
	const int ID_PELE_DURA = 3;
	const int ID_ARMADURA = 4;
	const int ID_FACA = 5;
	const int ID_ESPADA = 6;
	const int ID_AGRESSAO = 7;
	const int ID_ECOLOGICO = 8;
	const int ID_HEATSEEKER = 9;
	const int ID_BUILDSEEKER = 10;
	const int ID_WALKER = 11;
	const int ID_REMEDIO = 12;
	const int ID_SECONDCHANCE = 13;
	const int ID_ALUNO = 14;

	const char LETRAS[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
		'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	const int LINHAS = 20;
	const int COLUNAS = 40;

	//Limites coordenadas
	const int LIMITE_CASTELO = 10;
	const int Y_MIN = 0;
	const int X_MIN = 0;

	const int MAX_PERFIS = 5;

	static int random(int min, int max) {
		return min + rand() % (int)(max - min + 1);
	}
}

#endif // !_CONSTANTES
