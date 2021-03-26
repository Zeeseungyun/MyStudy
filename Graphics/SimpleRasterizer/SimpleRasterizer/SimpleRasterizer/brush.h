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

	class bitmap;
	class brush : public object, public clonable {
		friend void swap(brush& l, brush& r) noexcept;
		friend std::shared_ptr<brush> create_solid_brush(color_t color) noexcept;
		friend std::shared_ptr<brush> create_pattern_brush(bitmap color);

	public:
		brush() = default;
		brush(brush&& other) noexcept;
		brush(const brush& other);
		brush& operator=(brush&& other) noexcept;
		brush& operator=(const brush& other);

		virtual void clear() override final;
		~brush();

	private:
		brush_type type = brush_type::none;
	};

}//namespace zee 

