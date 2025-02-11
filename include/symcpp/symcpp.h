#pragma once

#include <numbers>

#include "expression.h"
#include "number.h"
#include "symbol.h"

namespace symcpp {

const Symbol pi("pi", std::numbers::pi);
const Symbol e("e", std::numbers::e);

}  // namespace symcpp
