#include "Define.h"

// test ��� ó�� �� ������


//-----------------------------  SetCursorType  -------------------------------
// Ŀ���� Ÿ������
//-----------------------------------------------------------------------------
void SetCursorType(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize=1;
		CurInfo.bVisible=FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize=100;
		CurInfo.bVisible=TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize=20;
		CurInfo.bVisible=TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}

//------------------------------  MoveCursor  ---------------------------------
// Ŀ���� �ش� ��ǥ�� �����δ�.
//-----------------------------------------------------------------------------
void MoveCursor(Position pos)
{
	COORD Pos = { pos.x_, pos.y_ };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//------------------------------  DrawObject  ---------------------------------
// �ش� ��ǥ�� text�� �Ѹ���.
//-----------------------------------------------------------------------------
void DrawObject(Position pos, char text)
{
	MoveCursor(pos);
	printf("%s",&text);
}

//------------------------------  DrawObject  ---------------------------------
// �ش� ��ǥ�� ���ڸ� �Ѹ���
//-----------------------------------------------------------------------------
void DrawObject(Position pos, int item)
{
	MoveCursor(pos);
	printf("%d",item);
}

//------------------------------  Getchon  ------------------------------------
// �ش� ��ǥ�� ���� char������ �о�´�.
//-----------------------------------------------------------------------------
int Getchon(Position pos)
{
	COORD Cur;
	Cur.X= pos.x_;
	Cur.Y= pos.y_;
	TCHAR Char;
	DWORD dwRead;

	ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE),
		&Char,1,Cur,&dwRead);
	return Char;
}

//------------------------------  WaitAnyKey  ---------------------------------
// �ϳ��� Ű�� �Էµɶ����� ��ٸ���.
//-----------------------------------------------------------------------------
void WaitAnyKey()
{
	int ch;

	ch=getch();
	if (ch==0xE0 || ch==0) {
		getch();
	}
}