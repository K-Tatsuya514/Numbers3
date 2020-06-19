#pragma warning(disable: 4996) //これを書くことでfopenを使えるようにしている
#include <stdio.h>

#define N 3
#define M 10

void sort(double RankP[N][M], int RankN[N][M]){
	int i, j, k,tmpN;
	double tmpP;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			for (k = j + 1; k < M; k++) {
				if (RankP[i][j] < RankP[i][k]) {
					tmpP = RankP[i][j];
					RankP[i][j] = RankP[i][k];
					RankP[i][k] = tmpP;
					tmpN = RankN[i][j];
					RankN[i][j] = RankN[i][k];
					RankN[i][k] = tmpN;
				}
			}
		}
	}
}
void sort2(double RankP[M], int RankN[M]) {
	int j, k, tmpN;
	double tmpP;
		for (j = 0; j < M; j++) {
			for (k = j + 1; k < M; k++) {
				if (RankP[j] < RankP[k]) {
					tmpP = RankP[j];
					RankP[j] = RankP[k];
					RankP[k] = tmpP;
					tmpN = RankN[j];
					RankN[j] = RankN[k];
					RankN[k] = tmpN;
				}
			}
		}
}

int main(void) {
	int i,j;



//ファイルの読み込み配列に格納
	FILE * fp;
	int NUM3[1000];
	fp = fopen("Book2.csv", "r");
	if (fp == NULL) {
		printf("ファイルオープン失敗");
		return -1;
	}
	int n=0;
	while (!feof(fp) && n < 512) {
		fscanf(fp, "%d", &(NUM3[n]));
		n++;
	}
	fclose(fp);
	n--;
	for (i = 0; i < n; i++) {
		printf("%d : %d\n",i+1, NUM3[i]);
	}
	printf("%d\n", n);
//配列に格納完了


//それぞれの位に分けて二次元配列に格納
	int num3[1000][N];
	int hand, ten, one;
	for (i = 0; i < n; i++) {
		hand = NUM3[i] / 100;
		ten = (NUM3[i] - hand * 100) / 10;
		one = (NUM3[i] - hand * 100 - ten * 10);
		num3[i][0] = hand;
		num3[i][1] = ten;
		num3[i][2] = one;
	}
	//for (i = 0; i < n; i++) {
	//	for (j = 0; j < 3; j++) {
	//		printf("%d", num3[i][j]);
	//	}
	//	printf("\n");
	//}
//それぞれの位に分けて二次元配列に格納完了


//それぞれの位の確率を表示
	int sum[N][M] = { 0 }; //N位の数字Mの個数
	int totalsum[M] = { 0 }; //全部の位の数字Mの個数
	int now;
	for (i = 0; i < n; i++) {
		for (j = 0; j < 3; j++) {
			now = num3[i][j];
			sum[j][now]++;
			totalsum[now]++;
		}
	}

	double NN;
	NN = n;

	double P[N][M]; //各位の各数字の確率
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			P[i][j] = sum[i][j]*100 / NN;
			printf("NUM[%d][%d]=%d  P[%d][%d]=%f%%\n", i, j, sum[i][j], i, j, P[i][j]);
		}
		printf("\n");
	}

	double totalP[M]; //全部の位の各数字の確率
	for (i = 0; i < M; i++) {
		totalP[i] = totalsum[i] * 100 / (NN * 3);
		printf("%dの全体確立：%f%%\n", i, totalP[i]);
	}printf("\n");


	double RankP[N][M] = { 0 }; //Nの位置の数字MのパーセンテージがRankP
	int RankN[N][M] = { 0 }; //RankPの数字がRnakN
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			RankP[i][j] = P[i][j];
			RankN[i][j] = j;
		}
	}
	sort(RankP, RankN);
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			printf("%d位：数字 = %d, %f%%\n", j+1, RankN[i][j], RankP[i][j]);
		}
		printf("\n");
	}

	double RanktotalP[M] = { 0 };
	int RanktotalN[M] = { 0 };
	for (i = 0; i < M; i++) {
		RanktotalP[i] = totalP[i];
		RanktotalN[i] = i;
	}
	sort2(RanktotalP, RanktotalN);
	for (i = 0; i < M; i++) {
		printf("合計%d位： %d = %f%%\n", i + 1, RanktotalN[i], RanktotalP[i]);
	}
//それぞれの位の確率を表示完了


	return 0;
}