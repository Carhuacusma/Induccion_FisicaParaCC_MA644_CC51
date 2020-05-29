#pragma once
#include <math.h>

typedef unsigned short ushort;

class vec3 {
public:
	double x, y, z;
	vec3(double x, double y, double z) : x(x), y(y), z(z) { }
	vec3(vec3* vector) {
		if (vector == nullptr) {
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}
		else {
			this->x = vector->x;
			this->y = vector->y;
			this->z = vector->z;
		}
	}
};

//EN FORMATO: P(x) = a + bx + c(x^2) + d(x^3) + e(x^5)
class polinomio {
	ushort nter;				// n terminos
	double* c;				// coeficientes
	float* exp;	// exponentes
public:
	polinomio(ushort nterminos, double* coeficientes, float* exponentes) : nter(nterminos) {
		this->c = coeficientes;
		this->exp = exponentes;
	}
	polinomio(ushort nterminos) : nter(nterminos) {
		//Lit P(X) = 1 + x + x^2 + x^3
		this->c = new double[nterminos];
		this->exp = new float[nterminos];
		for (ushort i = 0; i < nterminos; i++) {
			this->c[i] = 1;
			this->exp[i] = i;
		}
	}

	~polinomio() {
		delete[] c;
		delete[] exp;
	}

	ushort getN() {	return this->nter;}
	double resultado(double x) {
		double res = 0;
		for (ushort i = 0; i < nter; i++) {
			ushort e = this->exp[i];
			double j = this->c[i];
			res += j*pow(x, e);
			// F(x) = primer coeficiente * (x ^ primer exponente) + segundo coeficiente 
		}
		return res;
	}

	//TO DO: LEER PORQUE FORMATO P(X) HARDCODEADO
	//En teoría lo mejor es aplicar esto pero incluye tener funciones más grandes que solo polinomios XD, so f
	//Send help si posible (O limitar nuestro B a que sea solamente polinomio (o sen y cos porque creo sí hay librerías))
	//https://stackoverflow.com/questions/1559695/implementing-the-derivative-in-c-c
	polinomio* derivada() {
		//HARDCODEADO AL FORMATO P(X) = a*x^0 + b*x^1 (puede saltarse, por eso vector de exponentes)
		double* newCoef = new double[nter];
		float* newExp = new float[nter];
		ushort j = 0;
		for (ushort i = 0; i < nter; i++) {
			double newCoefAux = this->exp[i]*this->c[i];
			float newExpAux = this->exp[i] - 1;
			if (newCoef != 0) {
				newCoef[j] = newCoefAux;
				newExp[j] = newExpAux;
				j++;
			}
		}
		if (j == this->nter)
			return new polinomio(j, newCoef, newExp);

		//Para evitar tener un último término que apunta a la basura
		//(Considerando eliminarlo por si se puede usar el espacio original en algo más y evitar cuatro arreglos)
		//(Ya que igual j pasa como nter que determina hasta donde llegar)
		double* newC = new double[j];
		float* newE = new float[j];
		for (short i = 0; i < j; i++) {
			newC[i] = newCoef[i];
			newE[i] = newExp[i];
		}
		return new polinomio(j, newC, newE);
	}
	polinomio* multiplicacion(double coef) {
		double* newC = new double[this->nter];
		float* newE = new float[this->nter];
		for (ushort i = 0; i < this->nter; i++) {
			newC[i] = this->c[i] * coef;
			newE[i] = this->exp[i];
		}
		//Para evitar error si elimina el polinomio padre antes del resultado se envía otro puntero que crea por su cuenta otro new
		return new polinomio(this->nter, newC, newE);
	}
};

vec3 suma(vec3* v1, vec3* v2) {
	return vec3(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}
vec3 resta(vec3* v1, vec3* v2) {
	return vec3(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}