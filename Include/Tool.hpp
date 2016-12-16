#ifndef _TOOL_HPP_2016_12_16
#define _TOOL_HPP_2016_12_16 

inline void AtxGetFileName(const char* path_buffer, char* textout){
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char ext[_MAX_EXT];
	char fname[_MAX_FNAME];
	_splitpath(path_buffer, drive, dir, fname, ext);
	sprintf(textout, "%s%s", fname, ext);
};

inline void AtxGetFileExt(const char* path_buffer, char* textout){
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char ext[_MAX_EXT];
	char fname[_MAX_FNAME];
	_splitpath(path_buffer, drive, dir, fname, ext);
	sprintf(textout, "%s", ext);
};

inline void AtxGetFilePath(const char* path_buffer, char* textout){
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char ext[_MAX_EXT];
	char fname[_MAX_FNAME];
	_splitpath(path_buffer, drive, dir, fname, ext);
	sprintf(textout, "%s%s", drive, dir);
	int len = strlen(textout);
	if (len >= 1) textout[len - 1] = '\0';
};

inline void AtxGetFileTitle(const char* path_buffer, char* textout){
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char ext[_MAX_EXT];
	char fname[_MAX_FNAME];
	_splitpath(path_buffer, drive, dir, fname, ext);
	sprintf(textout, "%s", fname);
};

//"List of devices attached\r\n7N2SQL14CS045388\tdevice\r\n\r\n"
//"List of devices attached\r\n7N2SQL14CS045388\tdevice\r\n7N2SSE15BC038695\tdevice\r\n\r\n"
inline int getSubStrCount(char* pStrBuffer, const char* pStrFind)
{
	int nCount = 0;
	char * pPos = pStrBuffer;
	if (NULL == pStrBuffer || NULL == pStrFind)
		return nCount;
	while ((pPos = strstr(pPos, pStrFind)) != NULL)
	{
		nCount++;
		pPos++;
	}
	return nCount;
}

inline void delChr(char* pStrBuffer, const char pStrFind)
{
	if (NULL == pStrBuffer)
		return;
	char *t = pStrBuffer; //目标指针先指向原串头
	while (*pStrBuffer != '\0') //遍历字符串s
	{
		if (*pStrBuffer != pStrFind) //如果当前字符不是要删除的，则保存到目标串中
			*t++ = *pStrBuffer;
		pStrBuffer++; //检查下一个字符
	}
	*t = '\0'; //置目标串结束符。
}

inline int delSubStr(const char *str_in, const char *str_sub, char *str_out)
{
	if (NULL == str_in || NULL == str_sub || NULL == str_out)
		return 0;
	int start = 0;       /* 记录开始比较下标 */
	int count = 0;    /* 记录子串个数 */
	int j = 0;              /* 记录子串的下标 */
	int k = 0;            /* 记录结果字符串的下标 */

	for (int i = 0; str_in[i] != '\0'; i++)
	{
		start = i;      /* 临时保存比较下标 */
		j = 0;           /* 每次开始比较的时候，子串都从0开始,如果第一个字符相等，
						 那么就接着比较下一个字符，否则进入下一轮循环 */

		while ((str_in[i] != '\0') && (str_sub[j] != '\0') && (str_in[i] == str_sub[j]))
		{
			i++;        /* 源串后移一个位置 */
			j++;        /* 字串后移一个位置 */
		}

		if (str_sub[j] != '\0')                             /* 如果不是子串 */
		{
			str_out[k++] = str_in[start];     /* 将当前比较的这个字符存入结果 */
		}
		else                         /* 如果是子串 */
		{
			count++;
			i--;           /* 因为返回for循环之后，进行下一次循环的时候还要进行i++的运算的 */
		}
	}

	return count;
}

#endif
