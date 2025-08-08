#ifndef HANDLE_H
#define HANDLE_H

#include <array>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "../K9ngineCore/K9Debug.h"

namespace K9ngineCore {
	namespace Memory {
		template<typename T, uint64_t N> class Handle;
		template<typename T, uint64_t N> class HandleTable;

		template<typename T, uint64_t N>
		bool operator<(const Handle<T, N>&, const Handle<T, N>&);

		template<typename T, uint64_t N>
		bool operator==(const Handle<T, N>&, const Handle<T, N>&);

		template<typename T, uint64_t N>
		bool operator!=(const Handle<T, N>&, const Handle<T, N>&);

		template<typename T, uint64_t N = 0>
		class Handle {
			friend class HandleTable<T, N>;
		public:
			typedef T ValueType;

			Handle(const Handle<T, N>&) = default;
			Handle(Handle<T, N>&& other) noexcept:
				_pHandleTable(other._pHandleTable),
				_uid(other._uid),
				_index(other._index)
			{
				other._pHandleTable = nullptr;
			}

			~Handle()
			{
				_pHandleTable = nullptr;
				_uid = static_cast<uint64_t>(-1);
        _index = static_cast<size_t>(-1);
			}

			explicit operator bool() const {
				return isValid();
			}

			T& operator=(const Handle<T, N>& other) {
				if (this != &other) {
					_pHandleTable = other._pHandleTable;
					_uid = other._uid;
					_index = other._index;
				}
				return *this;
			}

			T& operator=(Handle<T, N>&& other) noexcept {
				if (this != &other) {
					_pHandleTable = other._pHandleTable;
					_uid = other._uid;
					_index = other._index;
				}
				return *this;
			}

			T& operator*();
			const T& operator*()const;

			T* operator->();
			const T* operator->() const;

			uint64_t uid() const { return _uid; }

			bool isValid() const;
		private:
			Handle(const HandleTable<T, N>* handleTable, uint64_t uid, size_t index) :
				_pHandleTable(handleTable),
				_uid(uid),
				_index(index) 
			{
			}

			const HandleTable<T, N>* _pHandleTable;
			uint64_t _uid;
			size_t _index;
		};

		template<typename T>
		struct HandleElement {
			typedef T ValueType;

			HandleElement()
			: uid{ static_cast<uint64_t>(-1) }
			,	value{ nullptr }
			{
			}

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
			uint64_t uid{ static_cast<uint64_t>(-1) };
			T* value{ nullptr };
		};

		template<typename T, uint64_t N = 0>
		class HandleTable {
			friend class Handle<T, N>;
		public:
			using ValueType = T;
			using HandleType = Handle<T, N>;
			using ContainerType = std::conditional_t<N == 0, std::vector<HandleElement<T>>, std::array<HandleElement<T>, N>>;

			static const Handle<T, N> NullHandle;

			HandleTable();
			HandleTable(const HandleTable<T, N>&) = delete;
			HandleTable(HandleTable<T, N>&&) noexcept = delete;

			~HandleTable();

			HandleTable<T, N>& operator=(const HandleTable<T, N>&) = delete;
			HandleTable<T, N>& operator=(HandleTable<T, N>&&) noexcept = delete;

			bool isValid(uint64_t uid, size_t index) const {
				//K9ASSERT(index < _elements.size(), "HandleTable::isValid, index out of range");
				return (index < _elements.size() && _elements[index].uid == uid && _elements[index].value != nullptr);
			}

			size_t createHandle(uint64_t uid, T* value);
			void deleteHandle(size_t index);
			Handle<T,N> getHandle(size_t index);
			const Handle<T, N> getHandle(size_t index) const;

			void clear();
		private:
			T* getElementValue(size_t index) {
				K9ASSERT(index < _elements.size(), "HandleTable::getElementValue, index out of range");
				return _elements[index].value;
			}

			T* const getElementValue(size_t index) const {
				K9ASSERT(index < _elements.size(), "HandleTable::getElementValue, index out of range");
				return _elements[index].value;
			}

			ContainerType _elements{};
			uint64_t _nextFreeElement{0};
			static constexpr uint64_t InvalidIndex = (uint64_t)(-1);
		};

		/****************************************/
		/******** FUNCTIONS DEFINITIONS *********/
		/****************************************/
		template<typename T, uint64_t N>
		bool operator<(const Handle<T, N>& lhs, const Handle<T, N>& rhs)
		{
			return lhs.uid() < rhs.uid();
		}

		template<typename T, uint64_t N>
		bool operator==(const Handle<T, N>& lhs, const Handle<T, N>& rhs)
		{
			return lhs.uid() == rhs.uid();
		}

		template<typename T, uint64_t N>
		bool operator!=(const Handle<T, N>& lhs, const Handle<T, N>& rhs)
		{
			return !(lhs == rhs);
		}

