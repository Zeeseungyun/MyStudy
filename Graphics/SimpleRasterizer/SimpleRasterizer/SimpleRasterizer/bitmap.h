#pragma once
#include "object.h"
namespace zee {
	class bitmap : public object {
	public:
		virtual void clear() override final;
	};
}//namespace zee 

