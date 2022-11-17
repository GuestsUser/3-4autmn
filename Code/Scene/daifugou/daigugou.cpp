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
//	char name[20]; /* ���O */
//	int hand[15]; /* ��D */
//	int fin; /* �I�� */
//	int pass; /* �p�X */
//};
//
//struct player data[4] = {
//{"���Ȃ�",0,0,0},
//{"NP1" ,0,0,0},
//{"NP2" ,0,0,0},
//{"NP3" ,0,0,0},
//};
//
//
//int cards[54]; /* �R�D */
//int order[4]; /* �N����n�߂邩 */
//int trash[15] = { 0 }; /* �ׯ�� */
//int produce[2][15]; /* �o����D */
//int rev = 0; /* �v�� */
//int eback = 0; /* 11�o�b�N */
//int pc = -1; /* �Ō�ɒN���o�������J�E���g */
//char mark[5] = { 'C','D','S','H','J' };/* �g�����v�̃}�[�N */
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
//	/* �J�[�h�̋��� */
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
//	/* �J�[�h�̐��� */
//	int x;
//
//	x = (num_x - 1) % 13 + 1;
//	return x;
//}
//
//int mar(int mar_x) {
//	/* �J�[�h�̃}�[�N */
//	char x;
//
//	x = mark[(mar_x - 1) / 13];
//	return x;
//}
//int com(int com_x, int com_y) {
//	/* �J�[�h�̋������r */
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
//	/* �\�[�g�p�֐� */
//	int i, j, x;
//
//	for (i = sort_x; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			/* �J�[�h�̋������Ƀ\�[�g �����������ꍇ�A�}�[�N���Ƀ\�[�g */
//			if (com(*(sort_y + j), *(sort_y + j + 1)) == 2 || com(*(sort_y + j), *(sort_y + j + 1)) == 0 && *(sort_y + j) > *(sort_y + j + 1)) {
//
//				x = *(sort_y + j);
//				*(sort_y + j) = *(sort_y + j + 1);
//				*(sort_y + j + 1) = x;
//
//				/* produce���\�[�g����ꍇ */
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
//	printf("�@��@�@�x�@�@���@\n");
//	onesec();
//	printf("[���[��]\n");
//	printf("�E8�؂�,11�o�b�N�@\n");
//	printf("�E2���o���`6���o��(JK�܂�),�v���@\n");
//	printf("�E8,JK,2(�v������3)�ł�����Ɣ����@\n");
//	printf("�E��x�p�X�����炻�̃^�[���͏o���Ȃ��@\n");
//	onesec();
//	printf("%s�̖��O����� : ", data[0].name);
//	scanf_s("%s", data[0].name);
//}
//
//void CP::deckmake(void) {
//	/* �R�D�쐬 */
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
//	/* �R�D���V���b�t�� */
//	int i, x, y, z;
//	for (i = 0; i < 500; i++) {
//		x = rand() % 54;
//		y = rand() % 54;
//		z = cards[x];
//		cards[x] = cards[y];
//		cards[y] = z;
//	}
//	onesec();
//	printf("�R�D���V���b�t�����܂���\n");
//}
//
//void CP::dealcards(void) {
//	/* ��D��z�� */
//	int i, j;
//
//	j = rand() % 4; /* �N����z�邩 */
//	for (i = 0; i <= 53; i++, j++) {
//		if (j == 4)
//			j = 0; /* data[3]�̎���data[0]�� */
//
//		data[j].hand[0]++; /* ������+1 */
//		data[j].hand[data[j].hand[0]] = *cards;
//	}
//	/* �S���̎�D���������Ƀ\�[�g */
//	sort(data[0].hand[0], data[0].hand, 0);
//	sort(data[1].hand[0], data[1].hand, 0);
//	sort(data[2].hand[0], data[2].hand, 0);
//	sort(data[3].hand[0], data[3].hand, 0);
//
//	onesec();
//	printf("��D��z��܂���\n");
//}
//
//void CP::d3start(void) {
//	/* �_�C���̂R����X�^�[�g */
//	int i, j;
//
//	for (i = 1, j = 0; i < 5; j++) {
//		if (j == 4) {
//			j = 0;
//			i++;
//		}
//		if (*data[j].hand == 16) /* �_�C���̂R�̃J�[�h�ԍ���16 */
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
//	printf("�_�C���̂R�������Ă�l����X�^�[�g���܂�\n");
//}
//
//void CP::phase(int n) {
//	/* �^�[��������Ă���O�ɍs������ */
//
//	/* �������g���b�V���ɏo�����J�[�h������炸��1�T���Ă����� */
//	if (n == pc) {
//		onesec();
//		printf("�ꂪ����܂���\n\n");
//		pc = -1;
//		eback = 0; /* 11�o�b�N�����Z�b�g */
//		trash[0] = 0; /* �ׯ�������Z�b�g */
//		data[0].pass = data[1].pass = data[2].pass = data[3].pass = 0; /* �p�X�����Z�b�g */
//	}
//}
//
//void CP::status(int n) {
//	/* �v���C���[�p�̏��\��������֐� */
//	int i;
//
//	onesec();
//	/* �g���b�V����\�� */
//	if (trash[0] == 0) /* �ׯ�����󂾂����ꍇ */
//		printf("[��] ��\n");
//
//	else { /* �ׯ���ɶ��ނ��������ꍇ */
//		printf("[��]");
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
//	/* ��D��\�� */
//	for (i = 1; i <= data[n].hand[0]; i++)
//		printf("[%3d]", i);
//	printf("\n");
//
//	for (i = 1; i <= data[n].hand[0]; i++) {
//
//		/* �W���[�J�[�������ꍇ �������\�� */
//		if (mar(*data[n].hand) != 'J')
//			printf(" %c%2d ", mar(*data[n].hand), num(data[n].hand[i]));
//		else
//			printf(" %c ", mar(data[n].hand[i]));
//	}
//	printf("\n");
//	printf("���Ȃ��̔Ԃł�\n");
//}
//int judg(int n) {
//
//	int i, j;
//
//	/* ���g��produce[1][]�ɃR�s�[ */
//	produce[1][0] = produce[0][0];
//	for (i = 1; i <= produce[0][0]; i++)
//		produce[1][i] = data[n].hand[produce[0][i]];
//
//	/* produce���\�[�g */
//	sort(produce[1][0], produce[1], 1);
//
//	void CP::onesec(void) {
//		/* 1�b�\�� */
//		time_t t1;
//		srand(time(NULL));
//
//		t1 = time(NULL);
//		while (1 != time(NULL) - t1);
//	}
//
//int str(int str_x) {
//	/* �J�[�h�̋��� */
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
//	/* �J�[�h�̐��� */
//	int x;
//
//	x = (num_x - 1) % 13 + 1;
//	return x;
//}
//
//int mar(int mar_x) {
//	/* �J�[�h�̃}�[�N */
//	char x;
//
//	x = mark[(mar_x - 1) / 13];
//	return x;
//}
//int com(int com_x, int com_y) {
//	/* �J�[�h�̋������r */
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
//	/* �\�[�g�p�֐� */
//	int i, j, x;
//
//	for (i = sort_x; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			/* �J�[�h�̋������Ƀ\�[�g �����������ꍇ�A�}�[�N���Ƀ\�[�g */
//			if (com(*(sort_y + j), *(sort_y + j + 1)) == 2 || com(*(sort_y + j), *(sort_y + j + 1)) == 0 && *(sort_y + j) > *(sort_y + j + 1)) {
//
//				x = *(sort_y + j);
//				*(sort_y + j) = *(sort_y + j + 1);
//				*(sort_y + j + 1) = x;
//
//				/* produce���\�[�g����ꍇ */
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
//	printf("�@��@�@�x�@�@���@\n");
//	onesec();
//	printf("[���[��]\n");
//	printf("�E8�؂�,11�o�b�N�@\n");
//	printf("�E2���o���`6���o��(JK�܂�),�v���@\n");
//	printf("�E8,JK,2(�v������3)�ł�����Ɣ����@\n");
//	printf("�E��x�p�X�����炻�̃^�[���͏o���Ȃ��@\n");
//	onesec();
//	printf("%s�̖��O����� : ", data[0].name);
//	scanf("%s", data[0].name);
//}
//
//void CP::deckmake(void) {
//	/* �R�D�쐬 */
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
//	/* �R�D���V���b�t�� */
//	int i, x, y, z;
//	for (i = 0; i < 500; i++) {
//		x = rand() % 54;
//		y = rand() % 54;
//		z = cards[x];
//		cards[x] = cards[y];
//		cards[y] = z;
//	}
//	onesec();
//	printf("�R�D���V���b�t�����܂���\n");
//}
//
//void CP::dealcards(void) {
//	/* ��D��z�� */
//	int i, j;
//
//	j = rand() % 4; /* �N����z�邩 */
//	for (i = 0; i <= 53; i++, j++) {
//		if (j == 4)
//			j = 0; /* data[3]�̎���data[0]�� */
//
//		data[j].hand[0]++; /* ������+1 */
//		data[j].hand[data[j].hand[0]] = cards;
//	}
//	/* �S���̎�D���������Ƀ\�[�g */
//	sort(data[0].hand[0], data[0].hand, 0);
//	sort(data[1].hand[0], data[1].hand, 0);
//	sort(data[2].hand[0], data[2].hand, 0);
//	sort(data[3].hand[0], data[3].hand, 0);
//
//	onesec();
//	printf("��D��z��܂���\n");
//}
//
//void Cp::d3start(void) {
//	/* �_�C���̂R����X�^�[�g */
//	int i, j;
//
//	for (i = 1, j = 0; i < 5; j++) {
//		if (j == 4) {
//			j = 0;
//			i++;
//		}
//		if (data[j].hand == 16) /* �_�C���̂R�̃J�[�h�ԍ���16 */
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
//	printf("�_�C���̂R�������Ă�l����X�^�[�g���܂�\n");
//}
//
//void CP::phase(int n) {
//	/* �^�[��������Ă���O�ɍs������ */
//
//	/* �������g���b�V���ɏo�����J�[�h������炸��1�T���Ă����� */
//	if (n == pc) {
//		onesec();
//		printf("�ꂪ����܂���\n\n");
//		pc = -1;
//		eback = 0; /* 11�o�b�N�����Z�b�g */
//		trash[0] = 0; /* �ׯ�������Z�b�g */
//		data[0].pass = data[1].pass = data[2].pass = data[3].pass = 0; /* �p�X�����Z�b�g */
//	}
//}
//
//void CP::status(int n) {
//	/* �v���C���[�p�̏��\��������֐� */
//	int i;
//
//	onesec();
//	/* �g���b�V����\�� */
//	if (trash[0] == 0) /* �ׯ�����󂾂����ꍇ */
//		printf("[��] ��\n");
//
//	else { /* �ׯ���ɶ��ނ��������ꍇ */
//		printf("[��]");
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
//	/* ��D��\�� */
//	for (i = 1; i <= data[n].hand[0]; i++)
//		printf("[%3d]", i);
//	printf("\n");
//
//	for (i = 1; i <= data[n].hand[0]; i++) {
//
//		/* �W���[�J�[�������ꍇ �������\�� */
//		if (mar(data[n].hand) != 'J')
//			printf(" %c%2d ", mar(data[n].hand), num(data[n].hand[i]));
//		else
//			printf(" %c ", mar(data[n].hand[i]));
//	}
//	printf("\n");
//	printf("���Ȃ��̔Ԃł�\n");
//}
//int judg(int n) {
//
//	int i, j;
//
//	/* ���g��produce[1][]�ɃR�s�[ */
//	produce[1][0] = produce[0][0];
//	for (i = 1; i <= produce[0][0]; i++)
//		produce[1][i] = data[n].hand[produce[0][i]];
//
//	/* produce���\�[�g */
//	sort(produce[1][0], produce[1], 1);
//
//
//
//	/* ========judg�̃��C������======== */
//
//	/* �I��͈͓��ŃJ�[�h���o���Ă��邩 */
//	for (i = 1; i <= produce[0][0]; i++) {
//		if (0 > produce[0][i] || produce[0][i] > data[n].hand[0])
//			return 0;
//	}
//
//	/* �����J�[�h���o���Ă��Ȃ��� */
//	for (i = produce[0][0]; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			if (produce[0][j] == produce[0][j + 1])
//				return 0;
//		}
//	}
//
//	/* ��ɃJ�[�h������ꍇ�A�����������o���Ă��邩 */
//	if (trash[0] != 0 && trash[0] != produce[0][0])
//		return 0;
//
//	/* ���������̃J�[�h�� */
//	for (i = produce[0][0]; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			if (num(produce[1][j]) != num(produce[1][j + 1]) && mar(produce[1][j]) != 'J' && mar(produce[1][j + 1]) != 'J')
//				return 0;
//		}
//	}
//
//	/* ��ɉ�������ꍇ�A���݂̏��苭���J�[�h�� */
//	if (trash[0] != 0 && com(trash[1], produce[1][1]) != 1)
//		return 0;
//
//	return 1;
//}
//void CP::arrange(int n) {
//	int i, j;
//
//	/* �ׯ���ɑI���������ނ������ */
//	trash[0] = produce[0][0];
//	for (i = 1; i <= trash[0]; i++)
//		trash[i] = produce[1][i];
//
//	/* ���������炵��D���߂� */
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
//	/* �W���[�J�[�������ꍇ �������\�� */
//	printf("��%s��", data[n].name);
//	for (i = 1; i <= trash[0]; i++) {
//		if (mar(trash[i]) == 'J')
//			printf(" %c ", mar(trash[i]));
//		else
//			printf("%c%2d", mar(trash[i]), num(trash[i]));
//		if (i != trash[0])
//			printf("��");
//	}
//	printf("���o���܂��� �c��%d���ł�\n", data[n].hand[0]);
//}
//void CP::revolution(void) {
//	/* �v�� */
//
//	if (trash[0] >= 4 && rev == 0) {
//		printf("�v�����N����܂���\n");
//		rev = 1;
//	}
//	else if (trash[0] >= 4 && rev == 1) {
//		printf("�v�����Ԃ���܂���\n");
//		rev = 0;
//	}
//}
//void CP::elevenback(void) {
//	/* 11���o���ꍇ */
//	int i;
//
//	for (i = 1; i <= trash[0]; i++) {
//		if (num(trash[i]) == 11) {
//			eback = 1;
//			printf("�C���u���o�b�N���܂���\n");
//			break;
//		}
//	}
//}
//void CP::pl_routine(int n) {
//	/* �v���C���[�p */
//	int i;
//
//	status(n);
//
//	/* 0�Ō���A�I�����Ă���J�[�h���^���֐�judg�ɑ��� */
//	while (1) {
//
//		/* ���͏��� */
//		produce[0][0] = 0;
//		i = 1;
//		while (1) {
//			printf("%2d���ڂ̃J�[�h : ", i);
//			scanf("%d", &produce[0][i]);
//			if (produce[0][i] == 0)
//				break;
//			produce[0][0]++;
//			i++;
//		}
//		/* ���߂���0�����͂��ꂽ�� */
//		if (produce[0][0] == 0) {
//			printf("��%s�̓p�X���܂���\n", data[n].name);
//			data[n].pass++;
//			break;
//		}
//		/* ���͂��I�������judg�Ŕ��� */
//		if (judg(n) == 1) {
//			arrange(n);
//			pc = n; /* �Ō�ɏo�����l���L�� */
//			print(n);
//			revolution();
//			elevenback();
//			break;
//		}
//		printf("�J�[�h���s���ł����B������x�I��ł��������B\n");
//	}
//}
//void CP::cp_routine(int n) {
//	/* �R���s���[�^�̍l���� */
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
//				printf("��%s�̓p�X���܂���\n", data[n].name);
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
//			printf("��%s�̓p�X���܂���\n", data[n].name);
//			data[n].pass++;
//		}
//	}
//}
//void CP::expend(int n) {
//	/* ��D���Ȃ��Ȃ����ꍇ */
//	int i;
//
//	if (data[n].hand[0] == 0) {
//		onesec();
//		data[n].fin = 1;
//		for (i = 1; i <= trash[0]; i++) {
//			if (num(trash[i]) == 8 || eback == 0 && str(trash[i]) == 12 || mar(trash[i]) == 'J') {
//				printf("%s�͔���������܂���\n", data[n].name);
//				break;
//			}
//			if (i == trash[0])
//				printf("%s�͂�����܂���\n", data[n].name);
//		}
//	}
//}
//void CP::slash8(int n) {
//	/* 8�؂� */
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
//		printf("\n==========��%d���X�^�[�g�I==========\n\n", i);
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
//		printf("\n\n\n==========��%d���I���I==========\n", i);
//
//
//	}
//}
//	for (i = 1; i <= produce[0][0]; i++) {
//		if (0 > produce[0][i] || produce[0][i] > data[n].hand[0])
//			return 0;
//	}
//
//	/* �����J�[�h���o���Ă��Ȃ��� */
//	for (i = produce[0][0]; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			if (produce[0][j] == produce[0][j + 1])
//				return 0;
//		}
//	}
//
//	/* ��ɃJ�[�h������ꍇ�A�����������o���Ă��邩 */
//	if (trash[0] != 0 && trash[0] != produce[0][0])
//		return 0;
//
//	/* ���������̃J�[�h�� */
//	for (i = produce[0][0]; i > 1; i--) {
//		for (j = 1; j < i; j++) {
//			if (num(produce[1][j]) != num(produce[1][j + 1]) && mar(produce[1][j]) != 'J' && mar(produce[1][j + 1]) != 'J')
//				return 0;
//		}
//	}
//
//	/* ��ɉ�������ꍇ�A���݂̏��苭���J�[�h�� */
//	if (trash[0] != 0 && com(trash[1], produce[1][1]) != 1)
//		return 0;
//
//	return 1;
//}
//void CP::arrange(int n) {
//	int i, j;
//
//	/* �ׯ���ɑI���������ނ������ */
//	trash[0] = produce[0][0];
//	for (i = 1; i <= trash[0]; i++)
//		trash[i] = produce[1][i];
//
//	/* ���������炵��D���߂� */
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
//	/* �W���[�J�[�������ꍇ �������\�� */
//	printf("��%s��", data[n].name);
//	for (i = 1; i <= trash[0]; i++) {
//		if (mar(trash[i]) == 'J')
//			printf(" %c ", mar(trash[i]));
//		else
//			printf("%c%2d", mar(trash[i]), num(trash[i]));
//		if (i != trash[0])
//			printf("��");
//	}
//	printf("���o���܂��� �c��%d���ł�\n", data[n].hand[0]);
//}
//void revolution(void) {
//	/* �v�� */
//
//	if (trash[0] >= 4 && rev == 0) {
//		printf("�v�����N����܂���\n");
//		rev = 1;
//	}
//	else if (trash[0] >= 4 && rev == 1) {
//		printf("�v�����Ԃ���܂���\n");
//		rev = 0;
//	}
//}
//void CP::elevenback(void) {
//	/* 11���o���ꍇ */
//	int i;
//
//	for (i = 1; i <= trash[0]; i++) {
//		if (num(trash[i]) == 11) {
//			eback = 1;
//			printf("�C���u���o�b�N���܂���\n");
//			break;
//		}
//	}
//}
//void CP::pl_routine(int n) {
//	/* �v���C���[�p */
//	int i;
//
//	status(n);
//
//	/* 0�Ō���A�I�����Ă���J�[�h���^���֐�judg�ɑ��� */
//	while (1) {
//
//		/* ���͏��� */
//		produce[0][0] = 0;
//		i = 1;
//		while (1) {
//			printf("%2d���ڂ̃J�[�h : ", i);
//			scanf_s("%d", &produce[0][i]);
//			if (produce[0][i] == 0)
//				break;
//			produce[0][0]++;
//			i++;
//		}
//		/* ���߂���0�����͂��ꂽ�� */
//		if (produce[0][0] == 0) {
//			printf("��%s�̓p�X���܂���\n", data[n].name);
//			data[n].pass++;
//			break;
//		}
//		/* ���͂��I�������judg�Ŕ��� */
//		if (judg(n) == 1) {
//			arrange(n);
//			pc = n; /* �Ō�ɏo�����l���L�� */
//			print(n);
//			revolution();
//			elevenback();
//			break;
//		}
//		printf("�J�[�h���s���ł����B������x�I��ł��������B\n");
//	}
//}
//void CP::cp_routine(int n) {
//	/* �R���s���[�^�̍l���� */
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
//				printf("��%s�̓p�X���܂���\n", data[n].name);
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
//			printf("��%s�̓p�X���܂���\n", data[n].name);
//			data[n].pass++;
//		}
//	}
//}
//void CP::expend(int n) {
//	/* ��D���Ȃ��Ȃ����ꍇ */
//	int i;
//
//	if (data[n].hand[0] == 0) {
//		onesec();
//		data[n].fin = 1;
//		for (i = 1; i <= trash[0]; i++) {
//			if (num(trash[i]) == 8 || eback == 0 && str(trash[i]) == 12 || mar(trash[i]) == 'J') {
//				printf("%s�͔���������܂���\n", data[n].name);
//				break;
//			}
//			if (i == trash[0])
//				printf("%s�͂�����܂���\n", data[n].name);
//		}
//	}
//}
//void CP::slash8(int n) {
//	/* 8�؂� */
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
//		printf("\n==========��%d���X�^�[�g�I==========\n\n", i);
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
//		printf("\n\n\n==========��%d���I���I==========\n", i);
//
//
//	}
//}