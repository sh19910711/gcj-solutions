
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

    const int SIZE = 4;
    string S[SIZE];

    class Solution: public ISolution {
    public:
        bool input() {
            for ( int i = 0; i < SIZE; ++ i )
                cin >> S[i];
            return true;
        }

        bool check( char c, char s ) {
            return s != c && s != 'T';
        }

        bool check( char c ) {
            for ( int i = 0; i < 4; ++ i ) {
                bool ok = true;
                for ( int j = 0; j < 4; ++ j ) {
                    if ( check(c, S[i][j]) )
                        ok = false;
                }
                if ( ok )
                    return true;
            }
            for ( int i = 0; i < 4; ++ i ) {
                bool ok = true;
                for ( int j = 0; j < 4; ++ j ) {
                    if ( check(c, S[j][i]) )
                        ok = false;
                }
                if ( ok )
                    return true;
            }
            {
                bool ok = true;
                for ( int i = 0; i < 4; ++ i ) {
                    if ( check(c, S[i][i]) )
                        ok = false;
                }
                if ( ok )
                    return true;
            }
            {
                bool ok = true;
                for ( int i = 0; i < 4; ++ i ) {
                    if ( check(c, S[SIZE-i-1][i]) )
                        ok = false;
                }
                if ( ok )
                    return true;
            }
            return false;
        }

        bool has_empty() {
            for ( int i = 0; i < SIZE; ++ i )
                for ( int j = 0; j < SIZE; ++ j )
                    if ( S[i][j] == '.' )
                        return true;
            return false;
        }

        string solve() {
            if ( check('X') )
                return "X won";
            else if ( check('O') )
                return "O won";
            else if ( has_empty() )
                return "Game has not completed";
            return "Draw";
        }

        void output( int test_no, string result ) {
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


