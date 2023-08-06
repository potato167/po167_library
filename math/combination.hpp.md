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
  bundledCode: "#line 2 \"math/combination.hpp\"\n\n#include<vector>\n#include<assert.h>\n\
    \nnamespace po167{\nstruct combination{\n\tint upper;\n\tint MOD;\n\tstd::vector<long\
    \ long> fact;\n\tstd::vector<long long> rev;\n\tstd::vector<long long> fact_rev;\n\
    \tcombination(int max,long long mod):upper(max),MOD(mod),fact(max+1),rev(max+1),fact_rev(max+1){\n\
    \t\tfor(long long i=0;i<=max;i++){\n\t\t\tif(i<2){\n\t\t\t\tfact[i]=1;\n\t\t\t\
    \tfact_rev[i]=1;\n\t\t\t\trev[i]=1;\n\t\t\t\tcontinue;\n\t\t\t}\n\t\t\tfact[i]=(fact[i-1]*i)%mod;\n\
    \t\t\trev[i]=mod-((mod/i)*rev[mod%i])%mod;\n\t\t\tfact_rev[i]=(fact_rev[i-1]*rev[i])%mod;\n\
    \t\t}\n\t}\n\tlong long Comb(int x,int y){\n\t\tassert(upper>=x);\n\t\tif (x<y||y<0||x<0)\
    \ return 0;\n\t\treturn (((fact_rev[y]*fact_rev[x-y])%MOD)*fact[x])%MOD;\n\t}\n\
    \tlong long P(int x,int y){\n\t\tassert(upper>=x);\n\t\tif (x<y||y<0||x<0) return\
    \ 0;\n\t\treturn (fact_rev[x-y]*fact[x])%MOD;\n\t}\n};\n}\nusing po167::combination;\n"
  code: "#pragma once\n\n#include<vector>\n#include<assert.h>\n\nnamespace po167{\n\
    struct combination{\n\tint upper;\n\tint MOD;\n\tstd::vector<long long> fact;\n\
    \tstd::vector<long long> rev;\n\tstd::vector<long long> fact_rev;\n\tcombination(int\
    \ max,long long mod):upper(max),MOD(mod),fact(max+1),rev(max+1),fact_rev(max+1){\n\
    \t\tfor(long long i=0;i<=max;i++){\n\t\t\tif(i<2){\n\t\t\t\tfact[i]=1;\n\t\t\t\
    \tfact_rev[i]=1;\n\t\t\t\trev[i]=1;\n\t\t\t\tcontinue;\n\t\t\t}\n\t\t\tfact[i]=(fact[i-1]*i)%mod;\n\
    \t\t\trev[i]=mod-((mod/i)*rev[mod%i])%mod;\n\t\t\tfact_rev[i]=(fact_rev[i-1]*rev[i])%mod;\n\
    \t\t}\n\t}\n\tlong long Comb(int x,int y){\n\t\tassert(upper>=x);\n\t\tif (x<y||y<0||x<0)\
    \ return 0;\n\t\treturn (((fact_rev[y]*fact_rev[x-y])%MOD)*fact[x])%MOD;\n\t}\n\
    \tlong long P(int x,int y){\n\t\tassert(upper>=x);\n\t\tif (x<y||y<0||x<0) return\
    \ 0;\n\t\treturn (fact_rev[x-y]*fact[x])%MOD;\n\t}\n};\n}\nusing po167::combination;\n"
  dependsOn: []
  isVerificationFile: false
  path: math/combination.hpp
  requiredBy: []
  timestamp: '2023-08-06 17:54:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/combination.hpp
layout: document
redirect_from:
- /library/math/combination.hpp
- /library/math/combination.hpp.html
title: math/combination.hpp
---
