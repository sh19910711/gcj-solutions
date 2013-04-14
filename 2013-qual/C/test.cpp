#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

typedef ostringstream OSS;
typedef istringstream ISS;
typedef long long LL;

string to_string( LL x ) {
    OSS oss;
    oss << x;
    return oss.str();
}

long long to_int( string s ) {
    ISS iss(s);
    long long res;
    iss >> res;
    return res;
}

bool is_number( long double x ) {
    return ceil(x) - floor(x) < 1e-9;
}

bool is_parindromic( LL x ) {
    string s = to_string(x);
    string rs = s;
    reverse( rs.begin(), rs.end() );
    return s == rs;
}

int main() {
    LL a = 12345678987654321LL;
    cout << a << ": " << (LL)sqrt(a) << endl;
    return 0;

    srand((unsigned int)time(NULL));
    for ( LL i = 0; i < 1000000000LL; ++ i ) {
        int k = rand() % 10000000;
        string left = to_string(k);
        string right = left;
        reverse(right.begin(), right.end());
        for ( char c = '0'; c <= '9'; ++ c ) {
            string tmp = left + c + right;
            LL num = to_int(tmp);
            long double a = sqrt(num);
            if ( is_number(a) && is_parindromic((LL)a) ) {
                cout << tmp << " <= " << a << endl;
                return 0;
            }
        }
    }
    return 0;
}

