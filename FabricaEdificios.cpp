#include "FabricaEdificios.h"
#include "Edificio.h"

Edificio * FabricaEdificios::cria(int id, int x, int y) {
	switch (id) {
	case 2: return new Torre(x, y, id);
	case 3: return new Quinta(x, y, id);
	default: return nullptr;
	}
}