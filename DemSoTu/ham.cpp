#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "library.h"
#include <wchar.h>
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#define max 1000
#define max_char 30
wchar_t List[27][4];	//Cac nguyen am trong tieng Viet
wchar_t VowelList[5] = { 'a','e','i','o','u' };

void DocThuVien(FILE * pFile, wchar_t **String, int &n)
{
	for (int i = 0; i < n; i++)
	{
		fgetws(String[i], max_char, pFile);
	}
}

void GetSentence(FILE *pFile, wchar_t line[])
{
	if (!pFile)
	{
		wprintf(L"ERROR: Cannot open file\n");
		return;
	}
	rewind(pFile);
	fgetws(line, max, pFile);
	wchar_t *temp = &line[1];
	wcscpy(line, temp);
}

void Destroy(wchar_t **&String, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(String[i]);
	}
	free(String);
}

int NumberOfSingleWord(wchar_t line[])
{
	int len = 0;
	if (line[0] != ' ') len++;
	for (int i = 1; line[i]; i++)
	{
		if (line[i] != ' '&&line[i - 1] == ' ') len++;
	}
	return len;
}

/*
bool BinarySearch(wchar_t **String, wchar_t text[], int n)
{
	int left = 0;
	int right = n - 1;
	int mid;
	if (wcscmp(text, String[left]) < 0 || wcscmp(text, String[right]) > 0) return false;	//Nam ngoai vung
	while (left + 1 < right)
	{
		mid = (left + right) / 2;
		int temp = wcscmp(text, String[mid]);
		wprintf(L"\n%s %d", String[mid], temp);
		if (temp == 0) return true;
		if (temp > 0)
		{
			left = mid;
		}
		else if (temp < 0)
		{
			right = mid;
		}
	}
	return false;
}
*/

bool Search(wchar_t **String, wchar_t text[], int n)
{
	for (int i = 0; i < n; i++)
	{
		
		if (wcscmp(String[i], text) == 0) return true;
	}
	return false;
}


int CompoundWord(wchar_t line[], wchar_t **String, int &TuLay, int &Word, int n)
{
	TuLay = 0;
	int WordInRest = NumberOfSingleWord(line);	//So tu don con lai chua co xet
	Word = 0;
	int CompoundWord = 0;
	int i = 0;
	wchar_t lasttext[max_char];
	lasttext[0] = '\0';
	CreateList();
	CreateVowelList();
	while (WordInRest)
	{
		for (int m = 4; m >= 1; m--)	//So tu don se lay ra kiem tra
		{
			if (m > WordInRest) continue;	//Neu so tu don xet nhieu hon so tu don con lai thi ko xet
			int lastIndex = i;				//Phong khi tu do ko ton tai thi tra i ve cho cu
			wchar_t text[max_char];			//Luu tu dang xet
			int temp = m;					//Bien temp chi so tu don trong 1 tu con phai lay ra
			int j = 0;						//Bien j la index cua text
			while (1)
			{
				if (line[i] == ' ' || line[i] == '\0')
				{
					temp--;
					if (temp == 0)break;
				}
				text[j++] = line[i++];
			}
			text[j++] = '\n';
			text[j] = '\0';
			
			
			if (wcscmp(text, lasttext)==0)		//Neu 2 tu ke nhau ma giong nhau thi ko xet
			{
				i = lastIndex;
				text[0] = '\0';
				continue;
			}
			if (Search(String, text, n))	//Kiem tra tu do co ton tai hay khong
			{
				Word++;	
				if (m >= 2)CompoundWord++;
				if (m == 2)
				{
					if (LaTuLay(text))
					{
						TuLay++;
						CompoundWord--;
					}
				}
				wcscpy(lasttext, text);
				WordInRest -= m;			//So tu don con lai giam xuong
				i++;						//Skip dau ' '
				break;
			}
			else
			{
				i = lastIndex;
				text[0] = '\0';
				continue;
			}
		}
	}
	return CompoundWord;
}

void XoaKyTu(wchar_t text[],int num,int &len)
{
	for (int i = num;i < len - 1;i++)
	{
		text[i] = text[i + 1];
	}
	len--;
}

void ChuanHoaDau(wchar_t text[])
{
	int len = wcslen(text);
	int i = 0;
	while (text[i] == 32)
	{
		XoaKyTu(text, i, len);
	}
	for (int i = 0;i < len;i++)
	{
		if ((text[i] >= 33 && text[i] <= 47) || (text[i] >= 91 && text[i] <= 96) || (text[i] >= 58 && text[i] <= 64) || (text[i] >= 123 && text[i] <= 126))
		{
			XoaKyTu(text, i, len);
			i--;
		}
		if (text[i] == ' '&&text[i + 1] == ' ')
		{
			XoaKyTu(text, i, len);
			i--;
		}
	}
	if (text[len - 1] == ' ')text[len - 1] = 0;
	text[len] = 0;
}

bool LaTuLay(wchar_t text[])
{
	wchar_t word1[10];	// word dung de luu tu don
	wchar_t word2[10];
	int i = 0;
	while (text[i] != ' ') word1[i] = text[i++];
	word1[i++] = '\0';
	for (int j = 0;;)
	{
		if (text[i] == '\n')
		{
			word2[j] = '\0';
			break;
		}
		word2[j++] = text[i++];
	}

	wchar_t temp1[10], temp2[10];
	for (int i = 0; i < 27; i++)
	{
		int j;
		wcscpy(temp1, word1);
		wcscpy(temp2, word2);
		for (j = 0; List[i][j] != '\0'&&word1[j] != '\0'&&word2[j] != '\0'; j++);
		temp1[j] = '\0';
		temp2[j] = '\0';
		if (wcscmp(temp1, temp2) == 0 && wcscmp(temp1, List[i]) == 0) return true;
	}
	if (LayAm(word1, word2)) return true;	
	return false;
}

void CreateList()
{
	FILE *pFile = NULL;
	pFile = _wfopen(L"List_PhuAm.txt", L"r,ccs=UTF-16LE");
	for (int i = 0; i < 27; i++)
	{
		fgetws(List[i], 4, pFile);
	}
	fclose(pFile);
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0;; j++)
		{
			if (List[i][j] == '\n')
			{
				List[i][j] = '\0';
				break;
			}
		}
	}
	List[26][1] = '\0';
	//Cho List[8] bi loi nen em danh sua thu cong
	List[8][0] = 's';
	List[8][1] = '\0';
}

bool LayAm(wchar_t word1[], wchar_t word2[])
{
	ChuanHoa(word1);
	ChuanHoa(word2);
	int len1 = wcslen(word1);
	int len2 = wcslen(word2);
	
	len1--;
	len2--;
	while (!LaNguyenAm(word1[len1]) && !LaNguyenAm(word2[len2]))
	{
		if (word1[len1] != word2[len2]) return false;
		len1--;
		len2--;
	}
	int flag = 0;	//neu so nguyen am la 2 thi chi can giong 1 la duoc
	while (LaNguyenAm(word1[len1]) && LaNguyenAm(word2[len2]))
	{
		if (word1[len1] == word2[len2]) return true;
	}
	return false;
}

bool LaNguyenAm(wchar_t word)
{
	for (int i = 0; i < 5; i++)
	{
		if (word == VowelList[i]) return true;
	}
	return false;
}

