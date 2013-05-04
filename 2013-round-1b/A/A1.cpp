
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

    const int SIZE = 111;
    const int MAX_SIZE = 1000000 + 11;
    const int INF = std::numeric_limits<int>::max();

    int k;
    int n;
    int A[SIZE];
    int dp[SIZE][MAX_SIZE];

    bool check( int adds, int dels ) {
        int sum = k;
        for ( int i = 0; i < n - dels; ++ i ) {
            while ( adds > 0 && sum <= A[i] ) {
                sum += sum - 1;
                adds --;
            }
            if ( sum <= A[i] )
                return false;
            sum += A[i];
        }
        return true;
    }

    int solve() {
        sort(A, A + n);
        int res = n;
        for ( int i = 0; i <= n; ++ i ) {
            for ( int j = 0; j <= n; ++ j ) {
                if ( check(i, j) )
                    res = min(res, i + j);
            }
        }
        return res;
    }

    class Solution: public ISolution {
    public:

        bool input() {
            if ( ! ( cin >> k >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i];
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


