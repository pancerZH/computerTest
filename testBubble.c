#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "testNum.txt"

int* makeSpaceBig(int*, int);
void bubble(int*, const int, const int);

int main(int argc, char* argv[])
{
	char* fileName = FILENAME;
	if(argc >= 2)//如果通过命令行传入文件名
		fileName = argv[1];
	FILE* fp = fopen(fileName, "r");
	if(fp == NULL)
	{
		printf("Out of space!\n");
		exit(1);
	}

	int count = 0;//count代表读入的字符
	int num, spaceSize = 100;
	int* intSpace = (int*)malloc(sizeof(int) * spaceSize);
	clock_t start, finish;
	start = clock();

	while(fscanf(fp, "%d", &num) != EOF)
	{
		if(count >= spaceSize)
		{
			intSpace = makeSpaceBig(intSpace, spaceSize);
			spaceSize *= 2;
		}
		
		*(intSpace + count) = num;
		++count;
	}
	fclose(fp);

	finish = clock();
	float totalTime = (float)(finish - start) / CLOCKS_PER_SEC;
	printf("%f seconds used to read file and ask for space\n", totalTime);

	--count;//现在count标记intSpace最后一个数字的位置

	start = clock();
	
	bubble(intSpace, count, 1);//冒泡排序-从大到小
	bubble(intSpace, count, 0);//冒泡排序-从小到大
	
	finish = clock();
	totalTime = (float)(finish - start) / CLOCKS_PER_SEC;
	printf("%f seconds used to sort\n", totalTime);

	/* 此部分为输出排好序的数字 */
	/*while(count >= 0)
	{
		printf("%d ", *(intSpace + count));
		if(count % 20 == 0)
			printf("\n");
		--count;
	}*/	

	return 0;
}

int* makeSpaceBig(int* oldSpace, int oldSize)//实现内存倍增
{
	int newSize = oldSize * 2;
	int* newSpace = (int*)malloc(sizeof(int) * newSize);
	if(newSpace == NULL)
	{
		printf("Out of space!");
		exit(1);
	}

	int count = 0;
	while(count < oldSize)//将数据从旧的内存空间拷贝进新的空间
	{
		*(newSpace + count) = *(oldSpace + count);
		++count;
	}
	
	free(oldSpace);
	return newSpace;
}

void bubble(int* intSpace, const int size, const int flag)
{
	int  i;
	if(flag == 1)//将数字从大到小排列
		for(i = 0;i < size;++i)	
		{
			int j;
			for(j = 0;j < size - i;++j)
			{
				if(*(intSpace + j) < *(intSpace + j + 1))
				{
					int temp = *(intSpace + j);
					*(intSpace + j) = *(intSpace + j + 1);
					*(intSpace + j + 1) = temp;
				}
			}
		}
	else//将数字从小到大排列
		for(i = 0;i < size;++i)
		{
			int j;
			for(j = 0;j < size;++j)
			{
				if(*(intSpace + j) > *(intSpace + j + 1))
				{
					int temp = *(intSpace + j);
					*(intSpace + j) = *(intSpace + j + 1);
					*(intSpace + j + 1) = temp;
				}
			}
		}
}
