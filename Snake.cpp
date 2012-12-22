#include "Snake.h"

//------------------------------- InitSnake -----------------------------------
// ���� ����/��ġ/������ �ʱ�ȭ���ش�.
//-----------------------------------------------------------------------------
void Snake::InitSnake()
{
	//���� ���� ��ǥ���� ����.
	snake_trace_.clear();

	//�ʱ���� ��ǥ�� �־��ش�.
	//��ǥ�� �׻� ���Ǳ��� + 1��ŭ�� �־���Ѵ�.
	//�׷��߸� ���� ���������� ���������� Snake_Game���� ������ �� �ִ�.
	snake_trace_.push_back(Position(7,5));
	snake_trace_.push_back(Position(6,5));
	snake_trace_.push_back(Position(5,5));
	snake_trace_.push_back(Position(4,5));

	current_position_ = Position(7,5);
	direction_ = RIGHT;
	length_ = 2;
	grow_goal_ = 0;
}

//-------------------------------- Update -------------------------------------
// ���� ������ �����̰�, ��ǥ�� ��������Ʈ�� �־��ش�.
//-----------------------------------------------------------------------------
void Snake::Update()
{
	switch (direction_) 
	{

	case LEFT:
		current_position_.x_ --;
		break;

	case RIGHT:
		current_position_.x_ ++;
		break;

	case UP:
		current_position_.y_ --;
		break;

	case DOWN:
		current_position_.y_ ++;
		break;
	}

	//��ǥ�� ����Ѵ�.
	snake_trace_.push_front(current_position_);

	//���� �ڶ�� �ִ����̸� ��ǥ�� �����ʴ´�.
	if(this->IsGrowing() == false)
	{
		snake_trace_.pop_back();
	}
}

int Snake::IsCollide()
{
	//���� ��ġ�� ���� dummy�� ����ִ´�.
	int dummy = Getchon(current_position_);

	//���� ������ ��ġ�� ������� �ʴٸ�,
	if(dummy != ' ')
	{
		//���̰��� Ȯ���Ѵ�.
		//���̳� �ڽ��� ���̶��
		//COLLIDE���� ��ȯ�Ѵ�.
		if(dummy == 'M' || dummy == '#')
		{
			return COLLIDE;
		}
		//�ƴ϶�� �������� �������̴�.
		else
		{
			//dummy�� char���̱� ������
			//int�� �ٲٱ����� 49�� ���ش�.
			grow_goal_ = dummy-49;

			return EAT_ITEM;
		}
	}

	return NOT_COLLIDE;
}

//------------------------------- IsGrowing -----------------------------------
// ���� ���� Ŀ���� �ִ��� Ȯ���Ѵ�.
//-----------------------------------------------------------------------------
bool Snake::IsGrowing()
{
	//grow_goal�� 0���� �۴ٸ� ũ������ �ʴٴ°��̴�.
	//���� ũ���ִٸ� 1�����Ӵ� ���� 1�� �ø���,
	//grow_goal�� 1 ���� ��Ų��.
	if(grow_goal_ < 0)
	{
		return false;
	}
	else
	{
		grow_goal_--;
		length_++;
	}

	return true;
}