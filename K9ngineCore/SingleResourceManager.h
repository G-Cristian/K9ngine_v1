#ifndef SINGLERESOURCEMANAGER_H
#define SINGLERESOURCEMANAGER_H

#include "Handle.h"
#include "Common/Hasher.h"
#include "K9Debug.h"
#include "FileSystem/ResourceLoader.h"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace K9ngineCore {
	template<typename T>
	class SingleResourceManager {
	public:
		SingleResourceManager(size_t elementsCount);
		SingleResourceManager(const SingleResourceManager&) = delete;
		SingleResourceManager(SingleResourceManager&&) noexcept = delete;

		SingleResourceManager&operator=(const SingleResourceManager&) = delete;
		SingleResourceManager& operator=(SingleResourceManager&&) noexcept = delete;

		Memory::Handle<T> loadResourceIfNeeded(const std::string& path);

		template<typename... Args>
		Memory::Handle<T> createResourceIfNeeded(const std::string& sId, Args&&... args) {
			return createResourceIfNeeded(Utility::hashString(sId), std::forward<Args>(args)...);
		}

		template<typename... Args>
		Memory::Handle<T> createResourceIfNeeded(uint64_t id, Args&&... args);

		Memory::Handle<T> getHandle(const std::string& path) const {
			return getHandle(Utility::hashString(path));
		}

		Memory::Handle<T> getHandle(uint64_t uid) const;

		void deleteResource(const std::string& sId) { deleteResource(Utility::hashString(sId)); }
		void deleteResource(uint64_t id);
	private:
		Memory::Handle<T> retrieveFromHashTable(uint64_t guid, uint64_t handleIndex) const;
		Memory::Handle<T> addResource(uint64_t id, T* pElement);

		std::unordered_map<uint64_t, uint64_t> _handlesIndices;
		Memory::HandleTable<T> _handleTable;
	};

	/*******************************/
	/****** IMPLEMENTATIONS ********/
	/*******************************/

	template<typename T>
	Memory::Handle<T> SingleResourceManager<T>::loadResourceIfNeeded(const std::string& path) {
		uint64_t uid = Utility::hashString(path);
		auto it = _handlesIndices.find(uid);
		if (it != _handlesIndices.end()) {
			K9ASSERT(_handleTable.isValid(uid, it->second), "SingleResourceManager<T>::loadResourceIfNeeded: invalid handle");
			return retrieveFromHashTable(uid, it->second);
		}

		T* resource = FileSystem::ResourceLoader<T>::loadResource(path);

		return addResource(uid, resource);
	}

	template<typename T>
	template<typename... Args>
	Memory::Handle<T> SingleResourceManager<T>::createResourceIfNeeded(uint64_t id, Args&&... args) {
		auto it = _handlesIndices.find(id);
		if (it != _handlesIndices.end()) {
			K9ASSERT(_handleTable.isValid(id, it->second), "SingleResourceManager<T>::createResourceIfNeeded: invalid handle");
			return retrieveFromHashTable(id, it->second);
		}

		T* resource = new T(id, std::forward<Args>(args)...);
		return addResource(uid, resource);
	}

	template<typename T>
	Memory::Handle<T> SingleResourceManager<T>::getHandle(uint64_t uid) const {
		auto it = _handlesIndices.find(uid);
		if (it == _handlesIndices.cend() || !_handleTable.isValid(uid, it->second)) {
			return Memory::HandleTable<T>::NullHandle;
		}

		return _handleTable.getHandle(it->second);
	}

	template<typename T>
	void SingleResourceManager<T>::deleteResource(uint64_t id) {
		auto handleIt = _handlesIndices.find(id);
		K9ASSERT(handleIt != _handlesIndices.end(), "SingleResourceManager<T>::deleteResource: handle not found");
		if (handleIt != _handlesIndices.end()) {
			K9ASSERT(_handleTable.isValid(id, handleIt->second), "SingleResourceManager<T>::deleteResource: invalid handle");
			if (_handleTable.isValid(id, handleIt->second)) {
				_handleTable.deleteHandle(handleIt->second);
			}
			_handlesIndices.erase(handleIt);
		}
	}

	template<typename T>
	Memory::Handle<T> SingleResourceManager<T>::retrieveFromHashTable(uint64_t guid, uint64_t handleIndex) const {
		if (_handleTable.isValid(guid, handleIndex)) {
			return _handleTable.getHandle(handleIndex);
		}
		else {
			return _handleTable.NullHandle;
		}
	}

	template<typename T>
	Memory::Handle<T> SingleResourceManager<T>::addResource(uint64_t id, T* pElement) {
		K9ASSERT(_handlesIndices.find(id) == _handlesIndices.end(), "SingleResourceManager<T>::addResource: id already exists");
		size_t index = _handleTable.createHandle(uid, value);
		_handlesIndices[id] = index;
		return _handleTable.getHandle(index);
	}
}

#endif // !SINGLERESOURCEMANAGER_H
