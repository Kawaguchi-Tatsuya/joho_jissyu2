//
//	情報処理実習2　授業用サンプルソースファイル
//
//

#include <stdio.h>

//	各種定数．これらを変更するとどうなるか検討すること
// 例えば，
// (1) ゲイン Kp を変えてみよう．
// (2) 制御周期 dt を，系の時定数 T より長くしてみよう．

const double Kp = 1.5;    // gain
const double dt = 10;  // 制御周期(s)

const double SV = 25.0;  // 目標値Set valiable. 例えばエアコンの設定温度など．
const double T = 300;    // 系の時定数(s)

const double T_end = 1000;   // シミュレーション終了時刻(s)

double MVn(const double PVn1)
{
	return Kp * (SV - PVn1);
}

double PVn(const double MVn, const double PVn1)
//	1次遅れ系のモデル
{
	return (T/(T+dt))*PVn1 + (dt/(T+dt))*MVn;
}

int main()
{
	//	確認のため画面に表示．これを改造して
	//	出力先をファイルに変更すること．
	//	グローバル変数の各種パラメータもファイルに記録しておくと良い．

	double PVn_current=0;  // 現在のPV（室温など）初期値をここで設定．
	double PVn1 = PVn_current;	// previous PV, i.e., PVn-1

	printf("SV= %lf, PV0=%lf\n\n", SV, PVn1);
	printf("t(s),PVn\n\n");

	double t = 0.0;   // 時刻(s)
	double MV = 0;    // 操作量

	do {
		printf("%lf, %lf\n", t, PVn_current);

		MV = MVn(PVn1);		//	操作量の決定
		PVn_current = PVn(MV, PVn1);   // PV を計測
		PVn1 = PVn_current;

		t += dt;

	} while(t <= T_end);
	return 0;
}
