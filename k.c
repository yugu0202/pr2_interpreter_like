#include <stdio.h>
#include <string.h>

#define BUFLEN 256 // 文字列バッファのサイズ

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

int main(void)
{
	int total = 0; // 合計
	int num = 0;
	char cmd[BUFLEN]; // コマンドの文字列バッファ
	char arg[BUFLEN]; // コマンド引数バッファ
	char buf[BUFLEN];

	char fmt[16]; // 書式文字列
	sprintf(fmt,"%%%ds",BUFLEN-1); // 書式文字列を自動生成する

	while (1)
	{
		// コマンドの入力
		printf("order > ");
		
		if (scanf(fmt, cmd) == EOF) break;

		// コマンドの解釈・実行
		if (strcmp(cmd, "exit") == 0) break;	// exit コマンド
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
			printf("total reset");
		}
		else if (strcmp(cmd,"help") == 0)
		{
			fgets(buf,BUFLEN,stdin);
			num = sscanf(buf,fmt,arg);
			help(num,arg);
		}
		else
		{
			printf("error:unknown command:%s\n", cmd);
		}

		printf("\n");
	}

	printf("end.\n\n");
	return 0;
}
