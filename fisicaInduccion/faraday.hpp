#pragma once
#include "mathp.hpp"

namespace faraday {
	double fem(double N, double dF, double dt) {
		return -1 * (N * dF) / dt;
	}
	polinomio flujo(polinomio* B, double A, float theta) {
		//A*B*cos(theta)
		double m = A * cos(theta);
		return multiplicacion(B, m);
	}
}