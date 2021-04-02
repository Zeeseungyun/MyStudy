#pragma once
#include "base.h"
#include <memory>
#include <mutex>
#include <atomic>

namespace zee {
	enum class thread_safety : uint8 {
		nosafe,
		safe,
	};

namespace detail {
	template<thread_safety Safety> struct reference_counter;

	template<> class reference_counter<thread_safety::nosafe> {
	public:
		std::size_t increase() noexcept;
		std::size_t decrease() noexcept;
		std::size_t get() const noexcept { return count; }

	private:
		std::size_t count;
	};

	template<> class reference_counter<thread_safety::safe> {
	public:
		std::size_t increase() noexcept;
		std::size_t decrease() noexcept;
		std::size_t get() const;

	private:
		std::atomic_size_t count;
	};
}//namespace detail 

	template<typename T>
	class shared_object_base {
	public:
		shared_object_base() : object(nullptr) { }
		~shared_object_base() { }

	private:
		T object;
	};

	template<typename T, thread_safety Safety = thread_safety::nosafe> class shared_object;

	template<typename T>
	class shared_object<T, thread_safety::nosafe> {

	};

}//namespace zee 
