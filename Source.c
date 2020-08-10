#define _CRT_SECURE_NO_WARNINGS 
#include <conio.h> 
#include <string> 
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#define MAX_LUNGH_KEY 10
using namespace std;
struct freq_ch
{
	char _c;		//символ алфавита
	double _num;	//число вхождений
	freq_ch* next;	//указатель на следующий
	double chastota;
}f_c;

freq_ch* head_ = NULL;
freq_ch** arr_of_seq = NULL;
                                    
int gen_key(int a[2], int size)
{                  
	int i;
	srand(time(0));
	do {
		a[0] = rand() % size + 1;
		a[1] = rand() % size + 1;
	} while (a[0] == 1);
	return *a;
}

void affin_encrypt(char* file)
{
	char m;
	int a[2];
	int temp = 0;
	int _i = 0;
	int size;
	head_ = frequency(head_, 0, 0, (char*)file,"C:\\Users\\shimk\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\Crypto1\\Crypto1\\frequency_text.txt", size);
	x:
		if (size != 1)
		{
			gen_key(a, size);
			while ((nod(a[0], size) != 1))
			{
				gen_key(a, size);
			}
			printf("Key: a=%d b=%d\n", a[0], a[1]);
		}
		else
		{
			printf("Moshnost'alfavita = 1");
			goto x;
		}
	freq_ch* counter = head_;
	in.open(file);
	out.open("C:\\Users\\shimk\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\Crypto1\\Crypto1\\shifrtext.txt");

	while(1)
	{
		in.get(m);
		if (in.eof()) break;
		counter = head_;
		_i = 0;
		while (1)
		{
			if (counter->_c == m)
				break;
			_i++;
			counter = counter->next;
		}
		temp = (a[0]*_i + a[1])% size;
	//	printf("%d", temp);
		_i = 0;
		counter = head_;
		while (1) //преобразование буквы в шифрбукву
		{
			if (_i++ == temp) //т.к. список цикличен, то шифрование будет происходить по кругу
				break;
			counter = counter->next;
		}
		out << counter->_c;
	//	printf("%c", (unsigned char)counter->_c);
	} 
	in.close();
	out.close();
}

void affin_decrypt(char* file, char* alfavit)
{
	int size;
	int i = 0;
	char m;

	out.open("C:\\Users\\shimk\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\Crypto1\\Crypto1\\sortirovka_shifrtext.txt");
	out.seekp(0);
	
	head_ = sortirovka(file,"C:\\Users\\shimk\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\Crypto1\\Crypto1\\frequency_shifrtext.txt", head_, size, *alfavit_shifr, *fr_shifr);
	freq_ch *counter = head_;
	do
	{
		alfavit_shifr[i] = counter->_c;
		fr_shifr[i] = counter->chastota;
		out << counter->_c;
		counter = counter->next;
		i++;
	} while (i != size);
	in.open("C:\\Users\\shimk\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\Crypto1\\Crypto1\\shifrtext.txt");
	out2.open("C:\\Users\\shimk\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\Crypto1\\Crypto1\\affin_decrypt.txt");
	while (1)
	{
		in.get(m);
		if (in.eof()) break;
		for (q = 0; q < size; q++)
		{
			if (alfavit_shifr[q] == m)
			{
				out2 << alfavit[q];
			}
		}
	}

}
void vigenere_encrypt(int alfavit[], char* file, int size)
{
	unsigned char c=0;
	FILE *f1, *f2;
	//out.open("C:\\Users\\shimk\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\Crypto1\\Crypto1\\Vigenere_shifrtext.txt");
	//out.seekp(0);
	//in.open(file);
	//in.seekg(0);
	f1 = fopen(file, "rb");
	f2 = fopen("C:\\Users\\shimk\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\Crypto1\\Crypto1\\Vigenere_shifrtext.txt", "wb");
	int k, p=0;
	int P[] = { 13, 23, 29, 17, 17 };
	for (int i = 0; i < 5; i++)
		if (P[i] > size) {
			P[i] = P[i] % size;
			printf("%d ", P[i]);
		}
	printf("\n");
	while (c!=255)
	{
		for (int i = 0; i < 5 && c!=255; i++)
		{
		x:
			c = fgetc(f1);
			//in >> c;
			if (c == 13) goto x;
			if (c == 255) break;
			//if (in.eof()) break;
			while (1)
			{
				c++;
				if (c == 255) 
					c = 0;
				k = alfavit[c];
				if (k != 0) p++;
				if (p == P[i]) break;
			}
			fprintf(f2, "%c", c);
			//out << c;

			p = 0;
		}
		if (c == '\0') break;
	}
	fclose(f1);
	fclose(f2);
	//in.close();
	//out.close();

}

