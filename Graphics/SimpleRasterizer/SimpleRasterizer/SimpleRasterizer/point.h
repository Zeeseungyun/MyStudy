#pragma once
#include "base.h"

namespace zee {
	struct ipoint_t {
		union {
			int32 x, y;
			int32 data[2];
		};

		constexpr ipoint_t(int32 new_x = 0, int32 new_y = 0) : data{new_x, new_y} { }
	};

} //namespace zee 
