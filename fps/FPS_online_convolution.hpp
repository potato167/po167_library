#pragma once
#include <atcoder/convolution>

namespace po167{
    template<class T>
    struct FPS_online_convolution{
        std::vector<T> f, g, h;
        std::vector<std::vector<T>> f_inv, g_inv;
        int p;
        FPS_online_convolution() : f(0), g(0), h(0), p(0){}
        T query(T fi, T gi){
            if (p == 0){
                f = {fi};
                g = {gi};
                h = {fi * gi};
                return h[p++];
            }
            int z = 0;
            while ((p & (1 << z)) == 0) z++;
            if (p == (1 << z)){
                f.resize(p * 2, 0);
                g.resize(p * 2, 0);
                h.resize(p * 2, 0);
            }
            f[p] = fi;
            g[p] = gi;
            int l = p - (1 << z);
            int m = p;
            int r = p + (1 << z);
            // [l, m) -> [m, r)
            std::vector<T> tmp3(r - l);
            if (l == 0){
                f_inv.push_back({});
                g_inv.push_back({});
            }
            for (int rp = 0; rp < 2; rp++){
                std::swap(f, g);
                std::swap(f_inv, g_inv);
                if (l == 0 && rp == 1) break;
                std::vector<T> tmp1(r - l), tmp2(r - l);
                for (int i = l; i < m; i++){
                    tmp1[i - l] = f[i];
                }
                atcoder::internal::butterfly(tmp1);
                if (l == 0) {
                    for (int i = 0; i < r - l; i++) {
                        if (i == 0) continue;
                        if (m <= i) break;
                        tmp2[i] = g[i];
                    }
                    atcoder::internal::butterfly(tmp2);
                }
                else{
                    if (g_inv[z].empty()){
                        g_inv[z].resize((1 << (z + 1)));
                        for (int i = 0; i < (1 << (z + 1)); i++){
                            if (i) g_inv[z][i] = g[i];
                            else g_inv[z][i] = 0;
                        }
                        atcoder::internal::butterfly(g_inv[z]);
                    }
                    tmp2 = g_inv[z];
                }
                for (int i = 0; i < r - l; i++) tmp3[i] += tmp1[i] * tmp2[i];
            }
            atcoder::internal::butterfly_inv(tmp3);
            T iz = (T)(1) / (T)(r - l);
            for (int i = m; i < r; i++) h[i] += tmp3[i - l] * iz;
            h[p] += f[0] * g[p];
            h[p] += f[p] * g[0];
            return h[p++];
        }
    };
}