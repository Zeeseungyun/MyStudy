#pragma once
#include "base.h"
#include "object.h"

namespace zee {
	enum class brush_type : uint8 {
		none,
		solid,
		hatch,
		count,
	};

	class brush : public object {
		friend void swap(brush& l, brush& r);
		friend brush create_solid_brush(color_t color);
		friend brush create_solid_brush(color_t color);
	public:
		brush() = default;
		brush(brush&& other) noexcept;
		brush(const brush& other);
		brush& operator=(brush&& other) noexcept;
		brush& operator=(const brush& other);

		void clear() final;
		~brush();

	private:
		brush_type type = brush_type::none;
	};
}//namespace zee 

