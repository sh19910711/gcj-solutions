
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

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/graphviz.hpp>

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
    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS> Graph;

    const int MAX_BOXES = 211;
    const int MAX_KEYS = 411;

    int init_keys[MAX_KEYS];
    int init_keys_count;
    int key_types[MAX_KEYS];
    int key_open_boxes[MAX_KEYS][MAX_BOXES];
    int key_open_boxes_count[MAX_KEYS];
    int key_count;
    int box_count;
    int box_key_types[MAX_BOXES];
    int box_keys[MAX_BOXES][MAX_KEYS];
    int box_key_ids[MAX_BOXES][MAX_KEYS];
    int box_keys_count[MAX_BOXES];
    bool b2b[MAX_BOXES][MAX_BOXES];
    bool k2k[MAX_KEYS][MAX_KEYS];
    Map box_order;
    Map key_order;

    void global_init() {
        for ( int i = 0; i < MAX_KEYS; ++ i )
            key_open_boxes_count[i] = 0;
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

    int add_key( int key_type ) {
        key_types[key_count] = key_type;
        return key_count ++;
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
                cin >> box_key_types[i] >> box_keys_count[i];
                for ( int j = 0; j < box_keys_count[i]; ++ j ) {
                    cin >> box_keys[i][j];
                }
            }
            return true;
        }

        bool solve() {
            // 鍵を登録する
            for ( int i = 0; i < init_keys_count; ++ i ) {
                add_key(init_keys[i]);
            }
            for ( int i = 0; i < box_count; ++ i ) {
                for ( int j = 0; j < box_keys_count[i]; ++ j ) {
                    box_key_ids[i][j] = add_key(box_keys[i][j]);
                }
            }

            // 鍵ごとに開くことができる箱を計算する
            for ( int i = 0; i < key_count; ++ i ) {
                int key_type = key_types[i];
                for ( int j = 0; j < box_count; ++ j ) {
                    int box_key_type = box_key_types[j];
                    if ( key_type == box_key_type ) {
                        key_open_boxes[i][key_open_boxes_count[i] ++] = j;
                    }
                }
            }
            
            // ある箱fromについて、fromに含まれる鍵で開くことができる箱toがあればb2b[from][to]をtrueにする
            // ワーシャルフロイド法でb2bの間接的な参照になっている部分を接続する
            for ( int from = 0; from < box_count; ++ from ) {
                for ( int i = 0; i < box_keys_count[from]; ++ i ) {
                    int key = box_key_ids[from][i];
                    for ( int j = 0; j < key_open_boxes_count[key]; ++ j ) {
                        int to = key_open_boxes[key][j];
                        if ( from == to )
                            continue;
                        b2b[from][to] = true;
                    }
                }
            }
            for ( int k = 0; k < box_count; ++ k ) {
                for ( int i = 0; i < box_count; ++ i ) {
                    for ( int j = 0; j < box_count; ++ j ) {
                        if ( b2b[i][k] && b2b[k][j] )
                            b2b[i][j] = true;
                    }
                }
            }
            
            // ある鍵fromについて、fromで開くことができる箱に含まれる鍵toがあればk2k[from][to]をtrueにする
            // ワーシャルフロイド法でk2kの間接的な参照になっている部分を接続する
            for ( int from = 0; from < key_count; ++ from ) {
                for ( int i = 0; i < key_open_boxes_count[from]; ++ i ) {
                    int box = key_open_boxes[from][i];
                    for ( int j = 0; j < box_keys_count[box]; ++ j ) {
                        int to = box_key_ids[box][j];
                        if ( from == to )
                            continue;
                        k2k[from][to] = true;
                    }
                }
            }
            for ( int k = 0; k < key_count; ++ k ) {
                for ( int i = 0; i < key_count; ++ i ) {
                    for ( int j = 0; j < key_count; ++ j ) {
                        if ( k2k[i][k] && k2k[k][j] )
                            k2k[i][j] = true;
                    }
                }
            }
            
            // b2b, k2kについてトポロジカルソートを行い、その結果をbox_order, key_orderに格納する（変形が必要）
            // トポロジカルソートが失敗した場合はIMPOSSIBLE
            {
                // b2b
                Graph G(key_count);
                for ( int i = 0; i < key_count; ++ i )
                    for ( int j = 0; j < key_count; ++ j )
                        if ( b2b[i][j] )
                            boost::add_edge(i, j, G);
                VI order;
                boost::topological_sort(G, back_inserter(order));
                reverse(order.begin(), order.end());
                int index = 0;
                for ( VI::iterator it_i = order.begin(); it_i != order.end(); ++ it_i ) {
                    box_order[*it_i] = index ++;
                }
            }
            {
                // k2k
                Graph G(key_count);
                for ( int i = 0; i < key_count; ++ i )
                    for ( int j = 0; j < key_count; ++ j )
                        if ( k2k[i][j] )
                            boost::add_edge(i, j, G);
                VI order;
                boost::topological_sort(G, back_inserter(order));
                reverse(order.begin(), order.end());
                int index = 0;
                for ( VI::iterator it_i = order.begin(); it_i != order.end(); ++ it_i ) {
                    key_order[*it_i] = index ++;
                }
            }
            
            // Weight(key_id, box_id) = box_count - box_order[box_id]
            // で表される二部グラフGを生成して最大マッチングを求める
        }

        void output( int test_no, bool result ) {
            cout << "Case #" << test_no << ": ";
            if ( result ) {
                cout << "hoge";
            } else {
                cout << "IMPOSSIBLE";
            }
            cout << endl;
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


