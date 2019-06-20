#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "windows.h"

#pragma warning(disable : 4996)

struct STUD
{
	int num;
	char name[15];
	float score[6];
	float total;
	float avg;
} stu[31];

struct JILU
{
	float average[6];
	float total[6];
} kecheng;

int records = 1;
int existed = 0;
int flag_c1 = 0;
int flag_c2 = 0;

void menu();
void biaotou(int kechengshu);
int shuru(int kechengshu);
int shuchu(int kechengshu);
void shuchuhang(int kechengshu, int col);
int calc_1(int kechengshu);
int calc_2(int kechengshu);
void jiaohuan(int col);
void rank_chengji(int kechengshu);
void rank_xuehao();
void rank_mingzi();
int sousuoxuehao(int xuehao);
int sousuoxingming(char a[]);
void tongji(int kechengshu);

int main()
{
	int kechengshu = 0;
	int a, i, j;
	char n[15];
	do
	{
		printf("input subjects:");
		scanf("%d", &kechengshu);
	} while (kechengshu < 0 || kechengshu > 6);
	printf("success!");
	system("pause");

	while (1)
	{
		system("cls");
		menu();

		printf("what to do?");
		scanf("%d", &a);

		switch (a)
		{
		case 1:
			shuru(kechengshu);
			break;
		case 2:
			calc_1(kechengshu);
			break;
		case 3:
			calc_2(kechengshu);
			break;
		case 4:
			rank_chengji(kechengshu);
			break;
		case 5:
			rank_xuehao();
			break;
		case 6:
			rank_mingzi();
			break;
		case 7:
			printf("Input number to search:");
			scanf("%d", &i);
			j = sousuoxuehao(i);
			if (j != -1)
			{
				shuchuhang(kechengshu, j);
			}
			else
			{
				printf("Not Found!\n");
			}
			system("pause");
			break;
		case 8:
			printf("Input name to search:");
			scanf("%s", n);
			i = sousuoxingming(n);
			if (i != -1)
			{
				shuchuhang(kechengshu, i);
			}
			else
			{
				printf("Not Found!\n");
			}
			system("pause");
			break;
		case 9:
			tongji(kechengshu);
			break;
		case 10:
			shuchu(kechengshu);
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
}

void menu()
{
	printf("1.	Input record manually\n");
	printf("2.	Calculate total and average score of every course\n");
	printf("3.	Calculate total and average score of every student\n");
	printf("4.	Sort in descending order by total score of every student\n");
	printf("5.	Sort in ascending order by number\n");
	printf("6.	Sort in dictionary order by name\n");
	printf("7.	Search by number\n");
	printf("8.	Search by name\n");
	printf("9.	Statistic analysis for every course\n");
	printf("10.	List record\n");
	printf("0 . Exit\n");
}

void biaotou(int kechengshu)
{
	printf("  学号  ");
	printf("     姓名    ");
	for (int i = 0; i < kechengshu; i++)
	{
		printf(" 成绩%d ", i + 1);
	}
	if (flag_c2)
	{
		printf("   总分   ");
		printf("   平均分   ");
	}
	printf("\n");
}

int shuru(int kechengshu)
{
	int i, j, flag;
	printf("input records:\nnumber,name,score of %d\n", kechengshu);
	printf("to end,input -1\n");

	if (existed)
	{
		i = records;
	}
	else
	{
		i = 1;
	}
	do
	{
		flag = 1;
		scanf("%d", &stu[i].num);
		if (stu[i].num != -1)
		{
			existed = 1;
			scanf("%s", &stu[i].name);
			for (j = 0; j < kechengshu; j++)
			{
				scanf("%f", &stu[i].score[j]);
			}
			for (; j < 5; j++)
			{
				stu[i].score[j] = 0;
			}
			records++;
			i++;
		}
		else
		{
			flag = 0;
		}
	} while (flag);

	flag_c1 = 0;
	flag_c2 = 0;

	return records;
}

int shuchu(int kechengshu)
{
	printf("\n");
	biaotou(kechengshu);

	for (int i = 1; i < records; i++)
	{
		printf("%8d  %s ", stu[i].num, stu[i].name);

		for (int j = 0; j < kechengshu; j++)
		{
			printf(" %3.2f ", stu[i].score[j]);
		}
		if (flag_c2)
		{
			printf(" %5.2f  %5.2f ", stu[i].total, stu[i].avg);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}

int calc_1(int kechengshu)
{
	float zongfen, total;
	for (int j = 0; j < kechengshu; j++)
	{
		zongfen = total = 0;
		for (int i = 1; i < records; i++)
		{
			total = total + stu[i].score[j];
		}
		kecheng.total[j] = total;
		kecheng.average[j] = total / (records - 1);
	}
	for (int i = 0; i < kechengshu; i++)
	{
		printf("Score No.%d :TOTAL  %5.2f   AVG  %3.2f\n", i, kecheng.total[i], kecheng.average[i]);
	}
	printf("\n");

	flag_c1 = 1;
	system("pause");
	return 0;
}
int calc_2(int kechengshu)
{
	float total;
	for (int i = 1; i < records; i++)
	{
		total = 0;
		for (int j = 0; j < kechengshu; j++)
		{
			total = total + stu[i].score[j];
		}
		stu[i].total = total;
		stu[i].avg = total / kechengshu;
	}
	printf("calculation OK\n");
	flag_c2 = 1;
	system("pause");
	return 0;
}

void jiaohuan(int col)
{
	stu[30] = stu[col];
	stu[col] = stu[col + 1];
	stu[col + 1] = stu[30];
}

void rank_chengji(int kechengshu)
{
	if (!flag_c2)
	{
		calc_2(kechengshu);
	}
	for (int i = 1; i < records; i++)
	{
		for (int j = 1; j < (records - i); j++)
		{
			if (stu[j].total < stu[j + 1].total)
			{
				jiaohuan(j);
			}
		}
	}
	printf("RANK OK\n");
	system("pause");
}

void rank_xuehao()
{
	for (int i = 1; i < records; i++)
	{
		for (int j = 1; j < (records - i); j++)
		{
			if (stu[j].num > stu[j + 1].num)
			{
				jiaohuan(j);
			}
		}
	}
	printf("RANK OK\n");
	system("pause");
}

void rank_mingzi()
{
	for (int i = 1; i < records; i++)
	{
		for (int j = 1; j < (records - i); j++)
		{
			if (strcmp(stu[j].name, stu[j + 1].name) > 0)
			{
				jiaohuan(j);
			}
		}
	}
	printf("RANK OK\n");
	system("pause");
}

void shuchuhang(int kechengshu, int col)
{
	printf("%8d  %s ", stu[col].num, stu[col].name);

	for (int j = 0; j < kechengshu; j++)
	{
		printf("  %3.2f   ", stu[col].score[j]);
	}
	if (flag_c2)
	{
		printf(" %5.2f   %5.2f  ", stu[col].total, stu[col].avg);
	}
	printf("\n");
}

int sousuoxuehao(int xuehao)
{
	int j = 1;
	for (int i = 1; i < records; i++)
	{
		if (xuehao == stu[j].num)
		{
			return j;
		}
		j++;
	}
	return -1;
}

int sousuoxingming(char a[])
{
	int i;
	for (i = 1; i < records; i++)
	{
		if (strcmp(a, stu[i].name) == 0)
		{
			return i;
		}
	}
	return -1;
}

void tongji(int kechengshu)
{
	int a, b, c, d, e, i, j;
	for (int i = 0; i < kechengshu; i++)
	{
		a = b = c = d = e = 0;
		for (int j = 1; j < records; j++)
		{
			if (stu[j].score[i] <= 100 && stu[j].score[i] >= 90)
			{
				a++;
			}
			else if (stu[j].score[i] <= 89 && stu[j].score[i] >= 80)
			{
				b++;
			}
			else if (stu[j].score[i] <= 79 && stu[j].score[i] >= 70)
			{
				c++;
			}
			else if (stu[j].score[i] <= 69 && stu[j].score[i] >= 60)
			{
				d++;
			}
			else if (stu[j].score[i] <= 59 && stu[j].score[i] >= 0)
			{
				e++;
			}
		}
		printf("Class No.%d:  A:%d/%.2f%%  B:%d/%.2f%%  C:%d/%.2f%%  D:%d/%.2f%%  E:%d/%.2f%%\n", i + 1, a, 100 * float(a) / records, b, 100 * float(b) / records, c, 100 * float(c) / records, d, 100 * float(d) / records, e, 100 * float(e) / records);
	}
	system("pause");
}
