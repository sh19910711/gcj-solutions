
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

    typedef set<int> Set;
    const int SIZE = 111;
    const int INF = std::numeric_limits<int>::max();
    const string YES = "YES";
    const string NO = "NO";
    int H, W;
    int A[SIZE][SIZE];
    int B[SIZE][SIZE];
    bool F[SIZE][SIZE];
    Set S;

    class Solution: public ISolution {
    public:

        void init() {
            S.clear();
            for ( int i = 0; i < SIZE; ++ i )
                for ( int j = 0; j < SIZE; ++ j )
                    F[i][j] = false;
        }

        bool input() {
            cin >> H >> W;
            for ( int i = 0; i < H; ++ i )
                for ( int j = 0; j < W; ++ j )
                    cin >> A[i][j];
            return true;
        }

        bool exist_top_or_left( int v ) {
            for ( int i = 0; i < W; ++ i )
                if ( A[0][i] == v )
                    return true;
            for ( int i = 0; i < H; ++ i )
                if ( A[i][0] == v )
                    return true;
            return false;
        }

        bool check_column( int k, int v ) {
            for ( int i = 0; i < H; ++ i ) {
                if ( A[i][k] != v )
                    return false;
            }
            return true;
        }

        void fill_column( int k, int v ) {
            for ( int i = 0; i < H; ++ i ) {
                B[i][k] = v + 1;
                F[i][k] = true;
            }
        }

        bool check_row( int k, int v ) {
            for ( int i = 0; i < W; ++ i ) {
                if ( A[k][i] != v )
                    return false;
            }
            return true;
        }

        void fill_row( int k, int v ) {
            for ( int i = 0; i < W; ++ i ) {
                B[k][i] = v + 1;
                F[k][i] = true;
            }
        }

        void copy_a_to_b() {
            for ( int i = 0; i < H; ++ i )
                for ( int j = 0; j < W; ++ j )
                    B[i][j] = A[i][j];
        }

        void copy_b_to_a() {
            for ( int i = 0; i < H; ++ i )
                for ( int j = 0; j < W; ++ j )
                    A[i][j] = B[i][j];
        }

        bool solve() {
            for ( int v = 1; v < 101; ++ v ) {
                copy_a_to_b();
                for ( int i = 0; i < W; ++ i ) {
                    if ( A[0][i] == v ) {
                        if ( ! check_column(i, v) )
                            continue;
                        fill_column(i, v);
                    }
                }
                for ( int i = 0; i < H; ++ i ) {
                    if ( A[i][0] == v ) {
                        if ( ! check_row(i, v) )
                            continue;
                        fill_row(i, v);
                    }
                }
                copy_b_to_a();
            }
            for ( int i = 0; i < H; ++ i )
                for ( int j = 0; j < W; ++ j )
                    if ( ! F[i][j] )
                        return false;
            return true;
        }

        void output( int test_no, bool result ) {
            cout << "Case #" << test_no << ": " << ( result ? YES : NO ) << endl;
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


