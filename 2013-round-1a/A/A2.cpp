
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
#include <boost/multiprecision/cpp_int.hpp>

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

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
    typedef std::istringstream ISS;
    typedef std::ostringstream OSS;
    typedef std::vector<std::string> VS;
    typedef int INT;
    typedef std::vector<INT> VI;
    typedef std::vector<VI> VVI;
    typedef std::pair<INT,INT> II;
    typedef std::vector<II> VII;
}


// @snippet<sh19910711/contest:solution/multi_tests.cpp>
namespace solution {
    using namespace std;
    namespace mp = boost::multiprecision;

    typedef mp::cpp_int LL;

    LL r, t;

    LL f( LL x ) {
        return x * x;
    }

    LL g( LL x ) {
        return f(x + 1) - f(x);
    }

    LL z( LL x ) {
        return x * ( 2 * x + 1 + 2 * ( r - 1 ) );
    }

    LL sum( LL x ) {
        return z(x);
    }

    // x回塗ることができるかどうか
    bool check( LL x ) {
        return sum(x) <= t;
    }

    class Solution: public ISolution {
    public:

        bool input() {
            if ( ! ( cin >> r >> t ) )
                return false;
            return true;
        }

        LL solve() {
            LL lb = 0, ub = 1;
            for ( int i = 0; i < 500; ++ i )
                ub *= 2;
            while ( ub - lb > 1 ) {
                LL mid = ( lb + ub ) / 2;
                if ( check(mid) ) {
                    lb = mid;
                } else {
                    ub = mid;
                }
            }
            return lb;
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


