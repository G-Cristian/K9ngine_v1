#ifndef HANDLE_H
#define HANDLE_H

#include <array>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "../K9ngineCore/K9Debug.h"

namespace K9ngineCore {
	namespace Memory {
		template<typename Table> class basic_handle;
		template<typename T, uint64_t N> class HandleTable;

		template<typename Table>
		bool operator<(const basic_handle<Table>&, const basic_handle<Table>&);

		template<typename Table>
		bool operator==(const basic_handle<Table>&, const basic_handle<Table>&);

		template<typename Table>
		bool operator!=(const basic_handle<Table>&, const basic_handle<Table>&);

		// Core handle that works with either HandleTable<T,N> or const HandleTable<T,N>
		template<typename Table>
		class basic_handle {
			friend Table;
			// Make the *non-const* and *const* twin specializations friends:
			friend class basic_handle<std::remove_const_t<Table>>;
			friend class basic_handle<std::add_const_t<std::remove_const_t<Table>>>;
		public:
			using table_type = Table;
			using table_ptr = table_type*;
			using element_type_nc = typename std::remove_const_t<table_type>::element_type;
			using is_const_table = std::bool_constant<std::is_const_v<Table>>;
			using element_ref = std::conditional_t<is_const_table::value, const element_type_nc&, element_type_nc&>;
			using element_ptr = std::conditional_t<is_const_table::value, const element_type_nc*, element_type_nc*>;

			// Default-constructed = null/invalid
			constexpr basic_handle() noexcept = default;
			basic_handle(const basic_handle&) noexcept = default;
			basic_handle(basic_handle&&) noexcept = default;

			// Factory for explicit null
			static constexpr basic_handle null() noexcept { return {}; }

			~basic_handle()
			{
				mHandleTable = nullptr;
				mUid = static_cast<uint64_t>(-1);
        mIndex = static_cast<size_t>(-1);
			}

			basic_handle& operator=(const basic_handle&) noexcept = default;
			basic_handle& operator=(basic_handle&&) noexcept = default;

			// Implicit convert non-const handle -> const handle
			template<class T2 = Table, std::enable_if_t<!std::is_const_v<T2>, int> = 0>
			operator basic_handle<std::add_const_t<std::remove_reference_t<T2>>>() const {
				return {mHandleTable, mUid, mIndex };
			}

			explicit constexpr operator bool() const noexcept {
				return isValid();
			}

			element_ref  operator*() const;
			element_ptr operator->() const;

			uint64_t uid() const { return mUid; }

			bool isValid() const;
		private:
			basic_handle(table_ptr handleTable, uint64_t uid, size_t index) :
				mHandleTable(handleTable),
				mUid(uid),
				mIndex(index) 
			{
			}

			table_ptr mHandleTable = nullptr;
			uint64_t mUid = static_cast<uint64_t>(-1);;
			size_t mIndex = static_cast<size_t>(-1);
		};

		template<typename T, uint64_t N = 0>
		using Handle = basic_handle<HandleTable<T, N>>;

		template<typename T, uint64_t N = 0>
		using ConstHandle = basic_handle<const HandleTable<T, N>>;

		template<typename T>
		struct HandleElement {
			using element_type = T;
			using element_ptr = element_type*;

			static_assert(std::is_nothrow_move_constructible_v<element_type>,
				"HandleElement<T>: T move ctor must be noexcept");

      HandleElement() = default;

			HandleElement(HandleElement<T>&& other) noexcept(std::is_nothrow_move_constructible_v<element_type>)
				:	uid{ other.uid }
        , occupied{ other.occupied }
			{
				static_assert(std::is_move_constructible_v<element_type>
										, "HandleElement<T>: T must be move-constructible");
				// Optional: also require move-assignable
				// static_assert(std::is_move_assignable_v<element_type>
				//             , "HandleElement<T>: T must be move-assignable");

				if (other.occupied) {
					new (get()) element_type(std::move(*other.get()));
					uid = other.uid;
					occupied = true;
					other.destroy();
					other.uid = static_cast<uint64_t>(-1);
				}
      }

			~HandleElement()
			{
				destroy();
			}

			HandleElement<T>& operator=(HandleElement<T>&& other) noexcept(std::is_nothrow_move_constructible_v<element_type>)
			{
				if (this != &other) {
					destroy();
					uid = other.uid;
					occupied = other.occupied;
					if (other.occupied) {
						new (get()) element_type(std::move(*other.get()));
						other.destroy();
						other.uid = static_cast<uint64_t>(-1);
					}
				}

				return *this;
      }

			template<typename... Args>
			void emplace(uint64_t newUId, Args&&... args)
			{
				new (get()) element_type(std::forward<Args>(args)...);
				uid = newUId,
				occupied = true;
			}

			void destroy()
			{
				if (occupied) {
					get()->~element_type();
					occupied = false;
				}
			}

			element_ptr				get()				{ return std::launder(reinterpret_cast<element_ptr>(&value)); }
			const element_type*	get() const	{ return std::launder(reinterpret_cast<const element_type*>(&value)); }

		private:
      HandleElement(const HandleElement<T>&) = delete;
      HandleElement<T>& operator=(const HandleElement<T>&) = delete;
		public:

			// NOTE: When occupied == false, uid stores the index of the next free slot in the HandleTable.
			uint64_t uid{ static_cast<uint64_t>(-1) };
			alignas(element_type) std::byte value[sizeof(element_type)];
			bool occupied = false;
		};

