#ifndef SNAKE_H_
#define SNAKE_H_

//------------------------------------------------------------------------
//
//  [11/18/2012 KimSiHoon]
//
//  Name:   Snake.h
//
//  Desc:   Snake ���� 
//
//  Author: ����� (bongnam_go@naver.com) 
//
//------------------------------------------------------------------------

#include "Define.h"
#include <list>
#include <iostream>

class Snake
{

public:

	//���� �������� ����� ��ǥ ����Ʈ
	std::list<Position> typedef SNAKE_TRACE;

	//���� �浿üũ�� ���� Enumlator
	//COLLIDE = ���̳� ������ �浹, NOT_COLLIDE = �浹���� ,EAT_ITEM = �����۸���
	typedef enum { COLLIDE, NOT_COLLIDE, EAT_ITEM } SNAKE_COLLIDE;

	//���� ���� ����
	typedef enum{ LEFT=75, RIGHT=77 ,UP=72, DOWN=80 } DIRECTION;

public:

	Snake() : direction_(RIGHT),current_position_(7,5),life_(5),grow_goal_(0)
	{
		this->InitSnake();
	}

	~Snake()
	{
	}

	//���� �ʱ�ȭ
	void InitSnake();
	void Update();

	//�浹üũ
	int IsCollide();

	//���� ���� �ڶ�� �ִ��� üũ
	bool IsGrowing();

	int GetLife() const { return life_; }
	SNAKE_TRACE GetTrace() const { return snake_trace_; } 
	DIRECTION GetDirection() const { return direction_; }
	Position GetPosition() const { return current_position_; }
	int GetLength() const { return length_; }

	void SetDirection(DIRECTION direction) { direction_ = direction; }

	void DecreLife() 
	{
		if(life_ >= 0)
		{
			life_ --; 
		}
	}

private:

	//���� ��ǥ ����Ʈ
	SNAKE_TRACE snake_trace_;

	//���� ���� ����
	DIRECTION direction_;

	//���� �Ӹ��� ��ġ
	Position current_position_;

	//���
	int life_;

	//���� ����
	int length_;

	//�ڶ���� ���� ���� ��ǥġ
	int grow_goal_;

};
#endif