#include "MapManager.h"

MapManager *MapManager::instance_;

MapManager* MapManager::GetInstance()
{
	if(!instance_)
	{
		instance_ = new MapManager();
	}

	return instance_;
}

//------------------------------ RegisterMap ----------------------------------
// Map�� ����Ѵ�.
//-----------------------------------------------------------------------------
void MapManager::RegisterMap(Map* new_map)
{
	map_list_.push_back(new_map);
}

//----------------------------- GetMapFromID ----------------------------------
// ���̵� ������ �ش� Map�� ��ȯ�Ѵ�.
//-----------------------------------------------------------------------------
Map* MapManager::GetMapFromID(int id) const
{
	MAP_LIST::const_iterator it = map_list_.begin();

	for(it = map_list_.begin(); it != map_list_.end(); it++)
	{
		if((*it)->GetID() == id)
		{
			return (*it);
		}
	}

	return NULL;
}

//------------------------------ RemoveMap ------------------------------------
// ���̵� ������ �ش� Map�� �����̳ʿ��� �����.
//-----------------------------------------------------------------------------
void MapManager::RemoveMap(int id)
{    
	MAP_LIST::const_iterator it = map_list_.begin();

	for(it = map_list_.begin(); it != map_list_.end(); it++)
	{
		if((*it)->GetID() == id)
		{
			map_list_.erase(it);
		}
	}

	return;
} 

//----------------------------- Destory ---------------------------------------
// ��� �ڷḦ �����ϰ� �����.
//-----------------------------------------------------------------------------
void MapManager::Destory()
{
	for(MAP_LIST::const_iterator it = map_list_.begin(); it != map_list_.end(); it++)
	{
		(*it)->~Map();

		delete (*it);
	}

	map_list_.clear();
	delete instance_;
}
