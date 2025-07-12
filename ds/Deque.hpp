#pragma once
#include <vector>
#include <cassert>
namespace po167{
// GPT 作
template<typename T>
struct Deque {
    Deque()
            : _cap(8), _size(0), _head(0)
    {
        _data = static_cast<T*>(operator new[](sizeof(T) * _cap));
    }

    ~Deque() {
        clear();
        operator delete[](_data);
    }

    // 要素数
    int size() const { return _size; }
    bool empty() const { return _size == 0; }

    // 前後に要素を追加
    void push_back(const T& v) { emplace_back(v); }
    void push_back(T&& v) { emplace_back(std::move(v)); }
    void push_front(const T& v) { emplace_front(v); }
    void push_front(T&& v) { emplace_front(std::move(v)); }

    // 前後から取り出し
    void pop_back() {
        assert(!empty());
        int idx = (_head + _size - 1) & (_cap - 1);
        _data[idx].~T();
        --_size;
    }
    void pop_front() {
        assert(!empty());
        _data[_head].~T();
        _head = ( _head + 1 ) & (_cap - 1);
        --_size;
    }

    // 前後の参照
    T& front() {
        assert(!empty());
        return _data[_head];
    }
    T& back() {
        assert(!empty());
        int idx = (_head + _size - 1) & (_cap - 1);
        return _data[idx];
    }

    // 添字アクセス (0 ≤ i < size())
    T& operator[](int i) {
        assert(i >= 0 && i < _size);
        return _data[( _head + i ) & (_cap - 1)];
    }
    const T& operator[](int i) const {
        assert(i >= 0 && i < _size);
        return _data[( _head + i ) & (_cap - 1)];
    }

    // 全要素をクリア
    void clear() {
        for(int i = 0; i < _size; i++){
            int idx = (_head + i) & (_cap - 1);
            _data[idx].~T();
        }
        _size = 0;
        _head = 0;
    }

private:
    T* _data;
    int _cap;   // 必ず2のべき乗
    int _size;
    int _head;  // 先頭要素のインデックス

    // 空きがなければ拡張
    void ensure_capacity() {
        if (_size < _cap) return;
        int new_cap = _cap << 1;
        T* new_data = static_cast<T*>(operator new[](sizeof(T) * new_cap));
        // 要素を head から順にコピー
        for(int i = 0; i < _size; i++){
            new (&new_data[i]) T(std::move((*this)[i]));
            (*this)[i].~T();
        }
        operator delete[](_data);
        _data = new_data;
        _cap = new_cap;
        _head = 0;
    }

    // 前後に emplace
    template<typename... Args>
    void emplace_back(Args&&... args) {
        ensure_capacity();
        int idx = (_head + _size) & (_cap - 1);
        new(&_data[idx]) T(std::forward<Args>(args)...);
        ++_size;
    }
    template<typename... Args>
    void emplace_front(Args&&... args) {
        ensure_capacity();
        _head = (_head - 1) & (_cap - 1);
        new(&_data[_head]) T(std::forward<Args>(args)...);
        ++_size;
    }
};
}
