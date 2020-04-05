#pragma once

#include <rua/log.hpp>

namespace nob {

template <typename... Args>
inline void log(Args &&... args) {
	rua::log(std::forward<Args>(args)...);
}

} // namespace nob
