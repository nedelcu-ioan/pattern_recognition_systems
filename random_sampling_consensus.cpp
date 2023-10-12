
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <opencv2/opencv.hpp>
#include <random>
typedef long long ll;

using namespace std;
using namespace __gnu_pbds;
using namespace cv;

const int MOD = 1e9 + 7;

#define FOR(i, j, k) for(int i = j; i < k; ++i)
#define FORI(i, n) for (int i = 0; i < n; ++i)
#define FORD(i, n) for (int i = n - 1; i >= 0; --i)
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define all(x) (x).begin(),(x).end()
#define eni(x) sim > typename \
enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

signed main(int argc, char **argv, char **envp) {
    // p1
    //cout << argc << endl;
    if (argc == 2) {
        freopen(argv[1], "r", stdin);
    }

    vector<pair<float, float>> points; // points

    Mat img = imread(argv[1], IMREAD_GRAYSCALE);
    
    const int nn = (int)img.rows;
    const int mm = (int)img.cols;

    for (int i = 0 ; i < nn ; ++i){
        for (int j = 0 ; j < mm ; ++j) {
            if (img.at<uchar>(i, j) != 255) {
                points.push_back({(float)j, (float)i});
            }
        }
    }

    float n = (float)points.size();
    float t = 10.0, p = 0.99, q = 0.3, s = 2;
    float N = log(1 - p) / log(1 - pow(q ,s));
    float T = q * n;

    debug() << imie(n) << imie(q) << imie(p) << imie(s);
    debug() << imie(T) << imie(N);
    debug() << imie(points);

    random_device rd;
    default_random_engine gen(rd());
    uniform_int_distribution<int> distribution(0, n - 1);

    // test random
    debug() << imie("test random numbers");
    for (int i = 0 ; i < 10; ++i) {
        debug() << imie(distribution(gen));
    }

    int iter_index = 1;             // current iteration index
    int best_valid_count = -1;      // best count so far 
    float a, b, c;                  // line params 
    int best_p1;
    int best_p2;

    while (true) {
        int p1 = distribution(gen);
        int p2 = distribution(gen);
    
        debug() << imie(p1) << imie(p2) << imie(iter_index);

        while (p2 == p1) {
            p2 = distribution(gen);
        }

        auto x = points[p1];
        auto y = points[p2];
        
        float c_a = x.second - y.second;
        float c_b = y.first - x.first;
        float c_c = x.first * y.second - x.second * y.first;

        debug() << imie(c_a) << imie(c_b) << imie(c_c);

        int current_count = 0;
        for (int i = 0 ; i < (int)points.size() ; ++i) {
            if (i == p1 || i == p2) {
                continue;
            }
            float dist = 
                fabs(
                        c_a * points[i].first 
                        + c_b * points[i].second + c_c
                ) / sqrt(c_a * c_a + c_b * c_b);
            if (dist <= t) {
                ++current_count;
            }
        }
        debug() << imie(current_count);
        if (current_count > best_valid_count) {
            a = c_a;
            b = c_b;
            c = c_c;
            best_p1 = p1;
            best_p2 = p2;
            best_valid_count = current_count;
        }
        if (iter_index == (int)N) {
            break;
        }
        ++iter_index;
    }

    debug() << imie(a) << imie(b) << imie(c);
    
    debug() << imie(points[best_p1]) << imie(points[best_p2]);

    line(
            img, 
            Point(points[best_p1].first, points[best_p1].second),
            Point(points[best_p2].first, points[best_p2].second),
            0
    );

    debug() << imie("Scriem rezultatul");
    imwrite("ans.bmp", img);

    return 0x0;
}
