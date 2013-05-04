
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

    const int MAX_LENGTH = 51;
    const int DICT_SIZE = 521196;
    const int INF = std::numeric_limits<int>::max();

    string s;
    int n;
    string D[DICT_SIZE];
    int DC;
    int A[100];
    int AC;

    void get_dict() {
        ifstream ifs("dict.txt");
        while ( ifs >> D[DC] )
            DC ++;
    }

    bool easy_match( string& a, string& b ) {
        if ( a.size() < b.size() )
            return false;
        int cnt = 0;
        for ( int i = 0; i < (int)b.size(); ++ i )
            if ( a[i] != b[i] )
                cnt ++;
        return cnt <= 2;
    }

    int get_min( int cur ) {
        if ( cur >= n ) {
            cout << AC << endl;
            return -1;
        }
        string sub = s.substr(cur, 10);
        int res = INF;
        for ( int i = 0; i < DC; ++ i ) {
            if ( easy_match(sub, D[i]) ) {
                A[AC ++] = i;
                res = min(res, get_min(cur + D[i].size()));
                return -1;
                AC --;
            }
        }
        return res;
    }

    int solve() {
        n = s.size();
        AC = 0;
        return get_min(0);
    }

    class Solution: public ISolution {
    public:

        bool input() {
            return cin >> s;
        }

        void output( int test_no, int result ) {
            cout << "Case #" << test_no << ": " << result << endl;
        }
        
        int run() {
            get_dict();
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


