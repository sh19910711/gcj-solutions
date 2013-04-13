
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

#define REP(i,n) for(int i=0;i<(int)n;++i)
#define FOR(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)
#define ALL(c) (c).begin(), (c).end()

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
    typedef int Weight;
    struct Edge {
        int src, dst;
        Weight weight;
        Edge(int src, int dst, Weight weight) :
            src(src), dst(dst), weight(weight) { }
    };
    bool operator < (const Edge &e, const Edge &f) {
        return e.weight != f.weight ? e.weight > f.weight : // !!INVERSE!!
            e.src != f.src ? e.src < f.src : e.dst < f.dst;
    }
    typedef vector<Edge> Edges;
    typedef vector<Edges> Graph;

    typedef vector<Weight> Array;
    typedef vector<Array> Matrix;

    const int SIZE = 211;
    int init_keys_num, N;
    VI init_keys;
    Set init_keys_set;
    int T[SIZE], KC[SIZE];
    VI K[SIZE];
    Set KS[SIZE];
    map<int, int> KSC[SIZE];
    bool G[SIZE][SIZE];
    int A[SIZE][SIZE];
    int AC[SIZE];
    map <int, VI> group_by_key;
    int R[SIZE];
    int CNT[SIZE];

    void add_edge( int from, int to ) {
        G[from][to] = true;
        A[from][AC[from]++] = to;
    }
    
    namespace SCC {
        void visit(const Graph &g, int v, vector< vector<int> >& scc,
                stack<int> &S, vector<bool> &inS,
                vector<int> &low, vector<int> &num, int& time) {
            low[v] = num[v] = ++time;
            S.push(v); inS[v] = true;
            FOR(e, g[v]) {
                int w = e->dst;
                if (num[w] == 0) {
                    visit(g, w, scc, S, inS, low, num, time);
                    low[v] = min(low[v], low[w]);
                } else if (inS[w])
                    low[v] = min(low[v], num[w]);
            }
            if (low[v] == num[v]) {
                scc.push_back(vector<int>());
                while (1) {
                    int w = S.top(); S.pop(); inS[w] = false;
                    scc.back().push_back(w);
                    if (v == w) break;
                }
            }
        }
        void stronglyConnectedComponents(const Graph& g,
                vector< vector<int> >& scc) {
            const int n = g.size();
            vector<int> num(n), low(n);
            stack<int> S;
            vector<bool> inS(n);
            int time = 0;
            REP(u, n) if (num[u] == 0)
                visit(g, u, scc, S, inS, low, num, time);
        }
    }

    namespace TOP {
        bool visit(const Graph &g, int v, vector<int> &order, vector<int> &color) {
            color[v] = 1;
            // cout << "@visit: v = " << v << endl;
            FOR(e, g[v]) {
                // cout << "edges = " << g[v].size() << endl;
                // cout << "from = " << v << ", to = " << e->dst << endl;
                if (color[e->dst] == 2) continue;
                if (color[e->dst] == 1) continue;
                if (!visit(g, e->dst, order, color)) return false;
            }
            order.push_back(v); color[v] = 2;
            return true;
        }
        bool topologicalSort(const Graph &g, vector<int> &order) {
            int n = g.size();
            vector<int> color(n);
            REP(u, n) if (!color[u] && !visit(g, u, order, color))
                return false;
            reverse(ALL(order));
            return true;
        }
    };

    class Solution: public ISolution {
    public:
        void init() {
            init_keys.clear();
            init_keys_set.clear();
            for ( int i = 0; i < SIZE; ++ i )
                K[i].clear();
            for ( int i = 0; i < SIZE; ++ i )
                KS[i].clear();
            for ( int i = 0; i < SIZE; ++ i )
                KSC[i].clear();
            for ( int i = 0; i < SIZE; ++ i )
                for ( int j = 0; j < SIZE; ++ j )
                    G[i][j] = false;
            for ( int i = 0; i < SIZE; ++ i )
                AC[i] = 0;
            group_by_key.clear();
            for ( int i = 0; i < SIZE; ++ i )
                CNT[i] = 0;
        }

        bool input() {
            cin >> init_keys_num >> N;
            for ( int i = 0; i < init_keys_num; ++ i ) {
                int tmp;
                cin >> tmp;
                init_keys.push_back(tmp);
                init_keys_set.insert(tmp);
            }
            for ( int i = 1; i <= N; ++ i ) {
                cin >> T[i] >> KC[i];
                for ( int j = 0; j < KC[i]; ++ j ) {
                    int tmp;
                    cin >> tmp;
                    K[i].push_back(tmp);
                    KS[i].insert(tmp);
                    KSC[i][tmp] ++;
                }
            }
            return true;
        }

        // 鍵ごとにグループを作成する
        void grouping() {
            for ( int i = 1; i <= N; ++ i )
                group_by_key[T[i]].push_back(i);
        }

        void generate_graph() {
            // 持っている鍵のリストから、その鍵を使用する箱へ辺を結ぶ
            for ( Set::iterator it_i = init_keys_set.begin(); it_i != init_keys_set.end(); ++ it_i ) {
                VI& list = group_by_key[*it_i];
                for ( VI::iterator it_j = list.begin(); it_j != list.end(); ++ it_j ) {
                    add_edge(0, *it_j);
                }
            }
            for ( int i = 1; i <= N; ++ i ) {
                for ( Set::iterator it_i = KS[i].begin(); it_i != KS[i].end(); ++ it_i ) {
                    int key = *it_i;
                    VI& list = group_by_key[key];
                    for ( VI::iterator it_j = list.begin(); it_j != list.end(); ++ it_j ) {
                        if ( i != *it_j ) {
                            add_edge(i, *it_j);
                        }
                    }
                }
            }
        }

        bool check_order( int k ) {
            if ( k >= N )
                return true;
            int from = R[k];
            int needed_key = T[from];
            if ( CNT[needed_key] > 0 ) {
                CNT[needed_key] --;
                for ( Set::iterator it_i = KS[from].begin(); it_i != KS[from].end(); ++ it_i )
                    CNT[*it_i] += KSC[from][*it_i];
                return check_order(k+1);
            } else {
                return false;
            }
            return false;
        }

        bool solve() {
            grouping();
            generate_graph();

            Graph graph(N+1, Edges());
            for ( int i = 0; i <= N; ++ i ) {
                sort( A[i], A[i] + AC[i], greater<int>() );
                for ( int j = 0; j < AC[i]; ++ j ) {
                    // cout << i << " -> " << A[i][j] << endl;
                    graph[i].push_back(Edge(i, A[i][j], 1));
                }
            }

            VI order;
            bool ret = TOP::topologicalSort(graph, order);
            if ( ! ret )
                return false;
            for ( int i = 0; i < N; ++ i ) {
                R[i] = order[i+1];
            }
            for ( int i = 0; i < init_keys_num; ++ i )
                CNT[init_keys[i]] ++;
            return check_order(0);
        }

        void output( int test_no, bool result ) {
            if ( result ) {
                cout << "Case #" << test_no << ": ";
                for ( int i = 0; i < N; ++ i ) {
                    cout << R[i];
                    if ( i + 1 < N )
                        cout << " ";
                }
                cout << endl;
            } else {
                cout << "Case #" << test_no << ": IMPOSSIBLE" << endl;
            }
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


