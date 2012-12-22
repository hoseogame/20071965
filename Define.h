#ifndef DEFINE_H_
#define DEFINE_H_

//------------------------------------------------------------------------
//
//  [11/18/2012 KimSiHoon]
//
//  Name:   Define.h
//
//  Desc:   ���������� ���� ���� �� Ÿ�� , �Լ����� �����Ѵ�.    
//
//  Author: ����� (bongnam_go@naver.com) 
//
//------------------------------------------------------------------------

//------------------------------  Include  ------------------------------------
// System Include 
//-----------------------------------------------------------------------------
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

//-----------------------------  CURSOR_TYPE  ---------------------------------
// Ŀ���� Ÿ������
//-----------------------------------------------------------------------------
typedef enum 
{ 
	NOCURSOR, 
	SOLIDCURSOR,
	NORMALCURSOR 

} CURSOR_TYPE;

//-------------------------------  Position  ----------------------------------
// ��ǥ Ŭ����
//-----------------------------------------------------------------------------
class Position
{

public: 

	Position(int x,int y): x_(x),y_(y)
	{}
	~Position(){}
	int x_;
	int y_;

};

//----------------------------  Grobal Funtion  -------------------------------
// �ֿܼ� ��ƿ��Ƽ �Լ�
//-----------------------------------------------------------------------------
void SetCursorType(CURSOR_TYPE c);
void MoveCursor(Position pos);
int Getchon(Position pos);
void DrawObject(Position pos, char text);
void DrawObject(Position pos, int item);
void WaitAnyKey();

#endif