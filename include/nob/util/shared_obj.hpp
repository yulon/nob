#pragma once

#include <memory>
#include <typeindex>
#include <type_traits>

template <typename S>
class dynamic_shared_obj;

template <typename S>
class shared_obj {
	protected:
		constexpr shared_obj() {}

	public:
		template<typename... A>
		void alloc(A&&... a) {
			_m = std::make_shared<S>(std::forward<A>(a)...);
		}

		void free() {
			_m.reset();
		}

		size_t ref_count() {
			return _m.use_count();
		}

		bool operator==(const shared_obj<S> &src) const {
			return _m.get() == src._m.get();
		}

		bool operator==(const S *mp) const {
			return _m.get() == mp;
		}

		bool operator!=(const S *mp) const {
			return _m.get() != mp;
		}

		bool operator==(std::nullptr_t) const {
			return _m.get() == nullptr;
		}

		bool operator!=(std::nullptr_t) const {
			return _m.get() != nullptr;
		}

		operator bool() const {
			return _m.get();
		}

		S *operator->() {
			return _m.get();
		}

		const S *operator->() const {
			return _m.get();
		}

		S &operator*() {
			return *_m;
		}

		const S &operator*() const {
			return *_m;
		}

		typedef S structure;

		template<typename D>
		D cast_with_type() const {
			static_assert(std::is_base_of<dynamic_shared_obj<typename D::structure>, D>::value, "dest is not a 'dynamic_shared_obj'");

			D dest;
			static_cast<dynamic_shared_obj<typename D::structure> &>(dest) = typeid(structure);
			static_cast<shared_obj<typename D::structure> &>(dest) = std::static_pointer_cast<typename D::structure>(_m);
			return dest;
		}

		template<typename D>
		D cast_with_type_s() const {
			static_assert(std::is_base_of<dynamic_shared_obj<typename D::structure>, D>::value, "dest is not a 'dynamic_shared_obj'");

			D dest;
			static_cast<dynamic_shared_obj<typename D::structure> &>(dest) = typeid(structure);
			static_cast<shared_obj<typename D::structure> &>(dest) = std::dynamic_pointer_cast<typename D::structure>(_m);
			return dest;
		}

		void operator=(std::shared_ptr<S> &&m) {
			_m = std::move(m);
		}

		template<typename D>
		D cast() const {
			static_assert(std::is_base_of<shared_obj<typename D::structure>, D>::value, "dest is not a 'shared_obj'");
			static_assert(!std::is_base_of<dynamic_shared_obj<typename D::structure>, D>::value, "dest cannot be a 'dynamic_shared_obj'");

			D dest;
			static_cast<shared_obj<typename D::structure> &>(dest) = std::static_pointer_cast<typename D::structure>(_m);
			return dest;
		}

		template<typename D>
		D cast_s() const {
			static_assert(std::is_base_of<shared_obj<typename D::structure>, D>::value, "dest is not a 'shared_obj'");
			static_assert(!std::is_base_of<dynamic_shared_obj<typename D::structure>, D>::value, "dest cannot be a 'dynamic_shared_obj'");

			D dest;
			static_cast<shared_obj<typename D::structure> &>(dest) = std::dynamic_pointer_cast<typename D::structure>(_m);
			return dest;
		}

	protected:
		std::shared_ptr<S> _m;
};

template <typename S>
class dynamic_shared_obj : public shared_obj<S> {
	protected:
		constexpr dynamic_shared_obj() : _t(typeid(nullptr)) {}

	public:
		template<typename... A>
		void alloc(A&&... a) {
			_t = typeid(typename shared_obj<S>::structure);
			shared_obj<S>::alloc(std::forward<A>(a)...);
		}

		void free() {
			_t = typeid(nullptr);
			shared_obj<S>::free();
		}

		template<typename D>
		bool type_is() {
			static_assert(std::is_base_of<shared_obj<typename D::structure>, D>::value, "target is not a 'shared_obj'");

			return _t == typeid(typename D::structure);
		}

		void operator=(std::type_index t) {
			_t = t;
		}

		template<typename D>
		D cast_with_type() const {
			static_assert(std::is_base_of<dynamic_shared_obj<typename D::structure>, D>::value, "dest is not a 'dynamic_shared_obj'");

			D dest;
			static_cast<dynamic_shared_obj<typename D::structure> &>(dest) = _t;
			static_cast<shared_obj<typename D::structure> &>(dest) = std::static_pointer_cast<typename D::structure>(shared_obj<S>::_m);
			return dest;
		}

		template<typename D>
		D cast_with_type_s() const {
			static_assert(std::is_base_of<dynamic_shared_obj<typename D::structure>, D>::value, "dest is not a 'dynamic_shared_obj'");

			D dest;
			static_cast<dynamic_shared_obj<typename D::structure> &>(dest) = _t;
			static_cast<shared_obj<typename D::structure> &>(dest) = std::dynamic_pointer_cast<typename D::structure>(shared_obj<S>::_m);
			return dest;
		}

	private:
		std::type_index _t;
};
