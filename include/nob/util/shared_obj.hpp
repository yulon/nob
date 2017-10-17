#pragma once

#include <memory>
#include <typeindex>

template <typename T>
class dynamic_shared_obj;

template <typename T>
class shared_obj {
	public:
		shared_obj() {}

		shared_obj(std::shared_ptr<T> &&m) : _m(std::move(m)) {}

		void alloc() {
			_m = std::make_shared<T>();
		}

		bool operator==(const shared_obj<T> &src) const {
			return _m.get() == src._m.get();
		}

		bool operator==(const T *mp) const {
			return _m.get() == mp;
		}

		bool operator!=(const T *mp) const {
			return _m.get() != mp;
		}

		bool operator==(nullptr_t) const {
			return _m.get() == nullptr;
		}

		bool operator!=(nullptr_t) const {
			return _m.get() != nullptr;
		}

		operator bool() const {
			return _m.get();
		}

		T *operator->() {
			return _m.get();
		}

		const T *operator->() const {
			return _m.get();
		}

		T &operator*() {
			return *_m;
		}

		const T &operator*() const {
			return *_m;
		}

		typedef T struct_type;

		typedef shared_obj<T> type;

		template<typename D>
		D cast_with_type() const {
			D dest;
			static_cast<dynamic_shared_obj<typename D::struct_type> &>(dest) = dynamic_shared_obj<typename D::struct_type>(
				typeid(type), std::static_pointer_cast<typename D::struct_type>(_m)
			);
			return dest;
		}

		template<typename D>
		D cast_with_type_s() const {
			D dest;
			static_cast<dynamic_shared_obj<typename D::struct_type> &>(dest) = dynamic_shared_obj<typename D::struct_type>(
				typeid(type), std::dynamic_pointer_cast<typename D::struct_type>(_m)
			);
			return dest;
		}

		template<typename D>
		D cast() const {
			D dest;
			static_cast<shared_obj<typename D::struct_type> &>(dest) = shared_obj<typename D::struct_type>(
				std::static_pointer_cast<typename D::struct_type>(_m)
			);
			return dest;
		}

		template<typename D>
		D cast_s() const {
			D dest;
			static_cast<shared_obj<typename D::struct_type> &>(dest) = shared_obj<typename D::struct_type>(
				std::dynamic_pointer_cast<typename D::struct_type>(_m)
			);
			return dest;
		}

	protected:
		std::shared_ptr<T> _m;
};

template <typename T>
class dynamic_shared_obj : public shared_obj<T> {
	public:
		dynamic_shared_obj() : _t(typeid(typename shared_obj<T>::type)) {}

		dynamic_shared_obj(const std::type_index &t, std::shared_ptr<T> &&m) : shared_obj<T>(std::move(m)), _t(t) {}

		void alloc() {
			_t = typeid(typename shared_obj<T>::type);
			shared_obj<T>::alloc();
		}

		template<typename D>
		bool type_is() {
			return _t == typeid(typename D::type);
		}

		template<typename D>
		D cast_with_type() const {
			D dest;
			static_cast<dynamic_shared_obj<typename D::struct_type> &>(dest) = dynamic_shared_obj<typename D::struct_type>(
				_t, std::static_pointer_cast<typename D::struct_type>(shared_obj<T>::_m)
			);
			return dest;
		}

		template<typename D>
		D cast_with_type_s() const {
			D dest;
			static_cast<dynamic_shared_obj<typename D::struct_type> &>(dest) = dynamic_shared_obj<typename D::struct_type>(
				_t, std::dynamic_pointer_cast<typename D::struct_type>(shared_obj<T>::_m)
			);
			return dest;
		}

	private:
		std::type_index _t;
};
