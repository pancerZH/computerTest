#include <stdio.h>
#include <stdlib.h>

#define LIMIT 50000

int main(int argc, char* argv[])
{
	FILE* fp = fopen("testNum.txt", "w");
	int count = 0, limit = LIMIT;
	if(argc > 1)//从命令行输入产生的数字数量
		limit = atoi(argv[1]);

	while(count < limit)
	{
		if(count % 20 == 0)
			fprintf(fp, "\n");
		fprintf(fp, "%d ", count);
		++count;
	}
	fclose(fp);

	return 0;
}
