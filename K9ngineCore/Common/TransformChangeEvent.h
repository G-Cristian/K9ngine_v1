#pragma once

#include "../Math/Transform.h"
#include "../K9Debug.h"
#include "IObserver.h"

#include <algorithm>
#include <memory>
#include <set>
#include <iostream>
namespace K9ngineCore {
  namespace Common {
    template<typename T>
    class TransformChangeEvent {
    public:
      class EventArg;
      using Subject = T;
      using ObserverType = IObserver<Subject, EventArg>;
      using ObserverTypePtr = std::shared_ptr< ObserverType >;

      class EventArg {
      public:
        EventArg(const K9Math::Transform&, const K9Math::Transform&);

        const K9Math::Transform& getOldValue() const;
        const K9Math::Transform& getNewValue() const;
      private:
        K9Math::Transform mOldValue;
        K9Math::Transform mNewValue;
      };

      explicit TransformChangeEvent(Subject* subject);
      TransformChangeEvent(TransformChangeEvent&&) noexcept;
      TransformChangeEvent& operator=(TransformChangeEvent&&) noexcept;
      ~TransformChangeEvent();

      TransformChangeEvent<Subject>& operator+=(ObserverTypePtr);
      TransformChangeEvent<Subject>& operator-=(ObserverTypePtr);

      void moveObserversTo(TransformChangeEvent<T>& other);

      void notify(const K9Math::Transform&, const K9Math::Transform&)const;
    private:
      TransformChangeEvent(const TransformChangeEvent&);
      TransformChangeEvent& operator=(const TransformChangeEvent&) = delete;

      std::set< ObserverTypePtr > mObservers{};
      Subject* mSubject;
    };

    template<typename T>
    TransformChangeEvent<T>::EventArg::EventArg(const K9Math::Transform& oldValue, const K9Math::Transform& newValue)
      : mOldValue{oldValue}
      , mNewValue{newValue} {
    }

    template<typename T>
    const K9Math::Transform& TransformChangeEvent<T>::EventArg::getOldValue() const { return mOldValue; }

    template<typename T>
    const K9Math::Transform& TransformChangeEvent<T>::EventArg::getNewValue() const { return mNewValue; }

    template<typename T>
    TransformChangeEvent<T>::TransformChangeEvent<T>(Subject* subject)
      :mSubject{ subject } {
      K9ASSERT(subject, "Subject is null");
    }

    template<typename T>
    TransformChangeEvent<T>::TransformChangeEvent(TransformChangeEvent&& other) noexcept
      : mObservers{ std::move(other.mObservers) }
      , mSubject{ other.mSubject }
    {
      other.mSubject = nullptr;
    }

    template<typename T>
    TransformChangeEvent<T>& TransformChangeEvent<T>::operator=(TransformChangeEvent&& other) noexcept
    {
      if (this != &other) {
        mObservers = std::move(other.mObservers);
        mSubject = other.mSubject;

        other.mSubject = nullptr;
      }

      return *this;
    }

    template<typename T>
    TransformChangeEvent<T>::~TransformChangeEvent()
    {
      mObservers.clear();
      mSubject = nullptr;
    }

    template<typename T>
    TransformChangeEvent<T>& TransformChangeEvent<T>::operator+=(ObserverTypePtr observer) {
      K9ASSERT(!mObservers.contains(observer), "Observer already exists.");
      mObservers.insert(observer);
      return *this;
    }

    template<typename T>
    TransformChangeEvent<T>& TransformChangeEvent<T>::operator-=(ObserverTypePtr observer) {
      auto found = mObservers.find(observer);
      if (found != mObservers.cend()) {
        mObservers.erase(found);
      }

      return *this;
    }

    template<typename T>
    void TransformChangeEvent<T>::moveObserversTo(TransformChangeEvent<T>& other) {
      for (auto& observer :mObservers) {
        other += observer;
      }

      mObservers.clear();
    }

    template<typename T>
    void TransformChangeEvent<T>::notify(const K9Math::Transform& oldValue, const K9Math::Transform& newValue) const {
      K9ASSERT(mSubject, "Subject is null");
      if (mSubject)
      {
        for (auto it = mObservers.begin(); it != mObservers.end(); it++) {
          K9ASSERT(*it, "Observer is null");
          if (*it) {
            (*it)->update(*mSubject, EventArg(oldValue, newValue));
          }
        }
      }
    }
  }
}