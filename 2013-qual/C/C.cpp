
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

    typedef set<LL> Set;
    const int SIZE = 39;
    LL A, B;
    Set S;
    LL T[SIZE] = {
        1, 4, 9,
        121, 484,
        10201, 12321, 14641, 40804, 44944,
        1002001, 1234321, 4008004,
        100020001, 102030201, 104060401, 121242121, 123454321, 125686521, 400080004, 404090404, 
        10000200001LL, 10221412201LL, 12102420121LL, 12345654321LL, 40000800004LL,
        1000002000001LL, 1002003002001LL, 1004006004001LL, 1020304030201LL,
        1022325232201LL, 1024348434201LL, 1210024200121LL, 1212225222121LL,
        1214428244121LL, 1232346432321LL, 1234567654321LL, 4000008000004LL,
        4004009004004LL
    };

    class Solution: public ISolution {
    public:
        bool input() {
            return cin >> A >> B;
        }

        LL f( LL x ) {
            if ( x == 0 )
                return 0;
            LL* p = lower_bound(T, T + SIZE, x);
            if ( p == T + SIZE )
                return SIZE;
            if ( *p > x )
                return p - T;
            return lower_bound(T, T + SIZE, x) - T + 1;
        }

        LL solve() {
            return f(B) - f(A-1);
        }

        string to_string( int x ) {
            OSS oss;
            oss << x;
            return oss.str();
        }

        bool is_palindromic_number( int x ) {
            string s = to_string(x);
            string rs = s;
            reverse( rs.begin(), rs.end() );
            return s == rs;
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
                output(i+1, solve());
            }
            return 0;
        }
    };
    
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}