		template<typename T, uint64_t N = 0>
		class HandleTable {
			friend basic_handle<HandleTable<T, N>>;
			friend basic_handle<const HandleTable<T, N>>;
		public:
			using element_type = T;
			using element_ptr = element_type*;
			using handle_type = Handle<element_type, N>;
			using const_handle_type = ConstHandle<element_type, N>;
			using container_type = std::conditional_t<N == 0, std::vector<HandleElement<element_type>>, std::array<HandleElement<element_type>, N>>;

			static const handle_type NullHandle;
			static const const_handle_type ConstNullHandle;

			HandleTable();
			HandleTable(const HandleTable<element_type, N>&) = delete;
			HandleTable(HandleTable<element_type, N>&&) noexcept = delete;

			~HandleTable();

			HandleTable<T, N>& operator=(const HandleTable<element_type, N>&) = delete;
			HandleTable<T, N>& operator=(HandleTable<element_type, N>&&) noexcept = delete;

			bool isValid(uint64_t uid, size_t index) const {
				//K9ASSERT(index < _elements.size(), "HandleTable::isValid, index out of range");
				return (index < _elements.size() && _elements[index].uid == uid && _elements[index].occupied);
			}

			template<typename... Args>
			size_t createHandle(uint64_t uid, Args&&... args);
			void deleteHandle(size_t index);
			Handle<T,N> getHandle(size_t index);
			ConstHandle<T,N> getHandle(size_t index) const;

			Handle<T, N> findHandle(uint64_t uid);
			ConstHandle<T, N> findHandle(uint64_t uid) const;

			void clear();
		private:
			element_ptr getElementValue(size_t index) {
				K9ASSERT(index < _elements.size(), "HandleTable::getElementValue, index out of range");
				return _elements[index].get();
			}

			const element_type* getElementValue(size_t index) const {
				K9ASSERT(index < _elements.size(), "HandleTable::getElementValue, index out of range");
				return _elements[index].get();
			}

			container_type _elements{};
			uint64_t _nextFreeElement{0};
			static constexpr uint64_t InvalidIndex = (uint64_t)(-1);
		};

		/****************************************/
		/******** FUNCTIONS DEFINITIONS *********/
		/****************************************/
		template<typename Table>
		bool operator<(const basic_handle<Table>& lhs, const basic_handle<Table>& rhs)
		{
			return lhs.uid() < rhs.uid();
		}

		template<typename Table>
		bool operator==(const basic_handle<Table>& lhs, const basic_handle<Table>& rhs)
		{
			return lhs.uid() == rhs.uid();
		}

		template<typename Table>
		bool operator!=(const basic_handle<Table>& lhs, const basic_handle<Table>& rhs)
		{
			return !(lhs == rhs);
		}

		/****************************************/
		/****** HANDLE CLASS DEFINITIONS ********/
		/****************************************/

		template<typename Table>
		inline typename basic_handle<Table>::element_ref basic_handle<Table>::operator*() const
		{
			K9ASSERT(isValid(), "basic_handle<Table>::operator*, handle not valid");
			return *(mHandleTable->getElementValue(mIndex));
		}

		template<typename Table>
		inline typename basic_handle<Table>::element_ptr basic_handle<Table>::operator->() const {
			K9ASSERT(isValid(), "basic_handle<Table>::operator->, handle not valid");
			return mHandleTable->getElementValue(mIndex);
		}

		template<typename Table>
		bool basic_handle<Table>::isValid() const {
			return mHandleTable != nullptr && mHandleTable->isValid(mUid, mIndex);
		}

		/****************************************/
		/****** HANDLE TABLE DEFINITIONS ********/
		/****************************************/

		template<typename T, uint64_t N>
		const Handle<T, N> HandleTable<T, N>::NullHandle{};

		template<typename T, uint64_t N>
		const ConstHandle<T, N> HandleTable<T, N>::ConstNullHandle{};

		template<typename T, uint64_t N>
		HandleTable<T, N>::HandleTable() {
			static_assert(std::is_move_constructible_v<HandleElement<T>>
									, "HandleTable<T,N>: HandleElement<T> must be move-constructible ");

			static_assert(std::is_nothrow_move_constructible_v<HandleElement<T>>
									, "HandleTable<T,N>: HandleElement<T> move ctor must be noexcept");

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
		Handle<T,N> HandleTable<T, N>::getHandle(size_t index) {
			K9ASSERT(index < _elements.size(), "HandleTable<T>::getHandle, index out of range");
			return Handle<T, N>{this, _elements[index].uid, index};
		}

		template<typename T, uint64_t N>
		ConstHandle<T, N> HandleTable<T, N>::getHandle(size_t index) const {
			K9ASSERT(index < _elements.size(), "HandleTable<T>::getHandle, index out of range");
			return ConstHandle<T, N>{this, _elements[index].uid, index};
		}

		template<typename T, uint64_t N>
		Handle<T, N> HandleTable<T, N>::findHandle(uint64_t uid)
		{
			for (size_t i = 0; i < _elements.size(); i++) {
				if (_elements[i].occupied && _elements[i].uid == uid) {
					return Handle<T, N>{this, uid, i};
				}
			}

			return NullHandle;
		}

		template<typename T, uint64_t N>
		ConstHandle<T, N> HandleTable<T, N>::findHandle(uint64_t uid) const
		{
			for (size_t i = 0; i < _elements.size(); i++) {
				if (_elements[i].occupied && _elements[i].uid == uid) {
					return ConstHandle<T, N>{this, uid, i};
				}
			}

			return ConstNullHandle;
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
