---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"no_test/random.hpp\"\nrandom_device seed_gen;\nmt19937 rng(seed_gen());\n\
    // return [l, r)\nlong long rand_long(long long l,long long r){\n    return uniform_int_distribution<long\
    \ long>(l,r-1)(rng);\n}\n"
  code: "random_device seed_gen;\nmt19937 rng(seed_gen());\n// return [l, r)\nlong\
    \ long rand_long(long long l,long long r){\n    return uniform_int_distribution<long\
    \ long>(l,r-1)(rng);\n}"
  dependsOn: []
  isVerificationFile: false
  path: no_test/random.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/random.hpp
layout: document
redirect_from:
- /library/no_test/random.hpp
- /library/no_test/random.hpp.html
title: no_test/random.hpp
---
