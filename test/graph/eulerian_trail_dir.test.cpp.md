---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.11.15/x64/lib/python3.11/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.11.15/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.11.15/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n \
    \ File \"/opt/hostedtoolcache/Python/3.11.15/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../../../graph/Eulerian_trail.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/eulerian_trail_directed\"\
    \n\n// #include \"graph/Eulerian_trail.hpp\"\n#include \"../../../graph/Eulerian_trail.hpp\"\
    \n#include <iostream>\nvoid solve();\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int t = 1;\n    std::cin >> t;\n    while (t--)\
    \ solve();\n}\n\nvoid solve(){\n    int N, M;\n    std::cin >> N >> M;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> G(N);\n    for (int i = 0; i < M; i++){\n        int a, b;\n        std::cin\
    \ >> a >> b;\n        G[a].push_back({b, i});\n        // G[b].push_back({a, i});\n\
    \    }\n    auto [var, edge] = po167::Eulerian_trail(G, M, -1, true);\n    if\
    \ (var.empty()){\n        std::cout << \"No\\n\";\n    }\n    else{\n        std::cout\
    \ << \"Yes\\n\";\n        for (int i = 0; i < (int)var.size(); i++){\n       \
    \     std::cout << var[i] << (i + 1 == (int)var.size() ? \"\\n\" : \" \");\n \
    \       }\n        for (int i = 0; i < (int)edge.size(); i++){\n            std::cout\
    \ << edge[i] << (i + 1 == (int)edge.size() ? \"\\n\" : \" \");\n        }\n  \
    \      if (edge.empty()) std::cout << \"\\n\";\n    }\n}"
  dependsOn: []
  isVerificationFile: true
  path: test/graph/eulerian_trail_dir.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/graph/eulerian_trail_dir.test.cpp
layout: document
redirect_from:
- /verify/test/graph/eulerian_trail_dir.test.cpp
- /verify/test/graph/eulerian_trail_dir.test.cpp.html
title: test/graph/eulerian_trail_dir.test.cpp
---
