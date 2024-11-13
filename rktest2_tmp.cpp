// rktest2_tmp.cpp
//
// 情報処理実習授業用
// 2階の常微分方程式のRunge-Kutta法の計算サンプルコードのテンプレート
// このソースコードは未完成であるので，必要に応じて加筆すること．
// 各種定数も正しく設定すること．
//
#include <stdio.h>
#include <math.h>

const double cm = ???;
const double km = ???;
const double um = ???;
    
double f(double t, double x, double z)
{
    // ここに方程式を記述
}
double g(double t, double x, double z)
{
    // ここに方程式を記述
}

int main(void)
{
    // 計算中に使用する定数はまとめて宣言しておくと見やすい．
    const double t_beg = 0.0;    // 開始時刻(s)
    const double t_end = 500.0;  // 終了時刻(s)
    const double x0 = ???;       // 位置 x [m] の初期値
    const double z0 = ???;       // 速度 x'[m/s] の初期値．変数zとおく． 

    const double h = ???;    //  時間刻み(s)

    double t, x;           // 計算用変数
    double z;              // 計算用変数 z = x'

    ///////////////////////////////////
    //
    // 計算開始
    //
    ///////////////////////////////////

    //  初期値の設定．これによって解が変わる
    t = t_beg;
    x = x0;
    z = z0;

    double k0, k1, k2, k3, k;  //  計算用変数
    double l0, l1, l2, l3, l;  //  計算用変数

    // 初期状態を表示
    printf("t , x\n");
    printf("%lf,  %lf\n", t, x);

    // Runge-Kutta法による積分．
    do {

        k0 = f(t,     x,        z       );
        l0 = g(t,     x,        z       );
        k1 = f(t+h/2, x+k0*h/2, z+l0*h/2);
        l1 = g(t+h/2, x+k0*h/2, z+l0*h/2);
        k2 = f(t+h/2, x+k1*h/2, z+l1*h/2);
        l2 = g(t+h/2, x+k1*h/2, z+l1*h/2);
        k3 = f(t+h,   x+k2*h,   z+l2*h  );
        l3 = g(t+h,   x+k2*h,   z+l2*h  );

        k = h/6.0 * (k0 + 2*k1 + 2*k2 + k3);
        l = h/6.0 * (l0 + 2*l1 + 2*l2 + l3);

        t = t + h;
        x = x + k;
        z = z + l;

        printf("%lf,  %lf\n", t, x);

    } while(t <= t_end);    //  計算終了時刻の判定

    return 0;
}
