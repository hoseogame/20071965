#include "Map.h"

//------------------------------  LoadMap  ------------------------------------
// FilePath��ο� �ִ� �ؽ�Ʈ������ �а�, ȭ�鿡 �׸���.
// ������ @�� ��ħǥ�� ����־�߸� �Ѵ�.
//-----------------------------------------------------------------------------
bool Map::LoadMap()
{
	FILE *fp;

	fp = fopen(file_path_,"r");

	if(fp == NULL)
	{
		return false;
	}

	char ch;

	while(true)
	{
		ch = fgetc(fp);
		if(ch=='@') break;
		putchar(ch);
	}

	int f_close = fclose(fp);

	if(f_close != NULL)
	{
		return false;
	}

	return true;
}