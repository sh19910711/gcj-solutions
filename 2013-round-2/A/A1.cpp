
// @snippet<sh19910711/contest:headers.cpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <complex>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
    typedef std::istringstream ISS;
    typedef std::ostringstream OSS;
    typedef std::vector<std::string> VS;
    typedef long long LL;
    typedef int INT;
    typedef std::vector<INT> VI;
    typedef std::vector<VI> VVI;
    typedef std::pair<INT,INT> II;
    typedef std::vector<II> VII;
}

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
    class ISolution {
    public:
        virtual void init() {};
        virtual bool input() { return false; };
        virtual void output() {};
        virtual int run() = 0;
    };
}


// @snippet<sh19910711/contest:io/pair.cpp>
namespace io {
    template <class A, class B> std::ostream& operator<<( std::ostream& os, const std::pair<A,B>& p ) {
        return os << "(" << p.first << "," << p.second << ")";
    }
    template <class A, class B> std::istream& operator>>( std::istream& is, std::pair<A,B>& p ) {
        return is >> p.first >> p.second;
    }
}

// @snippet<sh19910711/contest:solution/multi_tests.cpp>
namespace solution {
    using namespace std;
    using namespace io;
    
    typedef pair <LL, LL> Pair;
    typedef pair <Pair, LL> Range;
    
    const int SIZE = 1001;
    const LL MOD = 1000002013LL;
    
    int N, M;
    Range R[SIZE];
    
    bool is_intersect( Pair a, Pair b ) {
        return ( a.first <= b.first && b.first <= a.second );
    }

    LL get_cost( Pair p ) {
        LL x = abs(p.first - p.second) + 1;
        return x * ( x + 1 ) / 2LL;
    }

    bool can_make_bigger( Pair a, Pair b ) {
        Pair swapped_a = a, swapped_b = b;
        swap(swapped_a.first, swapped_b.first);
        if ( get_cost(a) < get_cost(swapped_a) && get_cost(b) < get_cost(swapped_a) )
            return true;
        if ( get_cost(a) < get_cost(swapped_b) && get_cost(b) < get_cost(swapped_b) )
            return true;
        return false;
    }

    bool update() {
        for ( int i = 0; i < M; ++ i ) {
            for ( int j = i + 1; j < M; ++ j ) {
                if ( R[i].second > 0 && R[j].second > 0 && is_intersect(R[i].first, R[j].first) && can_make_bigger(R[i].first, R[j].first) ) {
                    Range a = R[i], b = R[j];
                    if ( a.second < b.second ) {
                        R[j].second -= b.second - a.second;
                        R[M].second = b.second - a.second;
                        R[M].first.first = b.first.first;
                        R[M].first.second = b.first.second;
                        M ++;
                    } else if ( a.second > b.second ) {
                        R[i].second -= a.second - b.second;
                        R[M].second = a.second - b.second;
                        R[M].first.first = a.first.first;
                        R[M].first.second = a.first.second;
                        M ++;
                    }
                    swap(R[i].first.first, R[j].first.first);
                    return true;
                }
            }
        }
        return false;
    }

    LL get_sum() {
        LL res = 0;
        for ( int i = 0; i < M; ++ i ) {
            res = res + get_cost(R[i].first) * R[i].second;
        }
        return res;
    }
    
    LL solve() {
        LL org_sum = get_sum();
        sort(R, R + M);
        while ( update() ) {
            sort(R, R + M);
        }
        LL new_sum = get_sum();
        return abs(new_sum - org_sum ) % MOD;
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> N >> M ) )
                return false;
            for ( int i = 0; i < M; ++ i )
                cin >> R[i].first.first >> R[i].first.second >> R[i].second;
            return true;
        }
        
        void output( int test_no, LL result ) {
            cout << "Case #" << test_no << ": " << result << endl;
        }
        
        int run() {
            int tests;
            std::cin >> tests;
            for ( int i = 0; i < tests; ++ i ) {
                init();
                input();
                output(i + 1, solve());
            }
            return 0;
        }
        
    };
    
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}



