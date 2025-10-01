#include <stdio.h>
#include <stdlib.h>

struct Point2D
{
    double x;
    double y;
};


double spline(const Point2D pnt[], const int N, const double x)
/*
 * スプライン補間関数
 * pnt   : 点群を表す配列
 * N     : pnt のサイズ＝データ個数
 * x     : 求めたい x の値（点群以外の任意の値でもOK）
 * 戻り値 : xに対応する関数の値 y = f(x)
 */
{
	int idx = -1, k;

	double *h, *b, *d, *g, *u, *r;
	h = (double*)malloc(sizeof(double)*(N-1));
	b = (double*)malloc(sizeof(double)*(N-1));
	d = (double*)malloc(sizeof(double)*(N-1));
	g = (double*)malloc(sizeof(double)*(N-1));
	u = (double*)malloc(sizeof(double)*(N-1));
	r = (double*)malloc(sizeof(double)*(N  ));

	int i;
	for (i=1; i<N-1 && idx<0; i++) {
		if (x < pnt[i].x )
			idx = i - 1;
	}
	
	if (idx < 0)
		idx = N-2;
	
	for(i=0; i<N-1; i++) {
		h[i] = pnt[i+1].x - pnt[i].x;
	}

	for (i=1; i<N-1; i++) {
		b[i] = 2.0 * (h[i] + h[i-1]);
		d[i] = 3.0 * ((pnt[i+1].y - pnt[i  ].y) / h[i  ] 
					- (pnt[i  ].y - pnt[i-1].y) / h[i-1]);
	}

	g[1] = h[1] / b[1];

	for (i=2; i<N-2; i++) {
		g[i] = h[i] / (b[i] - h[i-1] * g[i-1]);
	}

	u[1] = d[1] / b[1];

	for(i=2; i<N-1; i++) {
		u[i] = (d[i]-h[i-1] * u[i-1]) / (b[i] - h[i-1] * g[i-1]);
	}
	
	if(idx > 1) {
		k = idx;
	} else {
		k = 1;
	}

	r[0]   = 0.0;
	r[N-1] = 0.0;
	r[N-2] = u[N-2];
	
	for (i=N-3; i>=k; i--) {
		r[i] = u[i] - g[i] * r[i+1];
	}

	double dx = x - pnt[idx].x;
	double q = (pnt[idx+1].y - pnt[idx].y) / h[idx] - h[idx] * (r[idx+1] + 2.0 * r[idx]) / 3.0;
	double s = (r[idx+1] - r[idx]) / (3.0 * h[idx]);
	
	free(h);
	free(b);
	free(d);
	free(g);
	free(u);

	//	動的配列中の値を戻り値として使用する場合は，開放する前に別のローカル変数にコピー
	double r_ret = r[idx];
	free(r);

	return pnt[idx].y + dx * (q + dx * (r_ret  + s * dx));
}


int main(void)
{
	const int N = 5;   /* データ個数 */

	Point2D points[N] =
			{{-2.0, 0.0},
			 {-1.0, 0.3},
			 { 0.0, 1.0},
			 { 1.0, 0.3},
			 { 2.0, 0.0} };
		
	//	以下は一例．xにたいするyの値を求める．
	double x = 0.25;
	double y = spline(points, N, x);
	
	printf("%lf , %lf\n", x, y);
	
	return 0;
}


