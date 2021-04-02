#include "memory.h"
namespace zee {
namespace detail {
	std::size_t reference_counter<thread_safety::nosafe>::increase() noexcept {
		return ++count;
	}

	std::size_t reference_counter<thread_safety::nosafe>::decrease() noexcept {
		if (count) {
			--count;
		}
		return count;
	}

	std::size_t reference_counter<thread_safety::safe>::increase() noexcept {
		return ++count;
	}

	std::size_t reference_counter<thread_safety::safe>::decrease() noexcept {
		if (count) {
			--count;
		}
		return count;
	}

	std::size_t reference_counter<thread_safety::safe>::get() const {
		return count;
	}
}//namespace detail 

}//namespace zee 