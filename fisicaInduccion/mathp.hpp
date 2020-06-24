#pragma once
#include <math.h>
#include <string>
#include <iostream>
typedef unsigned short ushort;

#pragma region Clases

class vec3 {
public:
	double x, y, z;
	vec3(char o) {
		o = tolower(o);
		this->x = 0; this->y = 0; this->z = 0;
		switch (o) {
		case 'i':
			this->x = 1; break;
		case 'j':
			this->y = 1; break;
		case 'k':
			this->z = 1; break;
		}
	}
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
	double magnitud() {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
	void selfSuma(vec3* dir) {
		this->x = this->x + dir->x;
		this->y = this->y + dir->z;
	}
	void selfProdVecEsc(double c) {
		//producto const * vector
		this->x = this->x*c;
		this->y = this->y*c;
		this->z = this->z*c;
	}
};

//EN FORMATO: P(x) = a + bx + c(x^2) + d(x^3) + e(x^5)
//No acepta coeficiente[i] = 0
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
			res += j*std::pow(x, e);
			// F(x) = primer coeficiente * (x ^ primer exponente) + segundo coeficiente 
		}
		return res;
	}

	std::string toString(char x = 'x') {
		std::string res = " ";
		bool sigpos = false;
		for (ushort i = 0; i < this->nter; i++) {
			//Si no es el primero, añadir el signo + cuando sea positivo (Lectura humana)
			if (sigpos && this->c[i] > 0) res += "+ ";
			//Si es 1 o -1, no imprimirlo
			//BTW: PUEDE SER BORRADO, ES SUPERFLUO XD
			switch (int(this->c[i])) {
				case -1: res += "- "; break;
				case 1: break;
				default:
					res += std::to_string(this->c[i]); break;
			}
			//por otro error raro que había antes, pero lo dejo para que sea entendible
			//el string del exponente que se le va a poner a x
			std::string exp = std::to_string(this->exp[i]);
			//idk why, pero piensa que quiero usar String de namespace System
			// --- poll: Con WindowsForms como que da igual porque es muy Windows so.. normal usar su String xd
			// --------- Repito,¿quieren usar Forms?
			res += x + (std::string)"^(" + exp + (std::string)") ";
			if (!sigpos) sigpos = true; //SOLO La primera vez es falso
		}
		return res;
	}
	void mostrar(char x = 'x') { std::cout << this->toString(x); }

	//TO DO: LEER PORQUE FORMATO P(X) HARDCODEADO
	//En teoría lo mejor es aplicar esto pero incluye tener funciones más grandes que solo polinomios XD, so f
	//Send help si posible (O limitar nuestro B a que sea solamente polinomio (o sen y cos porque creo sí hay librerías))
	//https://stackoverflow.com/questions/1559695/implementing-the-derivative-in-c-c
	polinomio* derivada() {
		//HARDCODEADO AL FORMATO P(X) = a*x^0 + b*x^1 (puede saltarse, por eso vector de exponentes)
		double* newCoef = new double[nter]; // Nuevos Coeficientes
		float* newExp = new float[nter];	// Nuevos Exponentes
		ushort j = 0;	// Contador para estos nuevos arreglos
		for (ushort i = 0; i < nter; i++) {
			//Pasa por cada miembro del polinomio
			//Regla: derivada de c*(x^n) = (c*n)*x^(n-1)
			//Ejem: 5x^3 -> 5*3*x^2
			//...Nuevo coeficiente: c*n
			double newCoefAux = this->exp[i]*this->c[i];
			//...Nuevo exponente: n-1
			float newExpAux = this->exp[i] - 1;
			if (newCoefAux != 0) {
				//Siempre que el nuevo coeficiente sea diferente a 0
				//Evita guardar 0 * x, ya que no es importante
				newCoef[j] = newCoefAux;
				newExp[j] = newExpAux;
				j++;
				//Guarda en la posición j, que siempre es menor a nter original,
				//pero puede sobrar ( por los casos donde coeficiente = 0 )
			}
		}
		if (j == this->nter)
			//Si cuando derivas, la cantidad de miembros es la misma, BIEN
			return new polinomio(j, newCoef, newExp);

		//Para evitar tener un último(s) término(s) que apunta a la basura
		//(Considerando eliminarlo por si se puede usar el espacio original en algo más y evitar cuatro arreglos)
		//(Ya que igual j pasa como nter que determina hasta donde llegar)
		//... Lo que sigue es un simple copiar a los nuevos arreglos donde no sobra espacio en la ram
		double* newC = new double[j];
		float* newE = new float[j];
		for (short i = 0; i < j; i++) {
			newC[i] = newCoef[i];
			newE[i] = newExp[i];
		}
		//Borra los arreglos donde sobra espacio
		delete[] newCoef;
		delete[] newExp;
		//Retorna el polinomio con espacio justo
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

#pragma endregion

#pragma region base para Vectores
vec3 prodVecEsc(vec3* v1, double c) {
	return vec3(v1->x*c, v1->y*c, v1->z*c);
}
vec3 suma(vec3* v1, vec3* v2) {
	return vec3(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}
vec3 resta(vec3* v1, vec3* v2) {
	//OKO REDUNDANCIA PORQUE BASTA suma(v1,v2*-1)
	return vec3(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}
#pragma endregion

#pragma region Apuntes Algebra Lineal para Angulos
double dotSimp(vec3* v1, vec3* v2) {
	//not a simp, pero pos no usa cos xd
	//Algebra Lineal
	return (v1->x*v2->x) + (v1->y*v2->y) + (v1->z*v2->z);
}
double cosTheta(vec3* v1, vec3* v2) {
	//Algebra Lineal: (u.v)/(||u||.||v||)
	return (dotSimp(v1, v2)) / (v1->magnitud()*v2->magnitud());
}
#pragma endregion