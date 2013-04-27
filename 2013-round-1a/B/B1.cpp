
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
    typedef long long LL;
    typedef int INT;
    typedef std::vector<INT> VI;
    typedef std::vector<VI> VVI;
    typedef std::pair<INT,INT> II;
    typedef std::vector<II> VII;
}


// @snippet<sh19910711/contest:solution/multi_tests.cpp>
namespace solution {
    using namespace std;

    const int SIZE = 11;
    const int ENERGY_MAX = 6;

    int E;
    int R;
    int N;
    int V[SIZE];

    void calc_init() {
    }

    LL calc( int x, int e ) {
        if ( x >= N )
            return 0;
        LL res = 0;
        for ( int t = 0; t <= e; ++ t ) {
            int ne = min(E, e - t + R );
            res = max(res, V[x] * t + calc(x + 1, ne));
        }
        return res;
    }

    class Solution: public ISolution {
    public:

        bool input() {
            if ( ! ( cin >> E >> R >> N ) )
                return false;
            for ( int i = 0; i < N; ++ i )
                cin >> V[i];
            return true;
        }

        LL solve() {
            calc_init();
            return calc(0, E);
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


