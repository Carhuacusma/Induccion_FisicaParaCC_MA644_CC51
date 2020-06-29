#include <iostream>
//#include <functional>
#include "faraday.hpp"
#include "mathp.hpp"
#include "ejemplo1.hpp"
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
	detector() {
		this->B = nullptr;
		this->posicion = nullptr;
		this->dirB = nullptr;
	}
	detector(ushort nTerB) {
		B = new polinomio(nTerB);
		posicion = new vec3(0, 0, 0);
		dirB = new vec3(0, 0, -1);
	}
	detector(polinomio* nB): B(nB) {
		this->posicion = new vec3(0, 0, 0);
		this->dirB = new vec3('k', -1); // (0,0,-1)
	}
	detector(polinomio* nB, vec3* dir, vec3* pos): B(nB), dirB(dir), posicion(pos) { }

	~detector() {
		delete B;
		delete posicion;
		delete dirB;
	}
	
	void cambiarB(polinomio* newB) {
		if (this->B) delete B;
		this->B = newB;
	}
	void mover(vec3 &direccion) {
		if (!this->posicion) this->posicion = new vec3('i', 0); // (0,0,0)
		this->posicion->selfSuma(&direccion);
	}
};

class objeto {
	vec3 posicion;

};

class controlador {
	detector* detectorMetales;
	int t;
	bool cambio;
	controlador() { }
	~controlador() {
		delete detectorMetales;
	}
	void iniciar() {

	}
	void menu() {

	}
};

int main() {
	ce_torre* torre = new ce_torre(195, 0.0561*pow(M_PI, 2), new vec3(0, 1, 0));
	double* coef = new double[3];
	float* exp = new float[3];
	coef[0] = 0.250; coef[1] = -0.559; coef[2] = 45.6;
	exp[0] = 3; exp[1] = 2; exp[2] = 1;
	polinomio* B = new polinomio(3,coef,exp,false);
	ce_campo* campo = new ce_campo(B, new vec3(0, 1, 0));

	ce_control control = ce_control(torre, campo);
	control.secuencia();
	system("pause");
	return 0;
}