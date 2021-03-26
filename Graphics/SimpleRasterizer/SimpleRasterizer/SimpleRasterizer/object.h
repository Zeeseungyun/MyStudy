#pragma once
#include "base.h"
#include <memory>

namespace zee {
	class object;

	class clonable {
	public:
		virtual std::shared_ptr<object> clone() const = 0;
	};

	class object : public std::enable_shared_from_this<object> {
	protected:
		object() : handle(nullptr) {

		}

		virtual ~object() {
			if (handle) {
				//"handle must nullptr at dtor.";
				std::terminate();
			}
		}

		virtual void clear() = 0;

	public:
		handle_t get_handle() const { return handle; }
		explicit operator bool() const { return handle != nullptr; }

	protected:
		handle_t handle;
	};
	
}//namespace zee 
