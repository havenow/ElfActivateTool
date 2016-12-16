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
	char *t = pStrBuffer; //Ŀ��ָ����ָ��ԭ��ͷ
	while (*pStrBuffer != '\0') //�����ַ���s
	{
		if (*pStrBuffer != pStrFind) //�����ǰ�ַ�����Ҫɾ���ģ��򱣴浽Ŀ�괮��
			*t++ = *pStrBuffer;
		pStrBuffer++; //�����һ���ַ�
	}
	*t = '\0'; //��Ŀ�괮��������
}

inline int delSubStr(const char *str_in, const char *str_sub, char *str_out)
{
	if (NULL == str_in || NULL == str_sub || NULL == str_out)
		return 0;
	int start = 0;       /* ��¼��ʼ�Ƚ��±� */
	int count = 0;    /* ��¼�Ӵ����� */
	int j = 0;              /* ��¼�Ӵ����±� */
	int k = 0;            /* ��¼����ַ������±� */

	for (int i = 0; str_in[i] != '\0'; i++)
	{
		start = i;      /* ��ʱ����Ƚ��±� */
		j = 0;           /* ÿ�ο�ʼ�Ƚϵ�ʱ���Ӵ�����0��ʼ,�����һ���ַ���ȣ�
						 ��ô�ͽ��űȽ���һ���ַ������������һ��ѭ�� */

		while ((str_in[i] != '\0') && (str_sub[j] != '\0') && (str_in[i] == str_sub[j]))
		{
			i++;        /* Դ������һ��λ�� */
			j++;        /* �ִ�����һ��λ�� */
		}

		if (str_sub[j] != '\0')                             /* ��������Ӵ� */
		{
			str_out[k++] = str_in[start];     /* ����ǰ�Ƚϵ�����ַ������� */
		}
		else                         /* ������Ӵ� */
		{
			count++;
			i--;           /* ��Ϊ����forѭ��֮�󣬽�����һ��ѭ����ʱ��Ҫ����i++������� */
		}
	}

	return count;
}

#endif
