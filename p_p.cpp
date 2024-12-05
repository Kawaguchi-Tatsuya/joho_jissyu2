/*
	P制御 位置型アルゴリズム
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

const int XCN=61;
const int YCN=21;


int main(void)
{
	int i, j;
	int ic[XCN][YCN];	/*グラフ用文字*/
	
	int ct=1;
	int cv=0;
	
	double e[2];
	double sig_e;	/*偏差積分値位置型アルゴリズム用*/
	double PV, MV, SV;
	double MV0;
	
	double T = 2.0;	/*時定数*/
	double dt = 0.1;	/*時間刻み*/
	double SimT = 10.0;/*シミュレーション時間*/
	double Kp = 3.0;	/*比例ゲイン*/

	PV=0.0;		/*応答初期値*/
	MV=0.0;		/*操作量初期値*/
	MV0=0.0;	/*操作量初期値位置型アルゴリズム用*/
	SV=1.0;		/*指令値*/

	for(i=0;i<2;i++){	/*偏差初期化*/
		e[i]=0.0;
	}

	for(j=0;j<YCN;j++){
		for(i=0;i<XCN;i++){
			ic[i][j]=0;
		}
	}

	for(j=0;j<YCN;j++)
		ic[0][j]=1;	     /*y軸*/
	for(i=0;i<XCN;i++)
		ic[i][20]=2;	/*時間軸*/

	printf("# SV=%lf\n", SV);
	printf("# i,PV\n");

	for(i=0;i<(SimT/dt);i++){	/*制御ループ*/

		e[0]=e[1];				/*位置型アルゴリズム用*/
		e[1]=SV-PV;				/*位置型アルゴリズム用*/
		sig_e=sig_e+e[1];		/*偏差積分値位置型アルゴリズム用*/
		
		MV = Kp * e[1] + MV0;	/*Pによる操作量位置型アルゴリズム用*/
		
		PV = PV*T/(T+dt) + MV*dt/(T+dt);	/*一次遅れの演算*/

		printf("%d %lf\n",i ,PV);


		if(i >= ct*(SimT/dt/(double)XCN)){
						
			if(SV<PV){
				for(cv=1; cv < YCN; cv++){
					if(PV <= (double)cv*SV*1.2/((double)YCN)){
						ic[ct][YCN-cv]=3;
						break;
					}
				}

				for(cv=1; cv < YCN; cv++){
					if(SV <= (double)cv*SV*1.2/((double)YCN)){
						ic[ct][YCN-cv]=4;
						ct++;
						break;
					}
				}
			}
			
			else if(SV>PV){
				for(cv=1; cv < YCN; cv++){
					if(SV <= (double)cv*SV*1.2/((double)YCN)){
						ic[ct][YCN-cv]=4;
						break;
					}
				}
				for(cv=1; cv < YCN; cv++){
					if(PV <= (double)cv*SV*1.2/((double)YCN)){
						ic[ct][YCN-cv]=3;
						ct++;
						break;
					}
				}
			}
			else ic[ct][YCN-cv]=4;
			
			
		}

	}

	for(j=0;j<YCN;j++){
		printf("\n");
		for(i=0;i<XCN;i++){
			switch(ic[i][j]){
				case 0:	printf(" ");
						break;
				case 1:	printf("|");
						break;
				case 2:	printf("-");
						break;
				case 3:	printf("*");
						break;
				case 4:	printf("+");
						break;
			}
			
		}
	}
	printf("\n");
	
	return 0;
}
