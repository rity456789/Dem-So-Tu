void DocThuVien(FILE * pFile, wchar_t **String, int &n);
void GetSentence(FILE *pFile, wchar_t line[]);
void Destroy(wchar_t **&String, int n);
int NumberOfSingleWord(wchar_t line[]);
/*void DeleteSpace(wchar_t line[]);
void DeleteAlphabet(wchar_t String[], int k);
bool BinarySearch(wchar_t **String, wchar_t text[], int n);
int StringCompare(wchar_t String1[], wchar_t String2[]);*/
bool Search(wchar_t **String, wchar_t text[], int n);
int CompoundWord(wchar_t line[], wchar_t **String, int &TuLay, int &Word, int n);
bool LaTuLay(wchar_t text[]);
bool LayAm(wchar_t word1[], wchar_t word2[]);
void CreateList();
void CreateVowelList();
void ChuanHoa(wchar_t text[]);
bool LaNguyenAm(wchar_t word);
void XoaKyTu(wchar_t text[], int num, int &len);
void ChuanHoaDau(wchar_t text[]);