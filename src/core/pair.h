#ifndef PAIR_H
#define PAIR_H

namespace mstd {
    template <typename F, typename S>
    struct pair{
        F first;
        S second;
        pair() {}
        pair(F first, S second) : first(first), second(second) {}
    };
}

#endif