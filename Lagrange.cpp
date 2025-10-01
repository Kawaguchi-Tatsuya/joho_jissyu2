#include <stdio.h>

struct Point2D
{
    double x;
    double y;
};

const int N = 5;   /* データ個数 */

double Lagrange(const Point2D pnt[], const double x)
/*
 * ラグランジ補間関数
 * pnt   : 点群を表す配列
 * x     : 求めたい x の値（点群以外の任意の値でもOK）
 * 戻り値 : xに対応する関数の値 y = f(x)
 */
{
    int i,j;
    /* 計算用変数の初期化 */
    double p, s = 0.0;

    for (i = 0; i < N; i++) {

        p = pnt[i].y;   /* 積の計算 */

        for (j=0; j<N; j++) {
            if (i != j) {
                p *= (x - pnt[j].x) / (pnt[i].x - pnt[j].x);
            }
        }
        s += p;
    }
    return s;
}

int main(void)
{
	Point2D points[N] =
			{{-2.0, 0.0},
			 {-1.0, 0.3},
			 { 0.0, 1.0},
			 { 1.0, 0.3},
			 { 2.0, 0.0} };
	
	//	以下は一例．xにたいするyの値を求める．
	double x = 0.25;
	double y = Lagrange(points, x);
	
	printf("%lf , %lf\n", x, y);
	
	return 0;
}


