#ifndef MAP_H_
#define MAP_H_

//------------------------------------------------------------------------
//
//  [11/18/2012 KimSiHoon]
//
//  Name:   Map.h
//
//  Desc:   MapŬ����, Map�� ��������� ���̵�� ���ϰ�θ� �Է��� �־���Ѵ�.
//			�ش� ���ϰ�ο� �ش��ϴ� ������ �о� ���� �ε��Ѵ�.
//
//  Author: ����� (bongnam_go@naver.com) 
//
//------------------------------------------------------------------------

#include <iostream>

class Map
{
public:

	explicit Map(int id, char *file_path) : id_(id)
	{
		file_path_ = new char[sizeof(file_path)+1];
		strcpy(file_path_,file_path);
	}
	~Map(){}

	int GetID() const { return id_; }
	bool LoadMap();

private :

	int id_;
	char* file_path_;


};


#endif