//
//  情報処理実習2　最小二乗法課題用テンプレート
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void draw_graph(
    const double x[],
    const double y[],
    const int N,
    const double a,
    const double b
)
//
//  gnuplot を呼び出して，散布図(x,y) および 直線 y=ax+b を描画する関数
//
{
    //  gnuplot の実行ファイルのパスを正しく設定しないと動作しない！
    const char gp_cmd[] = "\"C:/Program Files/gnuplot/bin/gnuplot\" -persist";   // for windows(情報処理教室)
//    const char gp_cmd[] = " /usr/local/bin/gnuplot -persist";   // for Mac(一例．)

    FILE *fp;
    fp = popen(gp_cmd, "w");
    if(fp == NULL) {
        printf("popen() error");
        exit(1);
    }

    fprintf(fp, "set title 'Spring rate measurement and least square fitting'\n");
    fprintf(fp, "set xrange [0 : 10.0]\n");        // x 軸の値の範囲
    fprintf(fp, "set yrange [0 : 20.0]\n");        // y 軸の値の範囲
    fprintf(fp, "set xlabel '{/Arial:Italic x}[mm]'\n");  // x 軸ラベル
    fprintf(fp, "set ylabel '{/Arial:Italic y}[N]'\n");  // y 軸ラベル

    // フォントの変更
    fprintf(fp, "set title font 'Arial, 20'\n"); // タイトル
    fprintf(fp, "set xlabel font 'Arial,16'\n"); // 横軸ラベル
    fprintf(fp, "set ylabel font 'Arial,16'\n"); // 縦軸ラベル
    fprintf(fp, "set key font 'Arial, 12'\n"); // 凡例
    fprintf(fp, "set tics font 'Arial, 12'\n"); // 目盛


    //  plotコマンド用文字列バッファ
    char buf[200];
    snprintf(buf, 200, "plot (%lf*x+%lf) linecolor black title 'least square'", a, b);  // 文字列bufに変数の値をセット
    strcat(buf, ", '-' with points pt 7 linecolor black title 'measured data'\n");
    fprintf(fp, buf);   //  gnuplotにplotコマンドを書き出す

    //  散布図の座標値を書き出す
    int i;
    for(int i=0; i<N; i++) {
        fprintf(fp,"%f\t%f\n", x[i], y[i]);    // データの書き込み
    }  

    fprintf(fp, "e\n");

    fflush(fp);
    pclose(fp);
}


int main(void)
{ 
    //  計測されたデータ
    const int N = 10;
    double x[N]={0, 1.1, 2.1, 3.0, 3.9, 5.0,  5.9,  7.1,  7.8, 8.9};
    double y[N]={0, 2.4, 4.2, 5.7, 8.2, 9.2, 11.9, 14.0, 16.2, 17.4};
    
    //  y = ax + b 
    //  このa,b の値は仮の設定！
    double a = 1.2;
    double b = 2.5;


    //  *** ここで最小二乗法により a, b を計算 ***


    // gnuplotでグラフを描く
    draw_graph(x, y, N, a, b);

    return 0;
}

