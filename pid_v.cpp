/*
	PID制御 速度型アルゴリズム
*/

#include <stdio.h>

int main(void)
{
	/* ASCIIグラフ用のキャンバスサイズ */
	const int XCN = 61;
	const int YCN = 21;
	int ic[XCN][YCN];	/* グラフ用数値配列．0=" ", 1="|", 2="-", 3="*", 4="+" を表示 */

	/* 計算用変数 */
	int ct = 1;
	int cv = 0;
	
	const int Ne = 3;   /* 偏差の配列サイズ */	
	double e[Ne];        /* 偏差，三時刻分を記憶する配列 */
	double sig_e;       /* 偏差積分値位置型アルゴリズム用 */

	//	定数パラメータ
	double T = 2.0;     /* 時定数(sec) */
	double dt = 0.1;    /* 時間刻み(sec) */
	double SimT = 10.0; /* シミュレーション時間(sec) */

	//	PIDパラメータ
	double Kp = 2.0;    /* 比例ゲイン */
	double Ti = 0.8;    /* 積分時間 */
	double Td = 0.05;   /* 微分時間 */


	double PV = 0.0;    /* 応答初期値 */
	double MV = 0.0;    /* 操作量初期値 */
	double SV = 1.0;    /* 指令値 */

	int i, j;

	for(i=0; i<Ne; i++) { /* 偏差を初期化 */
		e[i] = 0.0;
	}

	for(j=0; j<YCN; j++) {
		for(i=0; i<XCN; i++){
			ic[i][j] = 0;      /* キャンバスを0で初期化 */
		}
	}

	printf("# SV = %lf\n", SV);
	printf("# i, PV\n");

	for(i=0; i<(SimT/dt); i++) {	/* 制御ループ */

		e[0] = e[1];     /* 2つ前の制御周期における e */
		e[1] = e[2];     /* 1つ前の制御周期における e */
		e[2] = SV - PV;  /* 現周期の e */

		/* PIDによる操作量 MV の変化量 ΔMV を計算 */
		double dMV = Kp * ( (e[2]-e[1])         /* 比例動作 */
							+ (e[2]/Ti) * dt    /* 積分動作 */
							+ Td * (e[2] - 2.0*e[1] + e[0]) / dt ); /* 微分動作 */

		MV = MV + dMV;        /* 今の周期の操作量 */

		PV = PV * T/(T+dt) + MV * dt/(T+dt);   /* 一次遅れの演算 */

		printf("%d, %lf\n",i ,PV);

		if(i >= ct*(SimT/dt/(double)XCN) ) {
			
			
			if ( SV < PV ) {
				for( cv = 1; cv < YCN; cv++) {
					if(PV <= (double)cv * SV * 1.2/((double)YCN) ){
						ic[ct][YCN-cv] = 3;
						break;
					}
				}

				for(cv=1; cv < YCN; cv++ ) {
					if(SV <= (double)cv * SV * 1.2/((double)YCN)){
						ic[ct][YCN-cv] = 4;
						ct++;
						break;
					}
				}
			}
			
			else if(SV > PV ) {
				for(cv=1; cv < YCN; cv++) {
					if(SV <= (double)cv * SV * 1.2/((double)YCN)){
						ic[ct][YCN-cv] = 4;
						break;
					}
				}
				for(cv=1; cv < YCN; cv++){
					if(PV <= (double)cv * SV * 1.2 / ((double)YCN)){
						ic[ct][YCN-cv] = 3;
						ct++;
						break;
					}
				}
			}
			
			else ic[ct][YCN-cv]=4;
			
			
		}

	}

	/* 以下，テキスト図形を描画 */
	/* stderr を stdout に変更すると，リダイレクトでファイル保存可能 */
	fprintf(stderr, "---------------------------- ascii graph ----------------------------------\n");
	for(j=0; j<YCN; j++)
		ic[0][j]=1;	    /* 縦軸：y軸 */

	for(i=0; i<XCN; i++)
		ic[i][20]=2;	/* 横軸：時間軸 */

	for(j=0; j < YCN; j++) {
		fprintf(stderr, "\n");
		for(i=0; i<XCN; i++) {

			switch(ic[i][j]) {
				case 0:	fprintf(stderr, " ");
						break;
				case 1:	fprintf(stderr, "|");
						break;
				case 2:	fprintf(stderr, "-");
						break;
				case 3:	fprintf(stderr, "*");
						break;
				case 4:	fprintf(stderr, "+");
						break;
			}	
		}
	}
	fprintf(stderr, "\n");
	
	return 0;
}
