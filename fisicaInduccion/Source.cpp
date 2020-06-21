#include <iostream>
//#include <functional>
#include "faraday.hpp"
#include "mathp.hpp"
//btw: En teoría vec3 existe con GLSL 
//(y en foros para consultas son tipos creando librerías aparte)
//... so
//podemos pasar a OpenGL lit y hasta con eso graficar
//pero no me siento en la capacidad gráfica aún xd
//Please vote.

//Otra Consulta: Se ahorra tiempo de computacion (creo) en tener solo un componentes[3] en vec3, so... cambiazo o se queda en (x,y,z)

using namespace std;

class detector {
	polinomio* B; //Campo Mágnético generado por una corriente I que recorre la superficie (También puede ser afectado por radio)
	vec3* posicion; //Posición del centro del detector
	vec3* dirB; //Direccion del campo magnético
public:
	detector(ushort nTerB) {
		B = new polinomio(nTerB);
		posicion = new vec3(0, 0, 0);
		dirB = new vec3(0, 0, -1);
	}
	~detector() {
		delete B;
		delete posicion;
		delete dirB;
	}
	void mover(ushort direccion) {
		
	}
};

class objeto {
	vec3 posicion;

};
class controlador {
	detector* detectorMetales;
	int t;
	bool cambio;
	controlador( ) {
		//detectorMetales = new detectorMetales(B, posicion, dirB);
	}
	~controlador() {
		delete detectorMetales;
	}
	void iniciar() {

	}
};

int main() {
	double c[3] = {1,1,2};
	float e[3] = {0,2,3};
	polinomio* Ejemplo = new polinomio(3, &c[0], &e[0]);
	Ejemplo->mostrar();
	delete Ejemplo;
	system("pause");
	return 0;
}