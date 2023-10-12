
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <opencv2/opencv.hpp>

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

void write_image(vector<pair<float, float>> &points) {
    Mat img(500, 500, CV_8UC3);
    int dx = 250;
    int dy = 250;
    const int n = (int)points.size();
    for (int i = 0 ; i < n; ++i) {
        int x = (int)points[i].first;// + dx;
        int y = (int)points[i].second;// + dy;
        if (x >= 0 && x < 500 && y >= 0 && y < 500) {
            img.at<Vec3b>(y, x)[1] = 255;  
        }
    }
    imwrite("show.bmp", img);
}

void metod_1(vector<pair<float, float>> & points) {
    float theta_0 = 0.f;
    float theta_1 = 0.f;
    const int n = (int)points.size();

    /// compute theta_1 
    float sum_x = 0.f;
    float sum_y = 0.f;
    
    float ssum_x = 0.f;
    for (int i = 0 ; i < n ; ++i) {
        theta_1 += points[i].second * points[i].first;
        sum_x += points[i].first;
        sum_y += points[i].second;
        ssum_x += points[i].first * points[i].first;
    }
    theta_1 *= n;
    theta_1 -= sum_x * sum_y;
    theta_1 /= ((float)n * ssum_x - sum_x * sum_x); 

    theta_0 = 1.f / (float)n;
    theta_0 *= sum_y - theta_1 * sum_x;
    
    debug() << imie(theta_0) << imie(theta_1);
    
    Mat img = imread("show.bmp", IMREAD_COLOR);
    
    line(img, Point(0, theta_0), Point(500, theta_0 + 500 * theta_1), Scalar(0,0,255));
    imwrite("show_1.bmp", img);
}

void metod_2(vector<pair<float, float>> & points) {
    const int n = (int)points.size();
    float sum_x = 0.f;
    float sum_y = 0.f;
    float sum_xyi = 0.f;
    float sum_xx_m_yy = 0.f;

    
    for (int i = 0 ; i < n ; ++i) {
        float x = points[i].first;
        float y = points[i].second;

        sum_x += x;
        sum_y += y;
        sum_xyi += x * y;
        sum_xx_m_yy += - x*x + y*y;
    }
    
    float beta = -0.5 * atan2(
            + 2.0 * sum_xyi 
            - 2.0 / ((float)n) * sum_x * sum_y,

            sum_xx_m_yy 
            + 1.0 / ((float)n) * sum_x * sum_x 
            - 1.0 / ((float)n) * sum_y * sum_y
    );
   
    float ro = 1.0f / ((float)n) * (
              cos(beta) * sum_x 
            + sin(beta) * sum_y
            );
    
    Mat img = imread("show.bmp", IMREAD_COLOR);

    line(
            img, 
            Point(0, ro / sin(beta)), 
            Point(500, (ro - 500 * cos(beta)) / sin(beta)),
            Scalar(255, 0, 0)
    );

    
    imwrite("show_2.bmp", img);
}

signed main(int argc, char **argv, char **envp) {
    // p1
    //cout << argc << endl;
    if (argc == 2) {
        freopen(argv[1], "r", stdin);
    }
    int n; // number of points
    vector<pair<float, float>> points; // points

    cin >> n;
    debug() << imie(n);
    //cout << "Ceva";
    for (int i = 0; i < n; ++i) {
        float x, y;
        cin >> x >> y;
        points.push_back(make_pair(x, y));
    }

    // p2 
    write_image(points);
    
    // metod_1
    metod_1(points);
    // metod_2
    metod_2(points);
    return 0x0;
}
