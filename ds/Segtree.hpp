#pragma once
#include <atcoder/segtree>

namespace po167{
template <class S, S (*op)(S, S), S (*e)()>
struct segtree : atcoder::segtree<S, op, e> {
    using atcoder::segtree<S, op, e>::segtree;
    void updr(int ind, S x) {
        this->set(ind, op(this->get(ind), x));
    }
    void updl(int ind, S x) {
        this->set(ind, op(x, this->get(ind)));
    }
};
}