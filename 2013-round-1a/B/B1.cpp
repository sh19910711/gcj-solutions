
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
    const int BIT_SIZE = 1 << SIZE;
    const int ENERGY_MAX = 6;

    int E;
    int R;
    int N;
    int V[SIZE];
    LL dp[BIT_SIZE][ENERGY_MAX];

    LL calc() {
        for ( int i = 0; i < BIT_SIZE; ++ i )
            for ( int j = 0; j < ENERGY_MAX; ++ j )
                dp[i][j] = 0;

        for ( int i = 0; i < BIT_SIZE; ++ i ) {
            for ( int j = 0; j <= E; ++ j ) {
                // (i, j) = (使用済み, 残りのエネルギー)
                for ( int k = 0; k < N; ++ k ) {
                    int bk = 1 << k;
                    if ( i & bk )
                        continue;
                    int ni = i | bk;
                    for ( int t = 0; t <= j; ++ t ) {
                        // t = 使用するエネルギー
                        int nj = min(E, j - t + R);
                        int g = t * V[k];
                        dp[ni][nj] = max(dp[ni][nj], dp[i][j] + g);
                    }
                }
            }
        }

        LL res = 0;
        for ( int i = 0; i < ENERGY_MAX; ++ i )
            res = max(res, dp[BIT_SIZE - 1][i]);
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
            return calc();
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


