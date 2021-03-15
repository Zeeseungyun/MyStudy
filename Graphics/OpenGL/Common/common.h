#pragma once
#include <iostream>
#include <cmath>
#include <type_traits>
#include <vector>
#include <string>

namespace zee {
	typedef size_t offset_t;

	template<typename T> struct common_base;
	template<typename T> struct vec_default_base;

namespace detail {
	template<typename T> struct is_vec_func_base {
	private:
		template<typename T> static constexpr bool func(common_base<T> v) { return true; }
		static constexpr bool func(...) { return false; }

	public:
		static constexpr bool value = func(T());
	};

	template<typename T> struct is_vec_default_base {
	private:
		template<typename T> static constexpr bool func(vec_default_base<T> v) { return true; }
		static constexpr bool func(...) { return false; }

	public:
		static constexpr bool value = func(T());
	};

	template<typename T> struct get_value_type {
	private:
		template<typename U> static constexpr typename U::value_type func(U vv, typename U::value_type v = typename U::value_type());
		template<typename T> static constexpr int func(...);

	public:
		typedef decltype(func(T())) type;
	};

	template<typename T> using get_value_t = typename get_value_type<T>::type;
	template<typename T> constexpr bool is_vec_func_base_v = is_vec_func_base<T>::value;
	template<typename T> constexpr bool is_vec_default_base_v = is_vec_default_base<T>::value;

}//namespace detail 

	template<typename T> constexpr size_t component_size(const common_base<T>& v) { return T::component_size; }
	template<typename T> constexpr size_t scalar_size(const common_base<T>& v) { return sizeof(typename T::value_type); }


	template<typename T> constexpr auto at(const common_base<T>& va, size_t idx);
	template<typename T> constexpr auto at(common_base<T>& va, size_t idx);

	template<typename T>
	struct common_base {
	public:
		constexpr T& cast() { return static_cast<T&>(*this); }
		constexpr const T& cast() const { return static_cast<const T&>(*this); }
		constexpr auto at(size_t idx) const { return zee::at(*this, idx); }
		constexpr auto at(size_t idx) { return zee::at(*this, idx); }
		
	};

	template<typename T> constexpr auto cast(const common_base<T>& va) { return static_cast<const T&>(va); }
	template<typename T> constexpr auto cast(common_base<T>& va) { return static_cast<T&>(va); }
	template<typename T> constexpr auto at(const common_base<T>& va, size_t idx) { return cast(va).data[idx]; }
	template<typename T> constexpr auto at(common_base<T>& va, size_t idx) { return cast(va).data[idx]; }

	template<typename T>
	struct vec_default_base : public common_base<T> {
	public:

	};

}