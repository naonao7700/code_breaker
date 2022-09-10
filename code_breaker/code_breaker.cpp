#include <stdio.h>
#include <stdlib.h>

//セーブファイルに書き込みをする
//num = 繰り返した回数
void WriteSaveData( int num )
{
	FILE* fp = NULL;

	// プロジェクトからの相対パスで asset/sample.txt を書込モードで開く
	if (0 == fopen_s(&fp, "saveData.txt", "a"))
	{
		// フォーマットを指定して書き込む
		fprintf(fp, "%d\n", num );

		// 閉じる
		fclose(fp);
	}
	else
	{
		printf("ファイルを開けませんでした");
	}

}

//桁毎に被らないランダムな数字を取得する
int GetRandomNum()
{
	int table[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	for (int i = 0; i < 100; ++i)
	{
		int r1 = rand() % 10;
		int r2 = rand() % 10;

		//ランダムな位置を入れ替え
		int temp = table[r1];
		table[r1] = table[r2];
		table[r2] = temp;

	}

	int result = table[0];
	result += table[1] * 10;
	result += table[2] * 100;
	if (table[3] == 0)
	{
		result += table[4] * 1000;	//3桁にならないように修正
	}
	else
	{
		result += table[3] * 1000;
	}
	return result;
}

//数字を桁で分解した配列を作成する
void GetNumberArray(int value, int digit, int* outArray )
{
	int temp = value;
	for (int i = digit - 1; i >= 0; --i)
	{
		outArray[i] = temp % 10;
		temp /= 10;
	}
}

//HITの数を取得する
int GetHitNum(int numArray[4], int inputArray[4])
{
	int result = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (numArray[i] == inputArray[i])
		{
			result++;
		}
	}
	return result;
}

//Blowの数を取得する
int GetBlowNum(int numArray[4], int inputArray[4])
{
	int result = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (numArray[i] == inputArray[i])
		{
			inputArray[i] = -1;
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (numArray[i] == inputArray[j] && inputArray[i] != -1 )
			{
				result++;
			}
		}
	}
	return result;
}

int main()
{
	bool clearFlag = false;	//クリアしたフラグ

	//ランダムな数字を取得する
	int num = GetRandomNum();

	//配列で保持する
	int numArray[4];
	GetNumberArray(num, 4, numArray);

	//クリアするまでの回数
	int loopCount = 0;

	//クリアするまで繰り返す
	while (!clearFlag)
	{
		int input;
		scanf_s("%d", &input );
		int inputArray[4];
		GetNumberArray(input, 4, inputArray);

		//HITの数を取得する
		int hitNum = GetHitNum(numArray, inputArray);

		//Blowの数を取得する
		int blowNum = GetBlowNum(numArray, inputArray);

		printf("HIT:%d\n", hitNum);
		printf("Blow:%d\n", blowNum);

		//回数をカウントする
		loopCount++;
		
		//HITが4=クリア
		if (hitNum >= 4)
		{
			clearFlag = true;
		}
	}

	printf("クリア！答えは %d \n", num);
	printf("挑戦回数：%d\n", loopCount);

	//セーブデータに書き込む
	WriteSaveData(loopCount);

	return 0;
}