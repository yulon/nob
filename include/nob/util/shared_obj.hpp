#pragma once

#include <memory>

#define SHARED_OBJ(T) \
		T(nullptr_t) : _m(nullptr) {} \
		\
		T() : _m(std::make_shared<member_table>()) {} \
		\
		T(const member_table &ctx) : _m(std::make_shared<member_table>(ctx)) {} \
		\
		T(const T &src) : _m(src._m) {} \
		\
		T(T &&src) : _m(std::move(src._m)) {} \
		\
		T(const std::shared_ptr<member_table> &m) : _m(m) {} \
		\
		T(std::shared_ptr<member_table> &&m) : _m(std::move(m)) {} \
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
	private: \
		std::shared_ptr<member_table> _m; \
	public:

#include <typeindex>

#define SHARED_OBJ_FOR_POLYMORPHISM(T) \
		const std::type_index type; \
		\
		T(nullptr_t) : type(typeid(nullptr_t)), _m(nullptr) {} \
		\
		T() : type(typeid(T)), _m(std::make_shared<member_table>()) {} \
		\
		T(const member_table &ctx) : type(typeid(T)), _m(std::make_shared<member_table>(ctx)) {} \
		\
		T(const std::type_index &t, const member_table &ctx) : type(t), _m(std::make_shared<member_table>(ctx)) {} \
		\
		T(const T &src) : type(src.type), _m(src._m) {} \
		\
		T(T &&src) : type(src.type), _m(std::move(src._m)) {} \
		\
		T(const std::shared_ptr<member_table> &m) : type(typeid(T)), _m(m) {} \
		\
		T(std::shared_ptr<member_table> &&m) : type(typeid(T)), _m(std::move(m)) {} \
		\
		T(const std::type_index &t, const std::shared_ptr<member_table> &m) : type(t), _m(m) {} \
		\
		T(const std::type_index &t, std::shared_ptr<member_table> &&m) : type(t), _m(std::move(m)) {} \
		\
		const T &operator=(const T &src) { \
			const_cast<std::type_index &>(type) = src.type; \
			_m = src._m; \
			return *this; \
		} \
		\
		const T &operator=(T &&src) { \
			const_cast<std::type_index &>(type) = src.type; \
			_m = std::move(src._m); \
			return *this; \
		} \
		\
		const T &operator=(const std::shared_ptr<member_table> &m) { \
			const_cast<std::type_index &>(type) = typeid(T); \
			_m = m; \
			return *this; \
		} \
		\
		const T &operator=(std::shared_ptr<member_table> &&m) { \
			const_cast<std::type_index &>(type) = typeid(T); \
			_m = std::move(m); \
			return *this; \
		} \
		\
		bool operator==(const T &src) const { \
			return _m.get() == src._m.get(); \
		} \
		\
		bool operator==(const member_table *mp) const { \
			return _m.get() == mp; \
		} \
		\
		bool operator!=(const member_table *mp) const { \
			return _m.get() != mp; \
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
			return D(type, std::static_pointer_cast<typename D::member_table>(_m)); \
		} \
		\
		template<typename D> \
		D to_s() const { \
			return D(type, std::dynamic_pointer_cast<typename D::member_table>(_m)); \
		} \
		\
	private: \
		std::shared_ptr<member_table> _m; \
	public:
