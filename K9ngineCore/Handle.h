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

			~HandleElement()
			{
				destroy();
			}

			template<typename... Args>
			void emplace(uint64_t newUId, Args&&... args)
			{
				new (get()) ValueType(std::forward<Args>(args)...);
				uid = newUId,
				occupied = true;
			}

			void destroy()
			{
				if (occupied) {
					get()->~ValueType();
					occupied = false;
				}
			}

			ValueType*				get()				{ return std::launder(reinterpret_cast<ValueType*>(&value)); }
			const ValueType*	get() const	{ return std::launder(reinterpret_cast<const ValueType*>(&value)); }

			// NOTE: When occupied == false, uid stores the index of the next free slot in the HandleTable.
			uint64_t uid{ static_cast<uint64_t>(-1) };
			alignas(ValueType) std::byte value[sizeof(ValueType)];
			bool occupied = false;
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
				return (index < _elements.size() && _elements[index].uid == uid && _elements[index].occupied);
			}

			template<typename... Args>
			size_t createHandle(uint64_t uid, Args&&... args);
			void deleteHandle(size_t index);
			Handle<T,N> getHandle(size_t index);
			const Handle<T, N> getHandle(size_t index) const;

			void clear();
		private:
			T* getElementValue(size_t index) {
				K9ASSERT(index < _elements.size(), "HandleTable::getElementValue, index out of range");
				return _elements[index].get();
			}

			const T* getElementValue(size_t index) const {
				K9ASSERT(index < _elements.size(), "HandleTable::getElementValue, index out of range");
				return _elements[index].get();
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
			return *(const_cast<HandleTable<T, N>*>(_pHandleTable)->getElementValue(_index));
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
			return const_cast<HandleTable<T, N>*>(_pHandleTable)->getElementValue(_index);
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
					_elements[i].uid = static_cast<uint64_t>(i + 1);
					_elements[i].occupied = false;
				}
				_elements[N - 1].uid = InvalidIndex;
			}
			else {
				_elements.reserve(1);
				_elements.emplace_back();
				_elements[0].uid = 1;
				_elements[0].occupied = false;
			}

			_nextFreeElement = 0;
		}

		template<typename T, uint64_t N>
		HandleTable<T, N>::~HandleTable()
		{
			clear();
		}

		template<typename T, uint64_t N>
		template<typename... Args>
		size_t HandleTable<T, N>::createHandle(uint64_t uid, Args&&... args) {
			static_assert(N == 0 || N > 0, "N must be >= 0");

			uint64_t newElementIndex = _nextFreeElement;

			if constexpr(N != 0){
				// Array mode
				K9ASSERT(_nextFreeElement != InvalidIndex && _nextFreeElement < _elements.size(), "HandleTable<T>::createHandle, no more space");
				K9ASSERT(!_elements[_nextFreeElement].occupied, "HandleTable<T>::createHandle, element must be freed before reassigning");

				_nextFreeElement = _elements[newElementIndex].uid;
				_elements[newElementIndex].emplace(uid, std::forward<Args>(args)...);
			}
			else {
				// Vector mode
				//T must be movable if reallocation happens
				static_assert(std::is_move_constructible_v<HandleElement<T>>, "HandleElement<T> must be move-constructible in vector mode");

				K9ASSERT(_nextFreeElement != InvalidIndex, "HandleTable<T>::createHandle, no more space");
				if (_nextFreeElement >= _elements.size()) {
					const size_t oldSize = _elements.size();
					const size_t newCap = oldSize * 2;
					_elements.reserve(newCap);
					for (int i = oldSize; i < newCap; i++) {
						_elements.emplace_back();
						_elements[i].uid = static_cast<uint64_t>(i + 1);
						_elements[i].occupied = false;
					}
				}

				K9ASSERT(!_elements[_nextFreeElement].occupied, "HandleTable<T>::createHandle, element must be freed before reassigning");
				_nextFreeElement = _elements[newElementIndex].uid;

				_elements[newElementIndex].emplace(uid, std::forward<Args>(args)...);
			}

			return static_cast<size_t>(newElementIndex);
		}

		template<typename T, uint64_t N>
		void HandleTable<T, N>::deleteHandle(size_t index) {
			K9ASSERT(index < _elements.size(), "HandleTable<T>::deleteHandle, index out of range");

			HandleElement<T>& element = _elements[index];

			if (!element.occupied) {
				return;
			}

			element.destroy();
			element.uid = _nextFreeElement;
			_nextFreeElement = static_cast<uint64_t>(index);
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
