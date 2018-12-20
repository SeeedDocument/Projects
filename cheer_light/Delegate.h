/*
 * Delegate.h
 * A packed method pointer for OOP.
 *
 * Copyright (c) 2018 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Lets Blu
 * Created Time: Dec 2018
 * Modified Time:
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __DELEGATE_H__
#define __DELEGATE_H__

#include "IDelegate.h"

namespace middleware {
  template <typename T> class Delegate;
}

template <typename T>
class middleware::Delegate
  : public middleware::interface::IDelegate {
public:
  Delegate(T * object, void (T::*method)(void *));
  void invoke(void * args);

protected:
  T * _object;
  void (T::*_method)(void *);
};

template <typename T>
inline middleware::Delegate<T>::Delegate(T * object, void (T::*method)(void *))
  : _object(object), _method(method) { }

template <typename T>
inline void middleware::Delegate<T>::invoke(void * args) {
  (_object->*_method)(args);
}

#endif // __DELEGATE_H__