		/****************************************/
		/****** HANDLE CLASS DEFINITIONS ********/
		/****************************************/
		
		template<typename T, uint64_t N>
		inline T& Handle<T, N>::operator*() {
			K9ASSERT(isValid(), "Handle<T>::operator*, handle not valid");
			return *(_pHandleTable->getElementValue(_index));
		}

		template<typename T, uint64_t N>
		inline const T& Handle<T, N>::operator*() const
		{
			K9ASSERT(isValid(), "Handle<T>::operator*, handle not valid");
			return *(_pHandleTable->getElementValue(_index));
		}

		template<typename T, uint64_t N>
		inline T* Handle<T, N>::operator->() {
			K9ASSERT(isValid(), "Handle<T>::operator->, handle not valid");
			return _pHandleTable->getElementValue(_index);
		}

		template<typename T, uint64_t N>
		inline const T* Handle<T, N>::operator->() const {
			K9ASSERT(isValid(), "Handle<T>::operator->, handle not valid");
			return _pHandleTable->getElementValue(_index);
		}

		template<typename T, uint64_t N>
		bool Handle<T, N>::isValid() const {
			return _pHandleTable != nullptr && _pHandleTable->isValid(_uid, _index);
		}

		/****************************************/
		/****** HANDLE TABLE DEFINITIONS ********/
		/****************************************/

		template<typename T, uint64_t N>
		const Handle<T, N> HandleTable<T, N>::NullHandle{ nullptr, (uint64_t)-1, (size_t)-1 };

		template<typename T, uint64_t N>
		HandleTable<T, N>::HandleTable() {
			if constexpr (N != 0) {
				for (size_t i = 0; i != N; i++) {
					_elements[i] = HandleElement<T>{ i + 1, nullptr };
				}
				_elements[N - 1].uid = InvalidIndex;
			}
			else {
				_elements.reserve(1);
				_elements.emplace_back(1, nullptr);
			}

			_nextFreeElement = 0;
		}

		template<typename T, uint64_t N>
		HandleTable<T, N>::~HandleTable()
		{
			clear();
		}

		template<typename T, uint64_t N>
		size_t HandleTable<T, N>::createHandle(uint64_t uid, T* value) {
			uint64_t newElementIndex = _nextFreeElement;

			if constexpr(N != 0){
				K9ASSERT(_nextFreeElement != InvalidIndex && _nextFreeElement < _elements.size(), "HandleTable<T>::createHandle, no more space");
				K9ASSERT(_elements[_nextFreeElement].value == nullptr, "HandleTable<T>::createHandle, element must be freed before reassigning");

				_nextFreeElement = _elements[newElementIndex].uid;

				_elements[newElementIndex].uid = uid;
				_elements[newElementIndex].value = value;
			}
			else {
				K9ASSERT(_nextFreeElement != InvalidIndex, "HandleTable<T>::createHandle, no more space");
				if (_nextFreeElement < _elements.size()) {
					K9ASSERT(_elements[_nextFreeElement].value == nullptr, "HandleTable<T>::createHandle, element must be freed before reassigning");
				}
				else {
					_elements.reserve(_elements.size() * 2);
					for (int i = _nextFreeElement; i != _elements.capacity(); i++) {
						_elements.emplace_back(i + 1, nullptr);
					}
				}

				_nextFreeElement = _elements[newElementIndex].uid;

				_elements[newElementIndex].uid = uid;
				_elements[newElementIndex].value = value;
			}

			return newElementIndex;
		}

		template<typename T, uint64_t N>
		void HandleTable<T, N>::deleteHandle(size_t index) {
			K9ASSERT(index < _elements.size(), "HandleTable<T>::deleteHandle, index out of range");

			HandleElement<T>& element = _elements[index];

			if (element.value == nullptr) {
				return;
			}

			delete element.value;
			element.value = nullptr;
			element.uid = _nextFreeElement;
			_nextFreeElement = index;
		}

		template<typename T, uint64_t N>
		Handle<T, N> HandleTable<T, N>::getHandle(size_t index) {
			K9ASSERT(index < _elements.size(), "HandleTable<T>::getHandle, index out of range");
			return Handle<T, N>{this, _elements[index].uid, index};
		}

		template<typename T, uint64_t N>
		const Handle<T, N> HandleTable<T, N>::getHandle(size_t index) const {
			K9ASSERT(index < _elements.size(), "HandleTable<T>::getHandle, index out of range");
			return Handle<T, N>{this, _elements[index].uid, index};
		}

		template<typename T, uint64_t N>
		void HandleTable<T, N>::clear()
		{
			for (size_t i = 0; i < _elements.size(); i++) {
				deleteHandle(i);
			}

			if constexpr (N == 0) {
				_elements.clear();
				_elements.shrink_to_fit();
			}
		}
	}
}

#endif // !HANDLE_H
