#pragma once
#include "base.h"
#include <memory>
#include <mutex>

namespace zee {
	enum class thread_safety : uint8 {
		nosafe,
		safe,
	};

	class reference_counter {
	public:
		std::size_t increase() noexcept;
		std::size_t decrease() noexcept;
		std::size_t get() const noexcept { return count; }

	private:
		std::size_t count;
		mutable std::mutex mtx;
	};

	template<typename T>
	class shared_object_base {
	public:
		shared_object_base() : object(nullptr) { }
		~shared_object_base() {
		}

	private:
		T* object;
	};

	template<typename T, thread_safety safety>
	class shared_object;

	template<typename T>
	class shared_object<T, thread_safety::nosafe> {

	};

}//namespace zee 
