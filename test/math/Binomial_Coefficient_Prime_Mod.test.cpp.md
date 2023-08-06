---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combination.hpp
    title: math/combination.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod
    links:
    - https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod
  bundledCode: "#line 1 \"test/math/Binomial_Coefficient_Prime_Mod.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod\"\n\
    \n#line 2 \"math/combination.hpp\"\n\n#include<vector>\n#include<assert.h>\n\n\
    namespace po167{\nstruct combination{\n\tint upper;\n\tint MOD;\n\tstd::vector<long\
    \ long> fact;\n\tstd::vector<long long> rev;\n\tstd::vector<long long> fact_rev;\n\
    \tcombination(int max,long long mod):upper(max),MOD(mod),fact(max+1),rev(max+1),fact_rev(max+1){\n\
    \t\tfor(long long i=0;i<=max;i++){\n\t\t\tif(i<2){\n\t\t\t\tfact[i]=1;\n\t\t\t\
    \tfact_rev[i]=1;\n\t\t\t\trev[i]=1;\n\t\t\t\tcontinue;\n\t\t\t}\n\t\t\tfact[i]=(fact[i-1]*i)%mod;\n\
    \t\t\trev[i]=mod-((mod/i)*rev[mod%i])%mod;\n\t\t\tfact_rev[i]=(fact_rev[i-1]*rev[i])%mod;\n\
    \t\t}\n\t}\n\tlong long Comb(int x,int y){\n\t\tassert(upper>=x);\n\t\tif (x<y||y<0||x<0)\
    \ return 0;\n\t\treturn (((fact_rev[y]*fact_rev[x-y])%MOD)*fact[x])%MOD;\n\t}\n\
    \tlong long P(int x,int y){\n\t\tassert(upper>=x);\n\t\tif (x<y||y<0||x<0) return\
    \ 0;\n\t\treturn (fact_rev[x-y]*fact[x])%MOD;\n\t}\n};\n}\nusing po167::combination;\n\
    #line 4 \"test/math/Binomial_Coefficient_Prime_Mod.test.cpp\"\n#include <bits/stdc++.h>\n\
    using namespace std;\n\nint main(){\n\tint T,m;\n\tcin>>T>>m;\n\tpo167::combination\
    \ table(min(m,10000000)-1,m);\n\twhile (T--){\n\t\tint n,k;\n\t\tcin>>n>>k;\n\t\
    \tcout<<table.Comb(n,k)<<\"\\n\";\n\t}\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod\"\
    \n\n#include \"../../math/combination.hpp\"\n#include <bits/stdc++.h>\nusing namespace\
    \ std;\n\nint main(){\n\tint T,m;\n\tcin>>T>>m;\n\tpo167::combination table(min(m,10000000)-1,m);\n\
    \twhile (T--){\n\t\tint n,k;\n\t\tcin>>n>>k;\n\t\tcout<<table.Comb(n,k)<<\"\\\
    n\";\n\t}\n}"
  dependsOn:
  - math/combination.hpp
  isVerificationFile: true
  path: test/math/Binomial_Coefficient_Prime_Mod.test.cpp
  requiredBy: []
  timestamp: '2023-08-06 17:57:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/math/Binomial_Coefficient_Prime_Mod.test.cpp
layout: document
redirect_from:
- /verify/test/math/Binomial_Coefficient_Prime_Mod.test.cpp
- /verify/test/math/Binomial_Coefficient_Prime_Mod.test.cpp.html
title: test/math/Binomial_Coefficient_Prime_Mod.test.cpp
---
