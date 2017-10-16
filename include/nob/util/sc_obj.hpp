#pragma once

// Shared Context Object

#define SC_OBJ_WITH_DCC(T, default_ctor_code) \
	public: \
		\
		T() : _sc(std::make_shared<context>()) { default_ctor_code } \
		\
		context *operator->() { \
			return _sc.get(); \
		} \
		\
		const context *operator->() const { \
			return _sc.get(); \
		} \
		\
		T(const T &src) : _sc(src._sc) {} \
		\
		T(T &&src) : _sc(std::move(src._sc)) {} \
		\
		const T &operator=(const T &src) { \
			_sc = src._sc; \
			return *this; \
		} \
		\
		const T &operator=(T &&src) { \
			_sc = std::move(src._sc); \
			return *this; \
		} \
		\
		T(nullptr_t) : _sc(nullptr) {} \
		\
		bool operator==(nullptr_t) const { \
			return !_sc; \
		} \
		\
		T(const context &ctx) : _sc(std::make_shared<context>(ctx)) {} \
		\
		context &operator*() { \
			return *_sc; \
		} \
		\
		const context &operator*() const { \
			return *_sc; \
		} \
		\
		T(const std::shared_ptr<context> &ptr) : _sc(ptr) {} \
		\
		T(std::shared_ptr<context> &&ptr) : _sc(std::move(ptr)) {} \
		\
		const T &operator=(const std::shared_ptr<context> &ptr) { \
			_sc = ptr; \
			return *this; \
		} \
		\
		const T &operator=(std::shared_ptr<context> &&ptr) { \
			_sc = std::move(ptr); \
			return *this; \
		} \
		\
	protected: \
		std::shared_ptr<context> _sc; \
		friend const std::shared_ptr<context> &sc_obj::get_shared_context<T>(const T &); \
		friend std::shared_ptr<context> &sc_obj::get_shared_context<T>(T &); \
	public:

#define SC_OBJ(T) SC_OBJ_WITH_DCC(T, )

/////////////////////////////////////////////////////////////////////////

#include <memory>

namespace sc_obj {
	template<typename T>
	inline const std::shared_ptr<typename T::context> &get_shared_context(const T &obj) {
		return obj._sc;
	}

	template<typename T>
	inline std::shared_ptr<typename T::context> &get_shared_context(T &obj) {
		return obj._sc;
	}

	template<typename D, typename S>
	inline D s_cast(const S &src) {
		return std::static_pointer_cast<typename D::context>(get_shared_context(src));
	}

	template<typename D, typename S>
	inline D d_cast(const S &src) {
		return std::dynamic_pointer_cast<typename D::context>(get_shared_context(src));
	}

	template<typename D, typename S>
	inline D c_cast(const S &src) {
		return std::const_pointer_cast<typename D::context>(get_shared_context(src));
	}

	#if __cplusplus > 201402L
		template<typename D, typename S>
		inline D r_cast(const S &src) {
			return std::reinterpret_pointer_cast<typename D::context>(get_shared_context(src));
		}
	#endif
}