void vig_decrypt(int Vig_key[], char* file, int alfavit[])
{
	unsigned char c = 0;
	FILE *f1;
	//outt.open("C:\\Users\\shimk\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\Crypto1\\Crypto1\\Vigenere_decrypt.txt");
	//outt.seekp(0);
	//inn.open(file);
	//inn.seekg(0);
	int k, p = 0;
	f1 = fopen(file, "rb");
	f2 = fopen("C:\\Users\\shimk\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\Crypto1\\Crypto1\\Vigenere_decrypt.txt", "wb");
	/*Vig_key[1] = 23;
	Vig_key[2] = 29;
	Vig_key[3] = 17;
	Vig_key[4] = 17;*/

	//while (!inn.eof())
	while (c!=255)
	{
		for (int i = 0; i < 5 && c!=255; i++)
		{
			c = fgetc(f1);
			//inn >> c;
			if (c==255) break;
			while (1)
			{
				if (Vig_key[i] == 0) break;
				c--;
				if (c == 0)
					c = 255;
				k = alfavit[c];
				if (k != 0) p++;
				if (p == Vig_key[i]) break;
			}
			//outt << c;
			fprintf(f2, "%c", c);
			p = 0;
		}
		if (c == '\0') break;
	}
	fclose(f1);
	fclose(f2);
	//inn.close();
	//outt.close();

}

int kaziski(const char* file)
{
	int l[50000];
	int nods[50000] = {};
	int nl = 0;
	char *s = (char *)calloc(1, sizeof(char));
	char fname[100];
	char c;
	unsigned int n = 0, i, j, keylen;
	is.open(file);
	is.seekg(0);
	while (!is.eof())
	{
		is.get(s[n++]);
		s = (char *)realloc(s, n + 1);
	}
	s[n] = '\0';
	char str[4], str_[4];
	int y = strlen(s);
	for (i = 0; i < strlen(s); ++i)
	{
		str[0] = s[i]; str[1] = s[i + 1]; str[2] = s[i + 2]; str[3] = '\0';
		for (j = i + 1; j < strlen(s); ++j)
		{
			str_[0] = s[j];
			str_[1] = s[j + 1];
			str_[2] = s[j + 2];
			str_[3] = '\0';
			if (!strcmp(str, str_))
				l[nl++] = j - i; //считаем расстояния первой триграммы до всех остальных (если мы нашли равные триграммы)
		}
	}
	for (i = 0; i<nl; ++i)
		for (j = i + 1; j<nl; ++j)
			nods[nod(l[i], l[j])]++; //считаем нод каждого числа с каждым
	keylen = 0;
	for (i = 2; i<50000; ++i) // цикл начинается от 2, так как в массиве nods на 1 месте всегда будет 0 (нод двух чисел не мб 1)
		if (nods[keylen]<nods[i]) keylen = i;
	free(s);
	is.close();
	return keylen;
}

