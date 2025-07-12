---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/ds/deque.test.cpp
    title: test/ds/deque.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/Deque.hpp\"\n#include <vector>\n#include <cassert>\n\
    namespace po167{\n// GPT \u4F5C\ntemplate<typename T>\nstruct Deque {\n    Deque()\n\
    \            : _cap(8), _size(0), _head(0)\n    {\n        _data = static_cast<T*>(operator\
    \ new[](sizeof(T) * _cap));\n    }\n\n    ~Deque() {\n        clear();\n     \
    \   operator delete[](_data);\n    }\n\n    // \u8981\u7D20\u6570\n    int size()\
    \ const { return _size; }\n    bool empty() const { return _size == 0; }\n\n \
    \   // \u524D\u5F8C\u306B\u8981\u7D20\u3092\u8FFD\u52A0\n    void push_back(const\
    \ T& v) { emplace_back(v); }\n    void push_back(T&& v) { emplace_back(std::move(v));\
    \ }\n    void push_front(const T& v) { emplace_front(v); }\n    void push_front(T&&\
    \ v) { emplace_front(std::move(v)); }\n\n    // \u524D\u5F8C\u304B\u3089\u53D6\
    \u308A\u51FA\u3057\n    void pop_back() {\n        assert(!empty());\n       \
    \ int idx = (_head + _size - 1) & (_cap - 1);\n        _data[idx].~T();\n    \
    \    --_size;\n    }\n    void pop_front() {\n        assert(!empty());\n    \
    \    _data[_head].~T();\n        _head = ( _head + 1 ) & (_cap - 1);\n       \
    \ --_size;\n    }\n\n    // \u524D\u5F8C\u306E\u53C2\u7167\n    T& front() {\n\
    \        assert(!empty());\n        return _data[_head];\n    }\n    T& back()\
    \ {\n        assert(!empty());\n        int idx = (_head + _size - 1) & (_cap\
    \ - 1);\n        return _data[idx];\n    }\n\n    // \u6DFB\u5B57\u30A2\u30AF\u30BB\
    \u30B9 (0 \u2264 i < size())\n    T& operator[](int i) {\n        assert(i >=\
    \ 0 && i < _size);\n        return _data[( _head + i ) & (_cap - 1)];\n    }\n\
    \    const T& operator[](int i) const {\n        assert(i >= 0 && i < _size);\n\
    \        return _data[( _head + i ) & (_cap - 1)];\n    }\n\n    // \u5168\u8981\
    \u7D20\u3092\u30AF\u30EA\u30A2\n    void clear() {\n        for(int i = 0; i <\
    \ _size; i++){\n            int idx = (_head + i) & (_cap - 1);\n            _data[idx].~T();\n\
    \        }\n        _size = 0;\n        _head = 0;\n    }\n\nprivate:\n    T*\
    \ _data;\n    int _cap;   // \u5FC5\u305A2\u306E\u3079\u304D\u4E57\n    int _size;\n\
    \    int _head;  // \u5148\u982D\u8981\u7D20\u306E\u30A4\u30F3\u30C7\u30C3\u30AF\
    \u30B9\n\n    // \u7A7A\u304D\u304C\u306A\u3051\u308C\u3070\u62E1\u5F35\n    void\
    \ ensure_capacity() {\n        if (_size < _cap) return;\n        int new_cap\
    \ = _cap << 1;\n        T* new_data = static_cast<T*>(operator new[](sizeof(T)\
    \ * new_cap));\n        // \u8981\u7D20\u3092 head \u304B\u3089\u9806\u306B\u30B3\
    \u30D4\u30FC\n        for(int i = 0; i < _size; i++){\n            new (&new_data[i])\
    \ T(std::move((*this)[i]));\n            (*this)[i].~T();\n        }\n       \
    \ operator delete[](_data);\n        _data = new_data;\n        _cap = new_cap;\n\
    \        _head = 0;\n    }\n\n    // \u524D\u5F8C\u306B emplace\n    template<typename...\
    \ Args>\n    void emplace_back(Args&&... args) {\n        ensure_capacity();\n\
    \        int idx = (_head + _size) & (_cap - 1);\n        new(&_data[idx]) T(std::forward<Args>(args)...);\n\
    \        ++_size;\n    }\n    template<typename... Args>\n    void emplace_front(Args&&...\
    \ args) {\n        ensure_capacity();\n        _head = (_head - 1) & (_cap - 1);\n\
    \        new(&_data[_head]) T(std::forward<Args>(args)...);\n        ++_size;\n\
    \    }\n};\n}\n"
  code: "#pragma once\n#include <vector>\n#include <cassert>\nnamespace po167{\n//\
    \ GPT \u4F5C\ntemplate<typename T>\nstruct Deque {\n    Deque()\n            :\
    \ _cap(8), _size(0), _head(0)\n    {\n        _data = static_cast<T*>(operator\
    \ new[](sizeof(T) * _cap));\n    }\n\n    ~Deque() {\n        clear();\n     \
    \   operator delete[](_data);\n    }\n\n    // \u8981\u7D20\u6570\n    int size()\
    \ const { return _size; }\n    bool empty() const { return _size == 0; }\n\n \
    \   // \u524D\u5F8C\u306B\u8981\u7D20\u3092\u8FFD\u52A0\n    void push_back(const\
    \ T& v) { emplace_back(v); }\n    void push_back(T&& v) { emplace_back(std::move(v));\
    \ }\n    void push_front(const T& v) { emplace_front(v); }\n    void push_front(T&&\
    \ v) { emplace_front(std::move(v)); }\n\n    // \u524D\u5F8C\u304B\u3089\u53D6\
    \u308A\u51FA\u3057\n    void pop_back() {\n        assert(!empty());\n       \
    \ int idx = (_head + _size - 1) & (_cap - 1);\n        _data[idx].~T();\n    \
    \    --_size;\n    }\n    void pop_front() {\n        assert(!empty());\n    \
    \    _data[_head].~T();\n        _head = ( _head + 1 ) & (_cap - 1);\n       \
    \ --_size;\n    }\n\n    // \u524D\u5F8C\u306E\u53C2\u7167\n    T& front() {\n\
    \        assert(!empty());\n        return _data[_head];\n    }\n    T& back()\
    \ {\n        assert(!empty());\n        int idx = (_head + _size - 1) & (_cap\
    \ - 1);\n        return _data[idx];\n    }\n\n    // \u6DFB\u5B57\u30A2\u30AF\u30BB\
    \u30B9 (0 \u2264 i < size())\n    T& operator[](int i) {\n        assert(i >=\
    \ 0 && i < _size);\n        return _data[( _head + i ) & (_cap - 1)];\n    }\n\
    \    const T& operator[](int i) const {\n        assert(i >= 0 && i < _size);\n\
    \        return _data[( _head + i ) & (_cap - 1)];\n    }\n\n    // \u5168\u8981\
    \u7D20\u3092\u30AF\u30EA\u30A2\n    void clear() {\n        for(int i = 0; i <\
    \ _size; i++){\n            int idx = (_head + i) & (_cap - 1);\n            _data[idx].~T();\n\
    \        }\n        _size = 0;\n        _head = 0;\n    }\n\nprivate:\n    T*\
    \ _data;\n    int _cap;   // \u5FC5\u305A2\u306E\u3079\u304D\u4E57\n    int _size;\n\
    \    int _head;  // \u5148\u982D\u8981\u7D20\u306E\u30A4\u30F3\u30C7\u30C3\u30AF\
    \u30B9\n\n    // \u7A7A\u304D\u304C\u306A\u3051\u308C\u3070\u62E1\u5F35\n    void\
    \ ensure_capacity() {\n        if (_size < _cap) return;\n        int new_cap\
    \ = _cap << 1;\n        T* new_data = static_cast<T*>(operator new[](sizeof(T)\
    \ * new_cap));\n        // \u8981\u7D20\u3092 head \u304B\u3089\u9806\u306B\u30B3\
    \u30D4\u30FC\n        for(int i = 0; i < _size; i++){\n            new (&new_data[i])\
    \ T(std::move((*this)[i]));\n            (*this)[i].~T();\n        }\n       \
    \ operator delete[](_data);\n        _data = new_data;\n        _cap = new_cap;\n\
    \        _head = 0;\n    }\n\n    // \u524D\u5F8C\u306B emplace\n    template<typename...\
    \ Args>\n    void emplace_back(Args&&... args) {\n        ensure_capacity();\n\
    \        int idx = (_head + _size) & (_cap - 1);\n        new(&_data[idx]) T(std::forward<Args>(args)...);\n\
    \        ++_size;\n    }\n    template<typename... Args>\n    void emplace_front(Args&&...\
    \ args) {\n        ensure_capacity();\n        _head = (_head - 1) & (_cap - 1);\n\
    \        new(&_data[_head]) T(std::forward<Args>(args)...);\n        ++_size;\n\
    \    }\n};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/Deque.hpp
  requiredBy: []
  timestamp: '2025-07-12 19:01:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/ds/deque.test.cpp
documentation_of: ds/Deque.hpp
layout: document
redirect_from:
- /library/ds/Deque.hpp
- /library/ds/Deque.hpp.html
title: ds/Deque.hpp
---
