#pragma once

#include "mathp.hpp"

namespace faraday {
	
	double fem(double N, double dF, double dt) {
		return -1 * (N * dF) / dt;
	}
}