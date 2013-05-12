
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

    const int SIZE = 1000000 + 11;

    string s;
    int n;
    int k; // 問題分で言うn

    int A[SIZE];
    int B[SIZE];

    inline bool is_vowel( char c ) {
        return c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o';
    }

    void calc_consecutives() {
        fill(A, A + SIZE, 0);
        int cnt = 0;
        for ( int i = n - 1; i >= 0; -- i ) {
            if ( is_vowel(s[i]) ) {
                cnt = 0;
            } else {
                cnt ++;
            }
            A[i] = cnt;
        }
        int prev = 0;
        for ( int i = 0; i < n; ++ i ) {
            B[i] = prev;
            if ( A[i] >= k ) {
                prev = i + 1;
            }
        }
    }

    int calc_numbers() {
        int res = 0;
        for ( int i = 0; i < n; ++ i ) {
            if ( A[i] >= k ) {
                int l = i - B[i] + 1;
                int r = n - i - k + 1;
                res += l * r;
            }
        }
        return res;
    }

    int solve() {
        n = s.size();
        calc_consecutives();
        return calc_numbers();
    }

    class Solution: public ISolution {
    public:
        bool input() {
            return cin >> s >> k;
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


