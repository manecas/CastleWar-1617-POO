#include "FabricaCaracteristicas.h"
#include "Caracteristica.h"

Caracteristica * FabricaCaracteristicas::cria(int id){
	switch (id){
		case 1: return new Bandeira();
		case 2: return new Superior();
		case 3: return new PeleDura();
		case 4: return new Armadura();
		case 5: return new Faca();
		case 6: return new Espada();
		case 7: return new Agressao();
		case 8: return new Ecologico();
		case 9: return new HeatSeeker();
		case 10: return new BuildSeeker();
		case 11: return new Walker();
		case 12: return new Remedio();
		case 13: return new SecondChance();
		case 14: return new Aluno();
		default: return nullptr;
	}
}
