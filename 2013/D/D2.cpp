
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

    typedef map <int, int> Map;
    typedef set <int> Set;

    const int MAX_BOXES = 211;
    const int MAX_KEYS = 411;

    int init_keys[MAX_KEYS];
    int init_keys_count;
    int key_type[MAX_KEYS];
    int key_count;
    int box_count;
    int box_key_type[MAX_BOXES];
    int box_keys[MAX_BOXES][MAX_KEYS];
    int box_keys_count[MAX_BOXES];
    bool b2b[MAX_BOXES][MAX_BOXES];
    bool k2k[MAX_KEYS][MAX_KEYS];
    Map box_order;
    Map key_order;

    void global_init() {
        key_count = 0;
        for ( int i = 0; i < MAX_BOXES; ++ i )
            box_keys_count[i] = 0;
        for ( int i = 0; i < MAX_BOXES; ++ i )
            for ( int j = 0; j < MAX_BOXES; ++ j )
                b2b[i][j] = false;
        for ( int i = 0; i < MAX_KEYS; ++ i )
            for ( int j = 0; j < MAX_KEYS; ++ j )
                k2k[i][j] = false;
        box_order.clear();
        key_order.clear();
    }

    class Solution: public ISolution {
    public:
        void init() {
            global_init();
        }

        bool input() {
            cin >> init_keys_count >> box_count;
            for ( int i = 0; i < init_keys_count; ++ i )
                cin >> init_keys[i];
            for ( int i = 0; i < box_count; ++ i ) {
                cin >> box_key_type[i] >> box_keys_count[i];
                for ( int j = 0; j < box_keys_count[i]; ++ j ) {
                    cin >> box_keys[i][j];
                }
            }
            return true;
        }

        void solve() {
            // 鍵を登録する
            //
            // 鍵ごとに開くことができる箱を計算する
            //
            // ある箱fromについて、fromに含まれる鍵で開くことができる箱toがあればb2b[from][to]をtrueにする
            // ワーシャルフロイド法でb2bの間接的な参照になっている部分を接続する
            // 
            // ある鍵fromについて、fromで開くことができる箱に含まれる鍵toがあればk2k[from][to]をtrueにする
            // ワーシャルフロイド法でk2kの間接的な参照になっている部分を接続する
            //
            // b2b, k2kについてトポロジカルソートを行い、その結果をbox_order, key_orderに格納する（変形が必要）
            // トポロジカルソートが失敗した場合はIMPOSSIBLE
            //
            // Weight(key_id, box_id) = box_count - box_order[box_id]
            // で表される二部グラフGを生成して最大マッチングを求める
        }

        int run() {
            int tests;
            std::cin >> tests;
            for ( int i = 0; i < tests; ++ i ) {
                init();
                input();
                solve();
                output();
            }
            return 0;
        }
    };
    
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}


