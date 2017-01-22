#include "Planicie.h"
#include "Interface.h"
#include <time.h>
#include <assert.h>
#include "Consola.h"

#include <iostream>

using std::cout;

int main(){
	srand((unsigned int)time(NULL));
	//setlocale(LC_ALL, "Portuguese");

	Interface i;
	i.menuInicial();

	return 0;
}