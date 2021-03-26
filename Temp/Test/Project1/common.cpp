#include <iostream>
#include <memory>
#include <functional>

template<size_t StrIdx, size_t SourceSize>
struct name_buffer : private name_buffer<StrIdx - 1, SourceSize> {
private:
	typedef name_buffer<StrIdx - 1, SourceSize> parent_type;
	typedef const char(&Arr)[SourceSize];
	typedef const char(*ArrPtr)[SourceSize];
	enum { str_idx = StrIdx };

public:
	constexpr name_buffer(const char(&Str)[SourceSize])
		: parent_type(Str), c(Str[StrIdx]) {
	}

	constexpr char at(size_t idx) const {
		if (str_idx == idx) {
			return c;
		}

		return parent_type::at(idx);
	}

	constexpr char operator[](size_t idx) const { return at(idx); }
	constexpr size_t size() const { return SourceSize; }

private:
	char c;
};

template<size_t SourceSize>
struct name_buffer<0, SourceSize> {
private:
	enum { str_idx = 0 };

protected:
	constexpr name_buffer(const char(&Str)[SourceSize])
		: c(Str[0]) {
	}

public:
	constexpr char operator[](size_t idx) const { return at(idx); }

	constexpr char at(size_t idx) const {
		if (str_idx == idx) {
			return c;
		}
		return 0;
	}

private:
	char c;
};

struct simple_str {
	const char* ptr;
	size_t size;
	template<size_t StrSize>
	constexpr simple_str(const char(&Str)[StrSize])
		: ptr(Str), size(StrSize - 1) {
	}
	constexpr char operator[](size_t idx) const { return ptr[idx]; }
};

template<typename SimpleStrT>
struct make_vector_base {

};

template<size_t SourceSize>
constexpr name_buffer<SourceSize - 1, SourceSize> create_name_buffer(const char(&Str)[SourceSize]) {
	return name_buffer<SourceSize - 1, SourceSize>(Str);
}

constexpr char vv2 = simple_str("asdf")[0];

constexpr char vv = create_name_buffer("asdf")[0];
const char df[] = "asdf";

namespace Test {
	template<typename ...T>
	struct Temp {
	};

	struct X {

	};
}

template<typename ...T>
int myprintf(const char* format, T... _Val)
{
	::printf(format, sizeof... (_Val), _Val...);
	return sizeof... (_Val);
}

#include <vector>
class A 
{
public:
	int value;
	const char* str;

	auto func() {
		std::cout << " bound " << (std::size_t)this;
		return [this]() {
			this->execute();
		};
	}

	void execute() {
		std::cout << " executed. " << (std::size_t)this;
		std::cout << " value: " << value << ", str:" << str;
		std::cout << std::endl;
	}

	~A() {
		std::cout << "dtor\n";
	}
};

class UTest
{

public:
	A temp;
};

auto funcdd() {
	A temp;
	temp.value = 20;
	temp.str = "hi";
	return temp.func();
}

int main() {
	std::function<void()> deletate;
	{
		A* temp = new A();
		temp->value = 20;
		temp->str = "hi";
		deletate = temp->func();
	}
	{
		int aa;
		deletate();
	}
	return 0;
}

