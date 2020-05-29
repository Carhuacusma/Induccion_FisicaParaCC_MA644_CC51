#include <iostream>
//#include <functional>
#include "faraday.hpp"
#include "mathp.hpp"
using namespace std;

class detector {
	polinomio B; //Campo Mágnético generado por una corriente I que recorre la superficie (También puede ser afectado por radio)
	vec3 posicion; //Posición del centro del detector
	vec3 dirB; //Direccion del campo magnético
};

class objeto {
	vec3 posicion;

};

class controlador {
	detector* detectorMetales;
	int t;
	bool cambio;
	void iniciar() {

	}
};

int main() {

	system("pause");
	return 0;
}