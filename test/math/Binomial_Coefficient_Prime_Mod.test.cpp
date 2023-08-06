#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../../math/combination.hpp"
#include <bits/stdc++.h>
using namespace std;

int main(){
	int T,m;
	cin>>T>>m;
	po167::combination table(min(m,10000000)-1,m);
	while (T--){
		int n,k;
		cin>>n>>k;
		cout<<table.Comb(n,k)<<"\n";
	}
}