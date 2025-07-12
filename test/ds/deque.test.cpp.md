---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/Deque.hpp
    title: ds/Deque.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/3199
    links:
    - https://yukicoder.me/problems/no/3199
  bundledCode: "#line 1 \"test/ds/deque.test.cpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/3199\"\
    \n\n\n#line 2 \"ds/Deque.hpp\"\n#include <vector>\n#include <cassert>\nnamespace\
    \ po167{\n// GPT \u4F5C\ntemplate<typename T>\nstruct Deque {\n    Deque()\n \
    \           : _cap(8), _size(0), _head(0)\n    {\n        _data = static_cast<T*>(operator\
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
    \    }\n};\n}\n#line 5 \"test/ds/deque.test.cpp\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n#define rep(i, a, b) for (int i = (int)(a); i < (int)(b);\
    \ i++)\nconst int INF = 2100000000;\ntemplate<class T> bool chmin(T &a, T b){return\
    \ (a > b ? a = b, 1 : 0);}\n\nvoid solve();\n// POP'N ROLL MUSIC / TOMOO\nint\
    \ main() {\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n\n    int\
    \ t = 1;\n    // cin >> t;\n    rep(i, 0, t) solve();\n}\n\nvoid solve(){\n  \
    \  int H, W, M;\n    cin >> H >> W >> M;\n    vector<string> S(H);\n    rep(i,\
    \ 0, H) cin >> S[i];\n    int sx, sy, gx, gy;\n    rep(i, 0, H) rep(j, 0, W){\n\
    \            if (S[i][j] == 'S') sx = i, sy = j;\n            if (S[i][j] == 'G')\
    \ gx = i, gy = j;\n        }\n    vector dp(M + 1, vector(H, vector<int>(W, INF)));\n\
    \    po167::Deque<tuple<int, int, int>> q;\n    q.push_back({0, sx, sy});\n  \
    \  dp[0][sx][sy] = 0;\n    vector<int> dx = {0, 0, 1, -1}, dy = {1, -1, 0, 0};\n\
    \    while (!q.empty()){\n        auto [c, x, y] = q.front();\n        q.pop_front();\n\
    \        if ('1' <= S[x][y] && S[x][y] <= '9' && S[x][y] != (char)('0' + c)){\n\
    \            int d = S[x][y] - '0';\n            if (dp[d][x][y] == INF){\n  \
    \              dp[d][x][y] = dp[c][x][y];\n                q.push_front({d, x,\
    \ y});\n            }\n            continue;\n        }\n        if ('a' <= S[x][y]\
    \ && S[x][y] <= 'z' && S[x][y] != (char)('a' + c - 1)) continue;\n        rep(k,\
    \ 0, 4){\n            int s = dx[k] + x;\n            int t = dy[k] + y;\n   \
    \         if (s < 0 || H <= s || t < 0 || W <= t) continue;\n            if (S[s][t]\
    \ == '#') continue;\n            if (chmin(dp[c][s][t], dp[c][x][y] + 1)){\n \
    \               q.push_back({c, s, t});\n                continue;\n         \
    \   }\n        }\n    }\n    int ans = INF;\n    rep(i, 0, M + 1) chmin(ans, dp[i][gx][gy]);\n\
    \    if (ans == INF) ans = -1;\n    cout << ans << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/3199\"\n\n\n#include \"\
    ../../ds/Deque.hpp\"\n\n#include <bits/stdc++.h>\nusing namespace std;\n#define\
    \ rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)\nconst int INF = 2100000000;\n\
    template<class T> bool chmin(T &a, T b){return (a > b ? a = b, 1 : 0);}\n\nvoid\
    \ solve();\n// POP'N ROLL MUSIC / TOMOO\nint main() {\n    ios::sync_with_stdio(false);\n\
    \    cin.tie(nullptr);\n\n    int t = 1;\n    // cin >> t;\n    rep(i, 0, t) solve();\n\
    }\n\nvoid solve(){\n    int H, W, M;\n    cin >> H >> W >> M;\n    vector<string>\
    \ S(H);\n    rep(i, 0, H) cin >> S[i];\n    int sx, sy, gx, gy;\n    rep(i, 0,\
    \ H) rep(j, 0, W){\n            if (S[i][j] == 'S') sx = i, sy = j;\n        \
    \    if (S[i][j] == 'G') gx = i, gy = j;\n        }\n    vector dp(M + 1, vector(H,\
    \ vector<int>(W, INF)));\n    po167::Deque<tuple<int, int, int>> q;\n    q.push_back({0,\
    \ sx, sy});\n    dp[0][sx][sy] = 0;\n    vector<int> dx = {0, 0, 1, -1}, dy =\
    \ {1, -1, 0, 0};\n    while (!q.empty()){\n        auto [c, x, y] = q.front();\n\
    \        q.pop_front();\n        if ('1' <= S[x][y] && S[x][y] <= '9' && S[x][y]\
    \ != (char)('0' + c)){\n            int d = S[x][y] - '0';\n            if (dp[d][x][y]\
    \ == INF){\n                dp[d][x][y] = dp[c][x][y];\n                q.push_front({d,\
    \ x, y});\n            }\n            continue;\n        }\n        if ('a' <=\
    \ S[x][y] && S[x][y] <= 'z' && S[x][y] != (char)('a' + c - 1)) continue;\n   \
    \     rep(k, 0, 4){\n            int s = dx[k] + x;\n            int t = dy[k]\
    \ + y;\n            if (s < 0 || H <= s || t < 0 || W <= t) continue;\n      \
    \      if (S[s][t] == '#') continue;\n            if (chmin(dp[c][s][t], dp[c][x][y]\
    \ + 1)){\n                q.push_back({c, s, t});\n                continue;\n\
    \            }\n        }\n    }\n    int ans = INF;\n    rep(i, 0, M + 1) chmin(ans,\
    \ dp[i][gx][gy]);\n    if (ans == INF) ans = -1;\n    cout << ans << \"\\n\";\n\
    }\n"
  dependsOn:
  - ds/Deque.hpp
  isVerificationFile: true
  path: test/ds/deque.test.cpp
  requiredBy: []
  timestamp: '2025-07-12 19:01:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/ds/deque.test.cpp
layout: document
redirect_from:
- /verify/test/ds/deque.test.cpp
- /verify/test/ds/deque.test.cpp.html
title: test/ds/deque.test.cpp
---
