/*
  COPYRIGHT (c) 2012-2022 Esri R&D Center Zurich
  TRADE SECRETS: ESRI PROPRIETARY AND CONFIDENTIAL
  Unpublished material - all rights reserved under the
  Copyright Laws of the United States and applicable international
  laws, treaties, and conventions.

  For additional information, contact:
  Environmental Systems Research Institute, Inc.
  Attn: Contracts and Legal Services Department
  380 New York Street
  Redlands, California, 92373
  USA

  email: contracts@esri.com
*/

#pragma once

#include <utility>


namespace prtx {

template<typename T>
OpaquePtr<T>::OpaquePtr() : m{ new T{} } { }

template<typename T>
template<typename ...Args>
OpaquePtr<T>::OpaquePtr( Args&& ...args ) : m{ new T{ std::forward<Args>(args)... } } { }

template<typename T>
OpaquePtr<T>::OpaquePtr(OpaquePtr<T> const& other) : m{ new T(*other.m) } { };

template<typename T>
OpaquePtr<T>::OpaquePtr(OpaquePtr<T>&& other) : m{ std::move(other.m) } { };

template<typename T>
OpaquePtr<T>& OpaquePtr<T>::operator=(OpaquePtr<T> const& other) {
  *m = *other.m;
  return *this;
}

template<typename T>
OpaquePtr<T>& OpaquePtr<T>::operator=(OpaquePtr<T>&& other) {
  m = std::move(other.m);
  return *this;
}

template<typename T>
OpaquePtr<T>::~OpaquePtr() = default;

template<typename T>
T* OpaquePtr<T>::operator->() { return m.get(); }

template<typename T>
T const* OpaquePtr<T>::operator->() const { return m.get(); }

template<typename T>
T& OpaquePtr<T>::operator*() { return *m.get(); }

} // namespace prtx