int test_fridman1(char* file, double delta)
{
	char c=0;
	int l[128];
	int count = 0;
	int numcharr, num, i, j, k, o;
	int p;
	unsigned int n = 0;
	double ic = 0;
	static int array[256];
	static double arric[MAX_LUNGH_KEY] = { NULL }, str[MAX_LUNGH_KEY] = { NULL };
	if ((f1 = fopen(file, "rb")) == 0) printf("Error\n");
	while (c!=EOF)
	{
		c = fgetc(f1); 
		n++;
	}


	double del = delta;
	for (i = 1; i < MAX_LUNGH_KEY; i++) //i - кол-во строк, на которые разбиваем текст (то есть длина ключа)
	{
		num = (int)(n / i) + 1;
			for (j = 1; j <= n; j+=i)
			{
				c = fgetc(f1);
				fseek(f1, j, SEEK_SET);
				array[c]++;
			}

			for (o = 1; o <= 256; o++)
			{
				if (array[o] != 0) {
					arric[i] += ((float)(array[o] * (array[o] - 1.0)) / (num*(num - 1.0)));
				}
				else {
					arric[i] += 0;
				}
			}
			if (abs(delta - arric[i]) < del)
			{
				del = abs(delta - arric[i]);
				key = i;
			}
			count++;
			for (k = 1; k <= i; k++)
				arric[k] = 0;
			for (k = 1; k <= 256; k++)
				array[k] = 0;

	}
	printf("\Fridman I test. Length for key = %d\n", key);
	fclose(f1);
	return key;

}
void kryptoanalyze(int* coll, char* letter, char* file1, int key_length, int num)
{
	FILE *ff;
	char tmp3[255];
	if ((ff = fopen(file1, "rb")) == 0) printf("Error\n");
	int p = 0;
	char *Yt = (char*)malloc(num + 1);
	memset(Yt, 0, sizeof(Yt));
	for (int i = 0; i < num; i++) //записываем первый столбец в Yi
	{
		Yt[i] = fgetc(ff);
		fseek(ff, key_length - 1, SEEK_CUR);
		p++;
	}
	Yt[num] = '\0';
	for (int i = 0; i < 255; i++) {
		coll[i] = NULL; letter[i] = NULL; tmp3[i] = NULL;
	}
	for (int k = 0; Yt[k] != '\0'; k++)
	{
		int curr = Yt[k];
		coll[curr]++;
		tmp3[curr]= Yt[k];
	}
	int i = 0;
	/*for (int k = 0; k < 254; k++)
	{
		if (tmp3[k] != 0) {
			letter[i] = tmp3[k]; i++;
		}
	}*/
	int tmp2;
	char tmp1;
	
	for (int j = 0; j < 253; j++)
	{
		int k = 0;
		for (int i = j+1; i < 254; i++)
		{
			if (coll[j] < coll[i])
			{
				tmp1 = tmp3[j];
				tmp3[j] = tmp3[i];
				tmp3[i] = tmp1;
				tmp2 = coll[j];
				coll[j] = coll[i];
				coll[i] = tmp2;
			}
		}
	}
	for (int k = 0; k < 254; k++)
	{
		if (tmp3[k] != 0) {
			letter[i] = tmp3[k]; i++;
		}
	}
	fclose(ff);
}

