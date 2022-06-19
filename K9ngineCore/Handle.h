#ifndef HANDLE_H
#define HANDLE_H

#include <cstdint>
#include <vector>

#include "K9Debug.h"

namespace K9ngineCore {
	namespace Memory {
		template<typename T> class Handle;
		template<typename T> class HandleTable;

		template<typename T>
		bool operator<(const Handle<T>&, const Handle<T>&);

		template<typename T>
		class Handle {
			friend class HandleTable<T>;
		public:
			typedef T ValueType;

			Handle(const Handle<T>&) = default;
			Handle(Handle<T>&& other) noexcept:
				_pHandleTable(other._pHandleTable),
				_uid(other._uid),
				_index(other._index)
			{
				other._pHandleTable = nullptr;
			}

			T& operator=(const Handle<T>& other) {
				if (this != &other) {
					_pHandleTable = other._pHandleTable;
					_uid = other._uid;
					_index = other._index;
				}
				return *this;
			}

			T& operator=(Handle<T>&& other) noexcept {
				if (this != &other) {
					_pHandleTable = other._pHandleTable;
					_uid = other._uid;
					_index = other._index;
				}
				return *this;
			}

			T& operator*();
			T* operator->();

			uint64_t uid() const { return _uid; }

			bool isValid() const;
		private:
			Handle(HandleTable<T>* handleTable, uint64_t uid, size_t index) :
				_pHandleTable(handleTable),
				_uid(uid),
				_index(index) 
			{
			}

			HandleTable<T>* _pHandleTable;
			uint64_t _uid;
			size_t _index;
		};

		template<typename T>
		struct HandleElement {
			typedef T ValueType;

			HandleElement(uint64_t newUId, T* newValue):
				uid(newUId),
				value(newValue)
			{
			}

			~HandleElement() {
				if (value) {
					delete value;
				}
				value = nullptr;
			}

			/* NOTE: if value is null, uid will be the index to the next free element in the HandleTable */
			uint64_t uid;
			T* value;
		};

		template<typename T>
		class HandleTable {
			friend class Handle<T>;
		public:
			typedef T ValueType;

			HandleTable(size_t size);
			HandleTable(const HandleTable<T>&) = delete;
			HandleTable(HandleTable<T>&&) noexcept = delete;

			HandleTable& operator=(const HandleTable<T>&) = delete;
			HandleTable& operator=(HandleTable<T>&&) noexcept = delete;

			bool isValid(uint64_t uid, size_t index) const {
				K9ASSERT(index < _elements.size());
				return (_elements[index].uid == uid && _elements[index].value != nullptr);
			}

			size_t createHandle(uint64_t uid, T* value);
			void deleteHandle(size_t index);
			Handle<T> getHandle(size_t index);
		private:
			T* getElementValue(size_t index) {
				K9ASSERT(index < _elements.size());
				return _elements[index].value;
			}

			std::vector<HandleElement<T>> _elements;
			uint64_t _nextFreeElement;
			static constexpr uint64_t InvalidIndex = (uint64_t)(-1);
		};

		/****************************************/
		/******** FUNCTIONS DEFINITIONS *********/
		/****************************************/
		template<typename T>
		bool operator<(const Handle<T>& lhs, const Handle<T>& rhs) {
			return lhs.uid() < rhs.uid();
		}

		/****************************************/
		/****** HANDLE CLASS DEFINITIONS ********/
		/****************************************/
		
		template<typename T>
		inline T& Handle<T>::operator*() {
			K9ASSERT(isValid());
			return *(_pHandleTable->getElementValue(_index));
		}

		template<typename T>
		inline T* Handle<T>::operator->() {
			K9ASSERT(isValid());
			return _pHandleTable->getElementValue(_index);
		}

		template<typename T>
		bool Handle<T>::isValid() const {
			K9ASSERT(_pHandleTable != nullptr);
			return _pHandleTable->isValid(_uid, _index);
		}

		/****************************************/
		/****** HANDLE TABLE DEFINITIONS ********/
		/****************************************/

		template<typename T>
		HandleTable<T>::HandleTable(size_t size) {
			_elements.reserve(size);
			for (size_t i = 0; i != size; i++) {
				_elements.emplace_back( i + 1, nullptr );
			}
			_elements[size - 1].uid = InvalidIndex;
			_nextFreeElement = 0;
		}

		template<typename T>
		size_t HandleTable<T>::createHandle(uint64_t uid, T* value) {
			K9ASSERT(_nextFreeElement != InvalidIndex && _nextFreeElement < _elements.size());
			K9ASSERT(_elements[_nextFreeElement].value == nullptr);

			uint64_t newElementIndex = _nextFreeElement;

			_nextFreeElement = _elements[newElementIndex].uid;

			_elements[newElementIndex].uid = uid;
			_elements[newElementIndex].value = value;

			return newElementIndex;
		}

		template<typename T>
		void HandleTable<T>::deleteHandle(size_t index) {
			K9ASSERT(index < _elements.size());

			HandleElement<T>& element = _elements[index];

			if (element.value == nullptr) {
				return;
			}

			delete element.value;
			element.value = nullptr;
			element.uid = _nextFreeElement;
			_nextFreeElement = index;
		}

		template<typename T>
		Handle<T> HandleTable<T>::getHandle(size_t index) {
			K9ASSERT(index < _elements.size());
			Handle<T> handle(this, _elements[index].uid, index);
			return handle;
		}
	}
}

#endif // !HANDLE_H
