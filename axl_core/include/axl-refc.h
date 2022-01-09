#include <cstdint>
#include <type_traits>
#include <utility>

namespace axl {

	template<class T>
	struct ref_counted_object {
		void inc() {
			m_obj_count++;
		}
		void dec() {
			m_obj_count--;
			if (m_obj_count == 0) {
				delete m_raw_ptr;
			}
		}

		ref_counted_object(T* ptr = nullptr) : m_raw_ptr(ptr), m_obj_count(0) {
			if (ptr != nullptr) { 
				inc(); 
			}
		}

		ref_counted_object(const ref_counted_object& rco) 
			: m_raw_ptr(rco.m_raw_ptr), m_obj_count(rco.m_obj_count) {
			if(m_raw_ptr != nullptr) {
				inc();
			}
		}

		ref_counted_object(ref_counted_object&& other) noexcept 
			: m_raw_ptr(other.m_raw_ptr),
			  m_obj_count(other.m_obj_count) 
		{
		}

		~ref_counted_object() {
			if(m_raw_ptr != nullptr) {
				dec();
			}
		}

		ref_counted_object& operator=(T* ptr) {
			m_raw_ptr = ptr;
			m_obj_count = 0;
			inc();
			return *this;
		}

		ref_counted_object& operator=(const ref_counted_object& ptr) {
			m_raw_ptr = ptr.m_raw_ptr;
			m_obj_count = ptr.m_obj_count;
			inc();
		}

		T* raw() const {
			return m_raw_ptr;
		}

		T* operator->() const { return m_raw_ptr; }
		T& operator*()  const { return *m_raw_ptr;}
		operator T* ()  const { return m_raw_ptr; }
		operator bool() const { return m_raw_ptr != nullptr; }
		bool operator==(const ref_counted_object& ptr) { return m_raw_ptr == ptr.m_raw_ptr; }
		bool operator==(const T* ptr) { return m_raw_ptr == ptr; }

	private:
		uint32_t m_obj_count = 0;
		T* m_raw_ptr = nullptr;
	};

	template<class T>
	ref_counted_object<T>&& make_refc_objet(T* data) {
		ref_counted_object<T> obj = data;
		obj.inc();
		return std::move(obj);
	}
}