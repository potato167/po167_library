#pragma once

// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
namespace po167{
struct mint61{
    using u64 = unsigned long long;
    const u64 MOD = (1UL << 61) - 1;
    const u64 MASK30 = (1UL << 30) - 1;
    const u64 MASK31 = (1UL << 31) - 1;
    u64  x = 0;
    u64 calcmod(u64 a){
        u64 au = (a >> 61);
        u64 ad = (a & MOD);
        u64 res = au + ad;
        if (res >= MOD) res -= MOD;
        return res;
    }
    mint61(long long x_){
        while (x_ < 0) x_ += MOD;
        x = calcmod(x_);
    }
    mint61 &operator+=(mint61 b){
        if ((x += b.x) >= MOD) x -= MOD;
        return *this;
    }
    mint61 &operator-=(mint61 b){
        if (x >= b.x) x -= b.x;
        else{
            x += MOD;
            x -= b.x;
        }
        return *this;
    }
    mint61 &operator*=(mint61 b){
        u64 au = (x >> 31);
        u64 ad = (x & MASK31);
        u64 bu = (b.x >> 31);
        u64 bd = (b.x & MASK31);
        u64 mid = ad * bu + au * bd;
        u64 midu = (mid >> 30);
        u64 midd = (mid & MASK30);
        x = calcmod(au * bu * 2 + midu + (midd << 31) + ad * bd);
        return *this;
    }
    friend mint61 operator+(mint61 a, mint61 b){return a += b;}
    friend mint61 operator-(mint61 a, mint61 b){return a -= b;}
    friend mint61 operator*(mint61 a, mint61 b){return a *= b;}
    friend bool operator==(mint61 a, mint61 b){return a.x == b.x;}
    friend bool operator!=(mint61 a, mint61 b){return a.x != b.x;}
};
}