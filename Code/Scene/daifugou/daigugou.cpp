///* daifugo.c */
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include"DxLib.h"
//#include"CP_Player.h"
//#include"./../Code/GetKey.h"
//#include"daifugou.h"
//
//
//#pragma warning(disable : 4996)
//struct player {
//	char name[20]; /* 名前 */
//	int hand[15]; /* 手札 */
//	int fin; /* 終了 */
//	int pass; /* パス */
//};
//
//struct player data[4] = {
//{"あなた",0,0,0},
//{"NP1" ,0,0,0},
//{"NP2" ,0,0,0},
//{"NP3" ,0,0,0},
//};
//
//
//int cards[54]; /* 山札 */
//int order[4]; /* 誰から始めるか */
//int trash[15] = { 0 }; /* ﾄﾗｯｼｭ */
//int produce[2][15]; /* 出す手札 */
//int rev = 0; /* 革命 */
//int eback = 0; /* 11バック */
//int pc = -1; /* 最後に誰が出したかカウント */
//char mark[5] = { 'C','D','S','H','J' };/* トランプのマーク */
//
//
//void CP::onesec(void) {
//	time_t t1;
//	srand(time(NULL));
//
//	t1 = time(NULL);
//	while (1 != time(NULL) - t1);
//}
//
//int str(int str_x) {
//	/* カードの強さ */
//	int x;
//
//	if (eback + rev == 0 || eback + rev == 2)
//		x = (str_x + 10) % 13;
//	else
//		x = 12 - ((str_x + 10) % 13);
//
//	if (str_x == 53 || str_x == 54)
//		x = 13;
//
//	return x;
//}
//
//int num(int num_x) {
//	/* カードの数字 */
//	int x;
//
//	x = (num_x - 1) % 13 + 1;
//	return x;
//}
//
//int mar(int mar_x) {
//	/* カードのマーク */
//	char x;
//
//	x = mark[(mar_x - 1) / 13];
//	return x;
//}
//int com(int com_x, int com_y) {
//	/* カードの強さを比較 */
//
//	if (str(com_x) == str(com_y))
//		return 0;
//	else if (str(com_x) < str(com_y))
//		return 1;
//	else
//		return 2;
//}
//
//void sort(int sort_x, int* sort_y, int sort_z) {
//	/* ソート用関数 */
//	int i, j, x;
//
//	for (i = sort_x; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			/* カードの強さ順にソート 強さが同じ場合、マーク順にソート */
//			if (com(*(sort_y + j), *(sort_y + j + 1)) == 2 || com(*(sort_y + j), *(sort_y + j + 1)) == 0 && *(sort_y + j) > *(sort_y + j + 1)) {
//
//				x = *(sort_y + j);
//				*(sort_y + j) = *(sort_y + j + 1);
//				*(sort_y + j + 1) = x;
//
//				/* produceをソートする場合 */
//				if (sort_z == 1) {
//					x = produce[0][j];
//					produce[0][j] = produce[0][j + 1];
//					produce[0][j + 1] = x;
//				}
//
//			}
//		}
//	}
//}
//
//void CP::title(void) {
//	printf("\n\n");
//	printf("　大　　富　　豪　\n");
//	onesec();
//	printf("[ルール]\n");
//	printf("・8切り,11バック　\n");
//	printf("・2枚出し～6枚出し(JK含め),革命　\n");
//	printf("・8,JK,2(革命中は3)であがると反則　\n");
//	printf("・一度パスしたらそのターンは出せない　\n");
//	onesec();
//	printf("%sの名前を入力 : ", data[0].name);
//	scanf_s("%s", data[0].name);
//}
//
//void CP::deckmake(void) {
//	/* 山札作成 */
//	int i;
//	for (i = 0; i <= 53; i++)
//		cards[i] = i + 1;
//}
//
//void CP::datareset(void) {
//
//	data[0].fin = data[1].fin = data[2].fin = data[3].fin = 0;
//	data[0].pass = data[1].pass = data[2].pass = data[3].pass = 0;
//	pc = -1;
//
//}
//void CP::deckshuffle(void) {
//	/* 山札をシャッフル */
//	int i, x, y, z;
//	for (i = 0; i < 500; i++) {
//		x = rand() % 54;
//		y = rand() % 54;
//		z = cards[x];
//		cards[x] = cards[y];
//		cards[y] = z;
//	}
//	onesec();
//	printf("山札をシャッフルしました\n");
//}
//
//void CP::dealcards(void) {
//	/* 手札を配る */
//	int i, j;
//
//	j = rand() % 4; /* 誰から配るか */
//	for (i = 0; i <= 53; i++, j++) {
//		if (j == 4)
//			j = 0; /* data[3]の次はdata[0]に */
//
//		data[j].hand[0]++; /* 枚数を+1 */
//		data[j].hand[data[j].hand[0]] = *cards;
//	}
//	/* 全員の手札を強さ順にソート */
//	sort(data[0].hand[0], data[0].hand, 0);
//	sort(data[1].hand[0], data[1].hand, 0);
//	sort(data[2].hand[0], data[2].hand, 0);
//	sort(data[3].hand[0], data[3].hand, 0);
//
//	onesec();
//	printf("手札を配りました\n");
//}
//
//void CP::d3start(void) {
//	/* ダイヤの３からスタート */
//	int i, j;
//
//	for (i = 1, j = 0; i < 5; j++) {
//		if (j == 4) {
//			j = 0;
//			i++;
//		}
//		if (*data[j].hand == 16) /* ダイヤの３のカード番号は16 */
//			break;
//	}
//
//	order[0] = j;
//	for (i = 1, j = j + 1; i <= 3; i++, j++) {
//		if (j == 4)
//			j = 0;
//		order[i] = j;
//	}
//
//	onesec();
//	printf("ダイヤの３を持ってる人からスタートします\n");
//}
//
//void CP::phase(int n) {
//	/* ターンが回ってくる前に行う動作 */
//
//	/* 自分がトラッシュに出したカードが換わらずに1週してきたら */
//	if (n == pc) {
//		onesec();
//		printf("場が流れました\n\n");
//		pc = -1;
//		eback = 0; /* 11バックをリセット */
//		trash[0] = 0; /* ﾄﾗｯｼｭをリセット */
//		data[0].pass = data[1].pass = data[2].pass = data[3].pass = 0; /* パスをリセット */
//	}
//}
//
//void CP::status(int n) {
//	/* プレイヤー用の場を表示させる関数 */
//	int i;
//
//	onesec();
//	/* トラッシュを表示 */
//	if (trash[0] == 0) /* ﾄﾗｯｼｭが空だった場合 */
//		printf("[場] 空\n");
//
//	else { /* ﾄﾗｯｼｭにｶｰﾄﾞがあった場合 */
//		printf("[場]");
//		for (i = 1; i <= trash[0]; i++) {
//
//			if (mar(*trash) != 'J')
//				printf(" %c%2d ", mar(*trash), num(*trash));
//			else
//				printf(" %c ", mar(*trash));
//		}
//		printf("\n");
//	}
//
//	/* 手札を表示 */
//	for (i = 1; i <= data[n].hand[0]; i++)
//		printf("[%3d]", i);
//	printf("\n");
//
//	for (i = 1; i <= data[n].hand[0]; i++) {
//
//		/* ジョーカーだった場合 数字を非表示 */
//		if (mar(*data[n].hand) != 'J')
//			printf(" %c%2d ", mar(*data[n].hand), num(data[n].hand[i]));
//		else
//			printf(" %c ", mar(data[n].hand[i]));
//	}
//	printf("\n");
//	printf("あなたの番です\n");
//}
//int judg(int n) {
//
//	int i, j;
//
//	/* 中身をproduce[1][]にコピー */
//	produce[1][0] = produce[0][0];
//	for (i = 1; i <= produce[0][0]; i++)
//		produce[1][i] = data[n].hand[produce[0][i]];
//
//	/* produceをソート */
//	sort(produce[1][0], produce[1], 1);
//
//	void CP::onesec(void) {
//		/* 1秒表示 */
//		time_t t1;
//		srand(time(NULL));
//
//		t1 = time(NULL);
//		while (1 != time(NULL) - t1);
//	}
//
//int str(int str_x) {
//	/* カードの強さ */
//	int x;
//
//	if (eback + rev == 0 || eback + rev == 2)
//		x = (str_x + 10) % 13;
//	else
//		x = 12 - ((str_x + 10) % 13);
//
//	if (str_x == 53 || str_x == 54)
//		x = 13;
//
//	return x;
//}
//
//int num(int num_x) {
//	/* カードの数字 */
//	int x;
//
//	x = (num_x - 1) % 13 + 1;
//	return x;
//}
//
//int mar(int mar_x) {
//	/* カードのマーク */
//	char x;
//
//	x = mark[(mar_x - 1) / 13];
//	return x;
//}
//int com(int com_x, int com_y) {
//	/* カードの強さを比較 */
//
//	if (str(com_x) == str(com_y))
//		return 0;
//	else if (str(com_x) < str(com_y))
//		return 1;
//	else
//		return 2;
//}
//
//void CP::sort(int sort_x, int* sort_y, int sort_z) {
//	/* ソート用関数 */
//	int i, j, x;
//
//	for (i = sort_x; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			/* カードの強さ順にソート 強さが同じ場合、マーク順にソート */
//			if (com(*(sort_y + j), *(sort_y + j + 1)) == 2 || com(*(sort_y + j), *(sort_y + j + 1)) == 0 && *(sort_y + j) > *(sort_y + j + 1)) {
//
//				x = *(sort_y + j);
//				*(sort_y + j) = *(sort_y + j + 1);
//				*(sort_y + j + 1) = x;
//
//				/* produceをソートする場合 */
//				if (sort_z == 1) {
//					x = produce[0][j];
//					produce[0][j] = produce[0][j + 1];
//					produce[0][j + 1] = x;
//				}
//
//			}
//		}
//	}
//}
//
//void title(void) {
//	printf("\n\n");
//	printf("　大　　富　　豪　\n");
//	onesec();
//	printf("[ルール]\n");
//	printf("・8切り,11バック　\n");
//	printf("・2枚出し～6枚出し(JK含め),革命　\n");
//	printf("・8,JK,2(革命中は3)であがると反則　\n");
//	printf("・一度パスしたらそのターンは出せない　\n");
//	onesec();
//	printf("%sの名前を入力 : ", data[0].name);
//	scanf("%s", data[0].name);
//}
//
//void CP::deckmake(void) {
//	/* 山札作成 */
//	int i;
//	for (i = 0; i <= 53; i++)
//		cards = i + 1;
//}
//
//void CP::datareset(void) {
//
//	data[0].fin = data[1].fin = data[2].fin = data[3].fin = 0;
//	data[0].pass = data[1].pass = data[2].pass = data[3].pass = 0;
//	pc = -1;
//
//}
//void CP::deckshuffle(void) {
//	/* 山札をシャッフル */
//	int i, x, y, z;
//	for (i = 0; i < 500; i++) {
//		x = rand() % 54;
//		y = rand() % 54;
//		z = cards[x];
//		cards[x] = cards[y];
//		cards[y] = z;
//	}
//	onesec();
//	printf("山札をシャッフルしました\n");
//}
//
//void CP::dealcards(void) {
//	/* 手札を配る */
//	int i, j;
//
//	j = rand() % 4; /* 誰から配るか */
//	for (i = 0; i <= 53; i++, j++) {
//		if (j == 4)
//			j = 0; /* data[3]の次はdata[0]に */
//
//		data[j].hand[0]++; /* 枚数を+1 */
//		data[j].hand[data[j].hand[0]] = cards;
//	}
//	/* 全員の手札を強さ順にソート */
//	sort(data[0].hand[0], data[0].hand, 0);
//	sort(data[1].hand[0], data[1].hand, 0);
//	sort(data[2].hand[0], data[2].hand, 0);
//	sort(data[3].hand[0], data[3].hand, 0);
//
//	onesec();
//	printf("手札を配りました\n");
//}
//
//void Cp::d3start(void) {
//	/* ダイヤの３からスタート */
//	int i, j;
//
//	for (i = 1, j = 0; i < 5; j++) {
//		if (j == 4) {
//			j = 0;
//			i++;
//		}
//		if (data[j].hand == 16) /* ダイヤの３のカード番号は16 */
//			break;
//	}
//
//	order[0] = j;
//	for (i = 1, j = j + 1; i <= 3; i++, j++) {
//		if (j == 4)
//			j = 0;
//		order = j;
//	}
//
//	onesec();
//	printf("ダイヤの３を持ってる人からスタートします\n");
//}
//
//void CP::phase(int n) {
//	/* ターンが回ってくる前に行う動作 */
//
//	/* 自分がトラッシュに出したカードが換わらずに1週してきたら */
//	if (n == pc) {
//		onesec();
//		printf("場が流れました\n\n");
//		pc = -1;
//		eback = 0; /* 11バックをリセット */
//		trash[0] = 0; /* ﾄﾗｯｼｭをリセット */
//		data[0].pass = data[1].pass = data[2].pass = data[3].pass = 0; /* パスをリセット */
//	}
//}
//
//void CP::status(int n) {
//	/* プレイヤー用の場を表示させる関数 */
//	int i;
//
//	onesec();
//	/* トラッシュを表示 */
//	if (trash[0] == 0) /* ﾄﾗｯｼｭが空だった場合 */
//		printf("[場] 空\n");
//
//	else { /* ﾄﾗｯｼｭにｶｰﾄﾞがあった場合 */
//		printf("[場]");
//		for (i = 1; i <= trash[0]; i++) {
//
//			if (mar(trash) != 'J')
//				printf(" %c%2d ", mar(trash), num(trash));
//			else
//				printf(" %c ", mar(trash));
//		}
//		printf("\n");
//	}
//
//	/* 手札を表示 */
//	for (i = 1; i <= data[n].hand[0]; i++)
//		printf("[%3d]", i);
//	printf("\n");
//
//	for (i = 1; i <= data[n].hand[0]; i++) {
//
//		/* ジョーカーだった場合 数字を非表示 */
//		if (mar(data[n].hand) != 'J')
//			printf(" %c%2d ", mar(data[n].hand), num(data[n].hand[i]));
//		else
//			printf(" %c ", mar(data[n].hand[i]));
//	}
//	printf("\n");
//	printf("あなたの番です\n");
//}
//int judg(int n) {
//
//	int i, j;
//
//	/* 中身をproduce[1][]にコピー */
//	produce[1][0] = produce[0][0];
//	for (i = 1; i <= produce[0][0]; i++)
//		produce[1][i] = data[n].hand[produce[0][i]];
//
//	/* produceをソート */
//	sort(produce[1][0], produce[1], 1);
//
//
//
//	/* ========judgのメイン処理======== */
//
//	/* 選択範囲内でカードを出しているか */
//	for (i = 1; i <= produce[0][0]; i++) {
//		if (0 > produce[0][i] || produce[0][i] > data[n].hand[0])
//			return 0;
//	}
//
//	/* 同じカードを出していないか */
//	for (i = produce[0][0]; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			if (produce[0][j] == produce[0][j + 1])
//				return 0;
//		}
//	}
//
//	/* 場にカードがある場合、同じ枚数を出しているか */
//	if (trash[0] != 0 && trash[0] != produce[0][0])
//		return 0;
//
//	/* 同じ数字のカードか */
//	for (i = produce[0][0]; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			if (num(produce[1][j]) != num(produce[1][j + 1]) && mar(produce[1][j]) != 'J' && mar(produce[1][j + 1]) != 'J')
//				return 0;
//		}
//	}
//
//	/* 場に何かある場合、現在の場より強いカードか */
//	if (trash[0] != 0 && com(trash[1], produce[1][1]) != 1)
//		return 0;
//
//	return 1;
//}
//void CP::arrange(int n) {
//	int i, j;
//
//	/* ﾄﾗｯｼｭに選択したｶｰﾄﾞをいれる */
//	trash[0] = produce[0][0];
//	for (i = 1; i <= trash[0]; i++)
//		trash[i] = produce[1][i];
//
//	/* 枚数を減らし手札をつめる */
//	for (i = 1; i <= trash[0]; i++) {
//		j = 1;
//		while (1) {
//			if (trash[i] == data[n].hand[j]) {
//				while (j < data[n].hand[0]) {
//					data[n].hand[j] = data[n].hand[j + 1];
//					j++;
//				}
//				break;
//			}
//			j++;
//		}
//	}
//
//	data[n].hand[0] = data[n].hand[0] - produce[0][0];
//}
//void CP::print(int n) {
//	int i;
//
//	/* ジョーカーだった場合 数字を非表示 */
//	printf("→%sは", data[n].name);
//	for (i = 1; i <= trash[0]; i++) {
//		if (mar(trash[i]) == 'J')
//			printf(" %c ", mar(trash[i]));
//		else
//			printf("%c%2d", mar(trash[i]), num(trash[i]));
//		if (i != trash[0])
//			printf("と");
//	}
//	printf("を出しました 残り%d枚です\n", data[n].hand[0]);
//}
//void CP::revolution(void) {
//	/* 革命 */
//
//	if (trash[0] >= 4 && rev == 0) {
//		printf("革命が起こりました\n");
//		rev = 1;
//	}
//	else if (trash[0] >= 4 && rev == 1) {
//		printf("革命が返されました\n");
//		rev = 0;
//	}
//}
//void CP::elevenback(void) {
//	/* 11が出た場合 */
//	int i;
//
//	for (i = 1; i <= trash[0]; i++) {
//		if (num(trash[i]) == 11) {
//			eback = 1;
//			printf("イレブンバックしました\n");
//			break;
//		}
//	}
//}
//void CP::pl_routine(int n) {
//	/* プレイヤー用 */
//	int i;
//
//	status(n);
//
//	/* 0で決定、選択しているカードが真か関数judgに送る */
//	while (1) {
//
//		/* 入力処理 */
//		produce[0][0] = 0;
//		i = 1;
//		while (1) {
//			printf("%2d枚目のカード : ", i);
//			scanf("%d", &produce[0][i]);
//			if (produce[0][i] == 0)
//				break;
//			produce[0][0]++;
//			i++;
//		}
//		/* 初めから0が入力されたら */
//		if (produce[0][0] == 0) {
//			printf("→%sはパスしました\n", data[n].name);
//			data[n].pass++;
//			break;
//		}
//		/* 入力が終わったらjudgで判定 */
//		if (judg(n) == 1) {
//			arrange(n);
//			pc = n; /* 最後に出した人を記憶 */
//			print(n);
//			revolution();
//			elevenback();
//			break;
//		}
//		printf("カードが不正でした。もう一度選んでください。\n");
//	}
//}
//void CP::cp_routine(int n) {
//	/* コンピュータの考え方 */
//	int i, j;
//
//	onesec();
//	/* */
//	if (trash[0] == 0) {
//		produce[0][0] = 6;
//		while (1) {
//			for (i = 0; i < 10; i++) {
//
//				for (j = 1; j <= produce[0][0]; j++)
//					produce[0][j] = (rand() % data[n].hand[0]) + 1;
//
//				if (judg(n) == 1) {
//					arrange(n);
//					pc = n;
//					print(n);
//					revolution();
//					elevenback();
//					break;
//				}
//			}
//			if (pc == n)
//				break;
//
//			if (produce[0][0] == 1) {
//				printf("→%sはパスしました\n", data[n].name);
//				data[n].pass++;
//				break;
//			}
//			produce[0][0]--;
//		}
//	}
//	else {
//		produce[0][0] = trash[0];
//		for (i = 0; i < 20; i++) {
//
//			for (j = 1; j <= produce[0][0]; j++)
//				produce[0][j] = (rand() % data[n].hand[0]) + 1;
//
//			if (judg(n) == 1) {
//				arrange(n);
//				pc = n;
//				print(n);
//				revolution();
//				elevenback();
//				break;
//			}
//		}
//		if (pc != n) {
//			printf("→%sはパスしました\n", data[n].name);
//			data[n].pass++;
//		}
//	}
//}
//void CP::expend(int n) {
//	/* 手札がなくなった場合 */
//	int i;
//
//	if (data[n].hand[0] == 0) {
//		onesec();
//		data[n].fin = 1;
//		for (i = 1; i <= trash[0]; i++) {
//			if (num(trash[i]) == 8 || eback == 0 && str(trash[i]) == 12 || mar(trash[i]) == 'J') {
//				printf("%sは反則あがりました\n", data[n].name);
//				break;
//			}
//			if (i == trash[0])
//				printf("%sはあがりました\n", data[n].name);
//		}
//	}
//}
//void CP::slash8(int n) {
//	/* 8切り */
//	int i;
//
//	for (i = 1; i <= trash[0]; i++) {
//		if (num(trash[i]) == 8) {
//			pc = n;
//			data[0].pass = data[1].pass = data[2].pass = data[3].pass = 1;
//			data[n].pass = 0;
//			break;
//		}
//	}
//}
//void CP::turn(int n) {
//
//	phase(n);
//
//	if (data[n].fin == 0 && data[n].pass == 0) {
//
//		if (n == 0)
//			pl_routine(n);
//		else
//			cp_routine(n);
//
//		expend(n);
//		slash8(n);
//	}
//}
//void CP::main(void) {
//
//	int i = 0;
//	srand(time(NULL));
//
//
//	title();
//	deckmake();
//
//	while (1) {
//
//		datareset();
//		deckshuffle();
//		dealcards();
//		d3start();
//
//		i++;
//
//		printf("\n==========第%d回戦スタート！==========\n\n", i);
//		while (1) {
//
//			turn(order[0]);
//
//			if (data[0].fin + data[1].fin + data[2].fin + data[3].fin == 3)
//				break;
//
//			turn(order[1]);
//
//			if (data[0].fin + data[1].fin + data[2].fin + data[3].fin == 3)
//				break;
//
//			turn(order[2]);
//
//			if (data[0].fin + data[1].fin + data[2].fin + data[3].fin == 3)
//				break;
//
//			turn(order[3]);
//
//			if (data[0].fin + data[1].fin + data[2].fin + data[3].fin == 3)
//				break;
//
//		}
//		printf("\n\n\n==========第%d回戦終了！==========\n", i);
//
//
//	}
//}
//	for (i = 1; i <= produce[0][0]; i++) {
//		if (0 > produce[0][i] || produce[0][i] > data[n].hand[0])
//			return 0;
//	}
//
//	/* 同じカードを出していないか */
//	for (i = produce[0][0]; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			if (produce[0][j] == produce[0][j + 1])
//				return 0;
//		}
//	}
//
//	/* 場にカードがある場合、同じ枚数を出しているか */
//	if (trash[0] != 0 && trash[0] != produce[0][0])
//		return 0;
//
//	/* 同じ数字のカードか */
//	for (i = produce[0][0]; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			if (num(produce[1][j]) != num(produce[1][j + 1]) && mar(produce[1][j]) != 'J' && mar(produce[1][j + 1]) != 'J')
//				return 0;
//		}
//	}
//
//	/* 場に何かある場合、現在の場より強いカードか */
//	if (trash[0] != 0 && com(trash[1], produce[1][1]) != 1)
//		return 0;
//
//	return 1;
//}
//void CP::arrange(int n) {
//	int i, j;
//
//	/* ﾄﾗｯｼｭに選択したｶｰﾄﾞをいれる */
//	trash[0] = produce[0][0];
//	for (i = 1; i <= trash[0]; i++)
//		trash[i] = produce[1][i];
//
//	/* 枚数を減らし手札をつめる */
//	for (i = 1; i <= trash[0]; i++) {
//		j = 1;
//		while (1) {
//			if (trash[i] == data[n].hand[j]) {
//				while (j < data[n].hand[0]) {
//					data[n].hand[j] = data[n].hand[j + 1];
//					j++;
//				}
//				break;
//			}
//			j++;
//		}
//	}
//
//	data[n].hand[0] = data[n].hand[0] - produce[0][0];
//}
//void CP::print(int n) {
//	int i;
//
//	/* ジョーカーだった場合 数字を非表示 */
//	printf("→%sは", data[n].name);
//	for (i = 1; i <= trash[0]; i++) {
//		if (mar(trash[i]) == 'J')
//			printf(" %c ", mar(trash[i]));
//		else
//			printf("%c%2d", mar(trash[i]), num(trash[i]));
//		if (i != trash[0])
//			printf("と");
//	}
//	printf("を出しました 残り%d枚です\n", data[n].hand[0]);
//}
//void revolution(void) {
//	/* 革命 */
//
//	if (trash[0] >= 4 && rev == 0) {
//		printf("革命が起こりました\n");
//		rev = 1;
//	}
//	else if (trash[0] >= 4 && rev == 1) {
//		printf("革命が返されました\n");
//		rev = 0;
//	}
//}
//void CP::elevenback(void) {
//	/* 11が出た場合 */
//	int i;
//
//	for (i = 1; i <= trash[0]; i++) {
//		if (num(trash[i]) == 11) {
//			eback = 1;
//			printf("イレブンバックしました\n");
//			break;
//		}
//	}
//}
//void CP::pl_routine(int n) {
//	/* プレイヤー用 */
//	int i;
//
//	status(n);
//
//	/* 0で決定、選択しているカードが真か関数judgに送る */
//	while (1) {
//
//		/* 入力処理 */
//		produce[0][0] = 0;
//		i = 1;
//		while (1) {
//			printf("%2d枚目のカード : ", i);
//			scanf_s("%d", &produce[0][i]);
//			if (produce[0][i] == 0)
//				break;
//			produce[0][0]++;
//			i++;
//		}
//		/* 初めから0が入力されたら */
//		if (produce[0][0] == 0) {
//			printf("→%sはパスしました\n", data[n].name);
//			data[n].pass++;
//			break;
//		}
//		/* 入力が終わったらjudgで判定 */
//		if (judg(n) == 1) {
//			arrange(n);
//			pc = n; /* 最後に出した人を記憶 */
//			print(n);
//			revolution();
//			elevenback();
//			break;
//		}
//		printf("カードが不正でした。もう一度選んでください。\n");
//	}
//}
//void CP::cp_routine(int n) {
//	/* コンピュータの考え方 */
//	int i, j;
//
//	onesec();
//	/* */
//	if (trash[0] == 0) {
//		produce[0][0] = 6;
//		while (1) {
//			for (i = 0; i < 10; i++) {
//
//				for (j = 1; j <= produce[0][0]; j++)
//					produce[0][j] = (rand() % data[n].hand[0]) + 1;
//
//				if (judg(n) == 1) {
//					arrange(n);
//					pc = n;
//					print(n);
//					revolution();
//					elevenback();
//					break;
//				}
//			}
//			if (pc == n)
//				break;
//
//			if (produce[0][0] == 1) {
//				printf("→%sはパスしました\n", data[n].name);
//				data[n].pass++;
//				break;
//			}
//			produce[0][0]--;
//		}
//	}
//	else {
//		produce[0][0] = trash[0];
//		for (i = 0; i < 20; i++) {
//
//			for (j = 1; j <= produce[0][0]; j++)
//				produce[0][j] = (rand() % data[n].hand[0]) + 1;
//
//			if (judg(n) == 1) {
//				arrange(n);
//				pc = n;
//				print(n);
//				revolution();
//				elevenback();
//				break;
//			}
//		}
//		if (pc != n) {
//			printf("→%sはパスしました\n", data[n].name);
//			data[n].pass++;
//		}
//	}
//}
//void CP::expend(int n) {
//	/* 手札がなくなった場合 */
//	int i;
//
//	if (data[n].hand[0] == 0) {
//		onesec();
//		data[n].fin = 1;
//		for (i = 1; i <= trash[0]; i++) {
//			if (num(trash[i]) == 8 || eback == 0 && str(trash[i]) == 12 || mar(trash[i]) == 'J') {
//				printf("%sは反則あがりました\n", data[n].name);
//				break;
//			}
//			if (i == trash[0])
//				printf("%sはあがりました\n", data[n].name);
//		}
//	}
//}
//void CP::slash8(int n) {
//	/* 8切り */
//	int i;
//
//	for (i = 1; i <= trash[0]; i++) {
//		if (num(trash[i]) == 8) {
//			pc = n;
//			data[0].pass = data[1].pass = data[2].pass = data[3].pass = 1;
//			data[n].pass = 0;
//			break;
//		}
//	}
//}
//void CP::turn(int n) {
//
//	phase(n);
//
//	if (data[n].fin == 0 && data[n].pass == 0) {
//
//		if (n == 0)
//			pl_routine(n);
//		else
//			cp_routine(n);
//
//		expend(n);
//		slash8(n);
//	}
//}
//void CP::main(void) {
//
//	int i = 0;
//	srand(time(NULL));
//
//
//	title();
//	deckmake();
//
//	while (1) {
//
//		datareset();
//		deckshuffle();
//		dealcards();
//		d3start();
//
//		i++;
//
//		printf("\n==========第%d回戦スタート！==========\n\n", i);
//		while (1) {
//
//			turn(order[0]);
//
//			if (data[0].fin + data[1].fin + data[2].fin + data[3].fin == 3)
//				break;
//
//			turn(order[1]);
//
//			if (data[0].fin + data[1].fin + data[2].fin + data[3].fin == 3)
//				break;
//
//			turn(order[2]);
//
//			if (data[0].fin + data[1].fin + data[2].fin + data[3].fin == 3)
//				break;
//
//			turn(order[3]);
//
//			if (data[0].fin + data[1].fin + data[2].fin + data[3].fin == 3)
//				break;
//
//		}
//		printf("\n\n\n==========第%d回戦終了！==========\n", i);
//
//
//	}
//}