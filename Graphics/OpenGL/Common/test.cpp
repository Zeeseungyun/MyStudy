#include <iostream>
#include "common.h"
#include <array>
struct B;
struct A {
	B& ff();
};

struct B : A {

};

B& A::ff()
{
	return static_cast<B&>(*this);
}

struct d : public zee::common_base<d> {
	typedef int value_type;
	static constexpr size_t component_size = 3;
	constexpr d(value_type v0 = 1, value_type v1 = 2, value_type v2 = 0) : data{ v0, v1, v2 } { }
	union {
		value_type data[component_size];
		value_type x, y, z;
	};
};

int main() {
	zee::detail::is_vec_func_base<d>::value;
	zee::detail::is_vec_default_base<d>::value;
	zee::detail::get_value_t<d> f;
	
	constexpr d dd;
	constexpr auto fff = at(dd, 1);

	std::cout << dd.at(0);


	
	B b;
	b.ff();
	

	return 0;
}