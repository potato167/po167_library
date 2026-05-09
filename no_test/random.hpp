random_device seed_gen;
mt19937 rng(seed_gen());
// return [l, r)
long long rand_long(long long l,long long r){
    return uniform_int_distribution<long long>(l,r-1)(rng);
}