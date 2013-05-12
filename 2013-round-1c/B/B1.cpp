
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

    const int SIZE = 201;
    const int MOVE_MAX = 501;
    int sx, sy;
    int gx, gy;
    II P[MOVE_MAX][SIZE][SIZE];
    bool V[MOVE_MAX][SIZE][SIZE];

    int moves;

    typedef pair <int, II> Node;
    typedef queue <Node> Queue;

    const int dr[4] = {0, 0, 1, -1};
    const int dc[4] = {1, -1, 0, 0};
    const II NONE(-1, -1);

    Queue Q;
    
    void bfs() {
        for ( int i = 0; i < MOVE_MAX; ++ i )
            for ( int r = 0; r < SIZE; ++ r )
                for ( int c = 0; c < SIZE; ++ c )
                    V[i][r][c] = false;
        Q.push(Node(0, II(sx, sy)));
        V[0][sx][sy] = true;
        P[0][sx][sy] = NONE;

        while ( ! Q.empty() ) {
            Node node = Q.front();
            Q.pop();
            int x = node.second.first;
            int y = node.second.second;
            int s = node.first;

            if ( x == gx && y == gy ) {
                moves = s;
                return;
            }

            for ( int i = 0; i < 4; ++ i ) {
                int ns = s + 1;
                int nx = x + dr[i] * ns;
                int ny = y + dc[i] * ns;
                if ( nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE )
                    continue;
                if ( ns > 500 )
                    continue;
                if ( V[ns][nx][ny] )
                    continue;
                V[ns][nx][ny] = true;
                P[ns][nx][ny] = II(x, y);
                Q.push(Node(ns, II(nx, ny)));
            }
        }

        cout << "@bfs: none" << endl;
    }

    string get_result_string() {
        string res;
        int s = moves;
        int x = gx, y = gy;
        while ( true ) {
            II np = P[s][x][y];
            int nx = np.first;
            int ny = np.second;

            if ( abs(nx - x) != 0 ) {
                if ( nx - x > 0 ) {
                    res += 'W';
                } else {
                    res += 'E';
                }
            } else {
                if ( ny - y > 0 ) {
                    res += 'S';
                } else {
                    res += 'N';
                }
            }

            x = nx;
            y = ny;
            s --;
            if ( s == 0 )
                break;
        }
        reverse(res.begin(), res.end());
        return res;
    }

    string solve() {
        sx = 0;
        sy = 0;
        sx += 100;
        sy += 100;
        gx += 100;
        gy += 100;
        bfs();
        return get_result_string();
    }

    class Solution: public ISolution {
    public:

        bool input() {
            return cin >> gx >> gy;
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


