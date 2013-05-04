
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

    const int DICT_SIZE = 521196;
    const int INF = std::numeric_limits<int>::max();

    string s;
    int n;
    string D[DICT_SIZE];
    int DC;
    int smallest;

    void get_dict() {
        ifstream ifs("dict.txt");
        while ( ifs >> D[DC] )
            DC ++;
    }

    bool check_valid( int cur, int di ) {
        string a = s.substr(cur, 10);
        string b = D[di];
        if ( a.size() < b.size() )
            return false;
        int n = min(a.size(), b.size());
        for ( int i = 0; i < n; ++ i ) {
            if ( a[i] != b[i] ) {
                for ( int j = 1; j < 5; ++ j ) {
                    if ( a[i + j] != b[i + j] )
                        return false;
                }
            }
        }
        return true;
    }

    int get_changes( int cur, int di ) {
        string a = s.substr(cur, 10);
        string b = D[di];
        int res = 0;
        int n = b.size();
        for ( int i = 0; i < n; ++ i )
            if ( a[i] != b[i] )
                res ++;
        return res;
    }

    // s[cur...]
    int get_min( int cur, int changes ) {
        if ( cur >= n ) {
            smallest = min(smallest, changes);
            return changes;
        }
        int res = INF;
        for ( int i = 0; i < DC; ++ i ) {
            if ( check_valid(cur, i) ) {
                int next_changes = changes + get_changes(cur, i);
                if ( next_changes < smallest )
                    res = min(res, get_min(cur + D[i].size(), next_changes));
            }
        }
        return res;
    }

    int solve() {
        smallest = INF;
        n = s.size();
        return get_min(0, 0);
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


