#pragma once

#include <memory>

#define SHARED_OBJ_WITH_DCC(T, default_ctor_code) \
		constexpr T(nullptr_t) : _m(nullptr) {} \
		\
		T() : _m(std::make_shared<member_table>()) { default_ctor_code } \
		\
		T(const member_table &ctx) : _m(std::make_shared<member_table>(ctx)) {} \
		\
		T(const T &src) : _m(src._m) {} \
		\
		T(T &&src) : _m(std::move(src._m)) {} \
		\
		T(const std::shared_ptr<member_table> &ptr) : _m(ptr) {} \
		\
		T(std::shared_ptr<member_table> &&ptr) : _m(std::move(ptr)) {} \
		\
		const T &operator=(const T &src) { \
			_m = src._m; \
			return *this; \
		} \
		\
		const T &operator=(T &&src) { \
			_m = std::move(src._m); \
			return *this; \
		} \
		\
		const T &operator=(const std::shared_ptr<member_table> &m) { \
			_m = m; \
			return *this; \
		} \
		\
		const T &operator=(std::shared_ptr<member_table> &&m) { \
			_m = std::move(m); \
			return *this; \
		} \
		\
		bool operator==(const T &src) const { \
			return _m.get() == src._m.get(); \
		} \
		\
		bool operator==(const member_table *p) const { \
			return _m.get() == p; \
		} \
		\
		bool operator!=(const member_table *p) const { \
			return _m.get() != p; \
		} \
		\
		bool operator==(nullptr_t) const { \
			return _m.get() == nullptr; \
		} \
		\
		bool operator!=(nullptr_t) const { \
			return _m.get() != nullptr; \
		} \
		\
		operator bool() const { \
			return _m.get(); \
		} \
		\
		member_table *operator->() { \
			return _m.get(); \
		} \
		\
		const member_table *operator->() const { \
			return _m.get(); \
		} \
		\
		member_table &operator*() { \
			return *_m; \
		} \
		\
		const member_table &operator*() const { \
			return *_m; \
		} \
		\
		template<typename D> \
		D to() const { \
			return std::static_pointer_cast<typename D::member_table>(_m); \
		} \
		\
		template<typename D> \
		D to_s() const { \
			return std::dynamic_pointer_cast<typename D::member_table>(_m); \
		} \
		\
	private: \
		std::shared_ptr<member_table> _m; \
	public:

#define SHARED_OBJ(T) SHARED_OBJ_WITH_DCC(T, )
