
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


// @snippet<sh19910711/contest:solution/multi_tests.cpp>
namespace solution {
    using namespace std;

    const int SIZE = 11;
    const int OFFSET = 500;
    const int WIDTH = 1000;
    int n;
    int D[SIZE];
    int N[SIZE];
    int W[SIZE];
    int E[SIZE];
    int L[SIZE];
    int S[SIZE];
    int DD[SIZE];
    int DP[SIZE];
    int DS[SIZE];

    int A[WIDTH];

    void adjust_tribe() {
        for ( int i = 0; i < n; ++ i ) {
            W[i] += OFFSET;
            E[i] += OFFSET;
            L[i] = abs(W[i] - E[i]);
        }
    }

    bool simulate_attack( int t, int k ) {
        int times = ( t - D[k] ) / DD[k];
        int offset = W[k] + times * DP[k];
        int power = S[k] + DS[k] * times;

        bool ok = false;
        for ( int i = 0; i < L[k]; ++ i ) {
            if ( A[offset + i] < power ) {
                A[offset + i] = power;
                ok = true;
            }
        }

        return ok;
    }

    int solve() {
        adjust_tribe();
        int res = 0;
        for ( int t = 0; t < 1000000; ++ t ) {
            for ( int i = 0; i < n; ++ i ) {
                if ( D[i] <= t && t < D[i] + N[i] * DD[i] && ( t - D[i] ) % DD[i] == 0 ) {
                    if ( simulate_attack(t, i) )
                        res ++;
                }
            }
        }
        return res;
    }

    class Solution: public ISolution {
    public:

        void init() {
            fill(A, A + WIDTH, 0);
        }

        bool input_tribe( int k ) {
            return cin >> D[k] >> N[k] >> W[k] >> E[k] >> S[k] >> DD[k] >> DP[k] >> DS[k];
        }

        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                input_tribe(i);
            return true;
        }

        void output( int test_no, int result ) {
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


