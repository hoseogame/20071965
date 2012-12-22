#include "Snake_Game.h"

//------------------------------- Snake_Game ----------------------------------
// ���ӿ� �ʿ��� ��, �ʿ� �޸𸮸� �Ҵ��ϰ� ������ �ʱ�ȭ ���ش�.
//-----------------------------------------------------------------------------
Snake_Game::Snake_Game() : gameover_(false) , item_num_(0) , speed_ (150) , kMaxItemPosHeigh(17), kMaxItemPosWidth(75)
{
	snake_ = new Snake();

	current_stage_ = STAGE_ONE;

	Map* stage_one = new Map(STAGE_ONE,"Stage1.txt");
	Map* stage_two = new Map(STAGE_TWO,"Stage2.txt");
	Map* stage_three = new Map(STAGE_THREE,"Stage3.txt");
	Map* stage_four = new Map(STAGE_FOUR,"Stage4.txt");

	MAP_MANAGER->RegisterMap(stage_one);
	MAP_MANAGER->RegisterMap(stage_two);
	MAP_MANAGER->RegisterMap(stage_three);
	MAP_MANAGER->RegisterMap(stage_four);

	this->SetGame();
    
    
    
};

//------------------------------- SetGame -------------------------------------
// ������ ó�� ���������� ���������� �� �� �ֵ��� ���ش�.
//-----------------------------------------------------------------------------
void Snake_Game::SetGame()
{
	while(true)
	{
		this->InitGame();
		
		//UI�� ���ؼ�
		MoveCursor(Position(14,21));
		puts("N = ���� �������� / P = ���� �������� / S = ����");

		int ch=getch();

		//Ű���� �ް�, N�̸� ������������ P�� ������������ S�� ������ ��������������.
		if (ch == 0xE0) 
		{
			getch();
		} 
		else 
		{
			if (tolower(ch) == 'n') 
			{
				if(current_stage_ < STAGE_FOUR)
				{
					current_stage_++;
				}
			}
			if (tolower(ch) == 'p') 
			{
				if(current_stage_ > STAGE_ONE)
				{
					current_stage_--;
				}
			}
			if (tolower(ch) == 's')
			{
				break;
			}
		}
	}

	//UI�� ���������,/
	MoveCursor(Position(14,21));
	puts("                                                 ");
}

//------------------------------- InitGame ------------------------------------
// ������ �ʱ�ȭ�Ѵ�.
//-----------------------------------------------------------------------------
bool Snake_Game::InitGame()
{
	SetCursorType(NOCURSOR);

	this->LoadGame();

	srand(time(NULL));

	//���� �����۸�ŭ �������� �׷��ش�.
	for (int i=item_num_;i<goal_item_num_;i++)
	{
		while(true)
		{
			Position dummy(rand()%kMaxItemPosWidth,rand()%kMaxItemPosHeigh);
			if(Getchon(dummy) == ' ')
			{
				DrawObject(dummy,rand()%9+1);
				break;
			}
		}
	}

	return true;
}

//------------------------------- LoadGame ------------------------------------
// ���ӿ� ���� ���������� �ش��ϴ� �ʰ� ������ �ҷ��´�.
//-----------------------------------------------------------------------------
void Snake_Game::LoadGame()
{
	system("cls");

	MAP_MANAGER->GetMapFromID(current_stage_)->LoadMap();

	switch(current_stage_)
	{
	case STAGE_ONE:
		{
			speed_ = 150;
			goal_item_num_ = 10;
			snake_->InitSnake();
		}
		break;
	case STAGE_TWO:
		{
			speed_ = 100;
			goal_item_num_ = 15;
			snake_->InitSnake();
		}
		break;
	case STAGE_THREE:
		{
			speed_ = 80;
			goal_item_num_ = 20;
			snake_->InitSnake();
		}
		break;
	case STAGE_FOUR:
		{
			speed_ = 50;
			goal_item_num_ = 25;
			snake_->InitSnake();
		}
		break;
	}

	this->DrawUI();
}

