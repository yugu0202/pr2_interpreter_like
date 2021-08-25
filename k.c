#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFLEN 256 // 文字列バッファのサイズ

//ヘルプ表示　引数があればより詳細なヘルプを表示する
void help(int num,char *arg)
{
	if (num == -1)
	{
		printf("help [command]\n");
		printf("exit\n");
		printf("reset\n");
		printf("show\n");
		printf("sum [filename]\n");
	}
	else if (num == 1)
	{
		if (strcmp(arg,"help") == 0)
		{
			printf("\thelp [command]\n");
			printf("show help\n");
			printf("\t[command]\n");
			printf("show detailed [command] help\n");
		}
	}
}

//ファイルの中の数字の合計を出す
int sum(char *file)
{
	FILE *fp = NULL;
	int t = 0;
	int x;

	fp = fopen(file, "r");
	if (fp == NULL)
	{
		perror("open failure");
		return 0;
	}

	while (fscanf(fp, "%d", &x) != EOF)
	{
		t += x;
	}

	printf("subtotal:%d\n", t);
	if (fp != NULL) fclose(fp);

	return (t);
}

//合計をファイルに出力する
void save(char *file,int total)
{
	FILE *fp = NULL;

	fp = fopen(file,"w");
	if (fp == NULL)
	{
		perror("open failure");
	}

	fprintf(fp,"%d\n",total);

	fclose(fp);
}


void fCreate(char *file)
{
	FILE *fp = NULL;

	fp = fopen(file,"w");
	if (fp == NULL)
	{
		perror("open failure");
	}
	fclose(fp);
}


//コマンドの動作を記録する
void record(char *file,char *cmd)
{
	FILE *fp = NULL;

	fp = fopen(file,"a");

	if (fp == NULL)
	{
		perror("open failure");
	}

	fprintf(fp,"%s\n",cmd);

	fclose(fp);
}


//recordで作られたファイルの読み込み、実行
int run(char *file,int total)
{
	FILE *fp = NULL;
	char cmd[BUFLEN]; // コマンドの文字列バッファ
	char arg[BUFLEN]; // コマンド引数バッファ
	char buf[BUFLEN];

	char fmt[16]; // 書式文字列
	sprintf(fmt,"%%%ds",BUFLEN-1); // 書式文字列を自動生成する

	fp = fopen(file,"r");
	if (fp == NULL)
	{
		perror("open failure");
	}

	while (fscanf(fp, "%255s", cmd) != EOF)
	{
		printf("\n");
		printf("order > %s\n",cmd);
		// コマンドの解釈・実行
		if (strcmp(cmd,"sum") == 0)
		{
			scanf(fmt,arg);
			total += sum(arg);
		}
		else if (strcmp(cmd,"show") == 0)
		{
			printf("total:%d\n",total);
		}
		else if (strcmp(cmd,"reset") == 0)
		{
			total = 0;
			printf("total reset\n");
		}
		else if (strcmp(cmd,"save") == 0)
		{
			scanf(fmt,arg);
			save(arg,total);
		}
		else if (strcmp(cmd,"ls") == 0)
		{
			system(cmd);
		}
	}
	return total;
}


int main(void)
{
	int total = 0; // 合計
	int num = 0;
	int recordFlag = 0,skipFlag = 0; //0の時false 1の時true
	char recordFile[BUFLEN];
	char cmd[BUFLEN]; // コマンドの文字列バッファ
	char arg[BUFLEN]; // コマンド引数バッファ
	char buf[BUFLEN];

	char fmt[16]; // 書式文字列
	sprintf(fmt,"%%%ds",BUFLEN-1); // 書式文字列を自動生成する

	while (1)
	{
		skipFlag = 0;
		// コマンドの入力
		printf("order > ");
		
		if (scanf(fmt, cmd) == EOF) break;


		// コマンドの解釈・実行
		if (strcmp(cmd, "exit") == 0)
		{
			break;
		}
		else if (strcmp(cmd,"sum") == 0)
		{
			scanf(fmt,arg);
			total += sum(arg);
		}
		else if (strcmp(cmd,"show") == 0)
		{
			printf("total:%d\n",total);
		}
		else if (strcmp(cmd,"reset") == 0)
		{
			total = 0;
			printf("total reset\n");
		}
		else if (strcmp(cmd,"save") == 0)
		{
			scanf(fmt,arg);
			save(arg,total);
		}
		else if (strcmp(cmd,"record") == 0)
		{
			scanf(fmt,recordFile);
			recordFlag = 1;
			skipFlag = 1;
		}
		else if (strcmp(cmd,"end") == 0)
		{
			recordFlag = 0;
			recordFile[0] = '\0';
		}
		else if (strcmp(cmd,"run") == 0)
		{
			scanf(fmt,arg);
			total = run(arg,total);
		}
		else if (strcmp(cmd,"ls") == 0)
		{
			system(cmd);
		}
		else if (strcmp(cmd,"help") == 0)
		{
			skipFlag = 1;
			fgets(buf,BUFLEN,stdin);
			num = sscanf(buf,fmt,arg);
			help(num,arg);
		}
		else
		{
			printf("error:unknown command:%s\n", cmd);
			skipFlag = 1;
		}

		if (recordFlag == 1 && skipFlag == 0)
		{
			record(recordFile,cmd);
		}

		printf("\n");
	}

	printf("end.\n\n");
	return 0;
}
