#include "Headers\library.h"
using namespace std;

int main() {
	intro();
	int exit;
	do {
		exit = menu();
	} while (exit == 1);
	return 0;
}