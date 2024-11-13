//
// 情報処理実習授業用
// Runge-Kutta法の計算サンプルコードのテンプレート
// このソースコードは未完成であるので，必要に応じて加筆すること．
// 各種定数も正しく設定すること．
//
#include <stdio.h>
#include <math.h>

double func(double t, double x)
//  df/dt = f(t,x)なる方程式をここに書く．
//  以下は一例
{
    return 2*t;  // 解析解は t*t+1
//  return x;    // 解析解は exp(t)
//  return sin(t);  // 解析解は -cos(t)
}


int main(void)
{
    // 計算中に使用する定数はまとめて宣言しておくと見やすい．
    const double t_beg = 0.0;   // 開始時刻
    const double t_end = 2.0;   // 終了時刻
    const double x0 = 1.0;      // xの初期値

    const double h = 0.1;    //  時間刻み

    double t, x;           //  計算用変数

    ///////////////////////////////////
    //
    // 計算開始
    //
    ///////////////////////////////////

    //  初期値の設定．これによって解が変わる
    t = t_beg;
    x = x0;

    double k0, k1, k2, k3, k;  //  計算用変数

    // 初期状態を表示
    printf("t , x\n");
    printf("%lf,  %lf\n", t, x);

    // Runge-Kutta法による積分．
    do {  //  たまにはdo-while文を使用

        k0 = func(t,     x);
        k1 = func(t+h/2, x+k0*h/2);
        k2 = func(t+h/2, x+k1*h/2);
        k3 = func(t+h,   x+k2*h);

        k = h/6.0 * (k0 + 2*k1 + 2*k2 + k3);

        x = x + k;
        t = t + h;

        printf("%lf,  %lf\n", t, x);

    } while(t <= t_end);    //  計算終了時刻の判定

    return 0;
}
