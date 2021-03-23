#pragma once
#include "base.h"
#include <Windows.h>

bool is_valid_rect(const RECT& rc);
zee::uint32 rect_width(const RECT& rc);
zee::uint32 rect_height(const RECT& rc);
RECT make_rect(zee::uint32 width, zee::uint32 height);