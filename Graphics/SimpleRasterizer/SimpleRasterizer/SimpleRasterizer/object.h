#pragma once
#include "base.h"

namespace zee {
	class object {
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