//-------------------------------- Input --------------------------------------
// ������� �Է°��� ó�����ִ� �Լ�
//-----------------------------------------------------------------------------
void Snake_Game::Input()
{
	int ch;

	if (!kbhit()) {
		return;
	}

	ch=getch();

	//���� ���� ��������� �ݴ�������δ� �������� ���Ѵ�.
	//�����̽��� ������ ����� �ִ�.
	if (ch == 0xE0 || ch == 0) 
	{
		ch=getch();
		switch (ch) 
		{
		case Snake::LEFT:
			if (snake_->GetDirection() != Snake::RIGHT) snake_->SetDirection(Snake::LEFT);
			break;
		case Snake::RIGHT:
			if (snake_->GetDirection() != Snake::LEFT) snake_->SetDirection(Snake::RIGHT);
			break;
		case Snake::UP:
			if (snake_->GetDirection() != Snake::DOWN) snake_->SetDirection(Snake::UP);
			break;
		case Snake::DOWN:
			if (snake_->GetDirection() != Snake::UP) snake_->SetDirection(Snake::DOWN);
			break;
		}
	}
	else
	{
		switch (tolower(ch))
		{
		case 27:
			SetCursorType(NORMALCURSOR);
			exit(0);
		case ' ':
			WaitAnyKey();
			break;
		}
	}
}

//-------------------------------- Update -------------------------------------
// ����
//-----------------------------------------------------------------------------
void Snake_Game::Update()
{
	//������� �Է��� �޴´�.
	this->Input();

	//���� �������� ������Ʈ�Ѵ�.
	snake_->Update();

	//���� ���� �浹�ߴ°�?
	switch(snake_->IsCollide())
	{
	case Snake::COLLIDE :
		{
			//���̳� ���� �浹�ߴٸ�,
			//�������� �ϳ� ���ҽ�Ų��.
			//���� ����� 0���� �۾����ٸ� ������ ������.
			//�׷��� �ʴٸ� ȭ���� �����ְ�, 0.5���� �������� ������ �ٽý����Ѵ�.
			snake_->DecreLife();

			if(snake_->GetLife() < 0)
			{
				this->SetGameOver(true);
				MoveCursor(Position(12,20));
				puts("������ �������ϴ�. �׸� ��� ������ �����ϼ���.");
			}
			else
			{
				this->InitGame();
				this->DrawUI();
				Sleep(500);
			}
		}
		break;

	case Snake::EAT_ITEM :
		{
			//�������� �Ծ��ٸ�,
			//���� �����۰��� ���������ش�.
			//���� ��ǥġ��ŭ �������� �Ծ��ٸ�
			//�������� Ŭ���� �̺�Ʈ�� �߻���Ű�� Ű�� �Է¹޾� �������������� ����.
			item_num_++;
			if (item_num_ == goal_item_num_) 
			{
				MoveCursor(Position(12,20));
				puts("�����մϴ�. �ƹ� Ű�� �����ø� ���� ���������� ���ϴ�.");
				WaitAnyKey();
				current_stage_++;
				item_num_ = 0;
				this->InitGame();
				Sleep(500);
			}
		}

		break;
	}
	Sleep(this->speed_);
}

//-------------------------------- Render -------------------------------------
// �����Լ�
//-----------------------------------------------------------------------------
void Snake_Game::Render()
{
	//UI�� �׸���.
	this->DrawUI();

	//���� ������ �޾ƿ´�.
	Snake::SNAKE_TRACE dummy = snake_->GetTrace();

	//������� ���� �׸���.
	for(Snake::SNAKE_TRACE::iterator it = dummy.begin(); it != dummy.end(); it++)
	{
		DrawObject((*it),'#');
	}

	//�ǵڴ� ' '�� �����ش�.
	//���۾��� ���Ѵٸ� �������� ������ ȭ�鿡�� ��� ���� ������ ���δ�.
	//���� ��ü ȭ���� ����� �ٽ� �׸��� �۾��� �ϸ�
	//ȭ���� �����̴� ������ �Ͼ��.
	DrawObject(dummy.back(),' ');

	//������ġ���� ���� �Ӹ��� �׷��ش�.
	DrawObject(snake_->GetPosition(),'S');
}

//--------------------------------- Run ---------------------------------------
// ����
//-----------------------------------------------------------------------------
void Snake_Game::Run()
{
	while(!this->IsGameOver())
	{
		Update();
		Render();
	}
}

//--------------------------------- DrawUI ------------------------------------
// UI�� �׸���.
//-----------------------------------------------------------------------------
void Snake_Game::DrawUI()
{
	MoveCursor(Position(0,23));printf("�������� : %d",current_stage_+1);
	MoveCursor(Position(20,23));printf("���� �� : %d",snake_->GetLife());
	MoveCursor(Position(40,23));printf("              ");
	MoveCursor(Position(40,23));printf("���� ���� : %d",goal_item_num_ - item_num_);
	MoveCursor(Position(60,23));printf("���� ���� : %d",snake_->GetLength());
}

//--------------------------------- ~Snake_Game -------------------------------
// �Ҹ���
//-----------------------------------------------------------------------------
Snake_Game::~Snake_Game()
{
	MAP_MANAGER->Destory();
	delete snake_;
}