void test_fridman2(char* file, double delta, int key_length,/*char letter[],*/ int alfavit[], char* name, int fl)
{
	//key_length = 5;
	int size = 0;
	unsigned char c = 0;
	int numcharr, i, j, k;
	int p=0, q=0;
	unsigned int n = 0;
	double ic = 0;
	int pos=0;
	int tmp;
	static double MI;
	int l[256];
	int count = 0;
	static int array1[256], array2[256];
	if ((f1 = fopen(file, "rb")) == 0) printf("Error\n");
	while (1)
	{
		c = fgetc(f1);
		if (c != 255) n++; 
		else break;
	}
	for (i = 0; i < 256; i++)
		if (alfavit[i] != 0)
			size++;
	fseek(f1, pos, SEEK_SET);
	int num = 0;
	if (n % key_length == 0) num = n / key_length;
	else num = n / key_length + 1; //num - кол-во строк
	tmp = n%num; 
	if (tmp != 0)
		tmp = num - tmp;
	tmp = key_length - tmp; 
	tmp--;

	char* Yi = (char*)malloc(num + 1);
	char *Yj = (char*)malloc(num + 1);
	char *Ytmp = (char*)malloc(num + 1);
	memset(Yi, 0, sizeof(Yi));
	memset(Yj, 0, sizeof(Yj));
	memset(Ytmp, 0, sizeof(Ytmp));
	for (i = 0; i < num; i++) 
	{
		fread(&Yi[i], 1, sizeof(char), f1);
		fseek(f1, key_length-1, SEEK_CUR);
		p++;
	}
	int o;
	Yi[num] = '\0';
	for (i = 1; i < key_length; i++)
	{
		q = 0;
		fseek(f1, pos + i, SEEK_SET);
		for (j = 0; j < num; j++)
		{
			q++;
			//Yj[j] = fgetc(f1);
			fread(&Yj[j], 1, sizeof(char), f1);
			fseek(f1, key_length-1, SEEK_CUR);
		}
		if (tmp == 0)
			Yj[num - 1] = '\0';
		else
		{
			Yj[num] = '\0';
			tmp--;
		}
		double del = delta;
		for (j = 0; j < size; j++)
		{
			if (j != 0)
			{
				for (k = 0; Yj[k] != '\0'; k++)
				{
					int curr = Yj[k];
					int flag = 0;
					while (flag != 1)
					{
						while (alfavit[++curr] == 0)
						{
							if (curr == 255)
								curr = 0;
						}
						flag = 1;
					}
					Yj[k] = curr;
				}
			}

			int f1, f2 = 0;
			MI = 0;
			int m;
			for (k = 0; k < 256; k++)
			{
				f1 = 0;
				f2 = 0;
				for (m = 0; Yj[m] != '\0'; m++)
					if (k == Yj[m])
						f1++;
				for (m = 0; Yi[m] != '\0'; m++)
					if (k == Yi[m])
						f2++;
				MI += f1*f2;
			}
			MI /= /*(float)p*q*/strlen(Yi)*strlen(Yj);;
			//для смещения между соседними столбцами
			if (abs(delta - MI) < del)
			{
				del = abs(delta - MI);
					l[count] = size - j;
			}
		}
		printf("Smeshenie = %d \n", l[count]);
		count++;
	}
	fclose(f1);
	free(Yi);
	free(Yj);
	free(Ytmp);
	int stolb1num[255], stolb1numshifr[255];
	char	stolb1lett[255], stolb1lettshifr[255];
	kryptoanalyze(stolb1num, stolb1lett, name, key_length, num);
	kryptoanalyze(stolb1numshifr, stolb1lettshifr, file, key_length, num);


	int Vig_key[10]{ 0 };
	for (i = 0; i < 256; i++)
	{
		if ((i == stolb1lett[0]) && (alfavit[i]!=0))
			while (i != stolb1lettshifr[0])
			{
				if (alfavit[i] != 0) {
					Vig_key[0]++;
				}
				i++;
				if (i == 255) i = 0;
			}
		if (Vig_key[0]!=0) break;
	}
	printf("\n1st simbol for Vigenere key = %d", Vig_key[0]);
	printf("\nVigenere key: (%d, ", Vig_key[0]);
		for (i = 1; i < key_length; i++)
		{
			Vig_key[i] = Vig_key[0] + l[i - 1];
			
			if (i == key_length - 1) {
				printf("%d", Vig_key[i]);
				break;
			}
			printf("%d, ", Vig_key[i]);
		}
	printf(")\n");
	fclose(f1);
	vig_decrypt(Vig_key, file, alfavit);

}
