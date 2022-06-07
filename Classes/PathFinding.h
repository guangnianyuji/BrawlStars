#ifndef __PATH_FINDING__
#define __PATH_FINDING__

#include <new>
#include "cocos2d.h"
#include "Entity.h"
#include "MathUtils.h"
#include "AI.h"

struct m_Node
{
	Point position;

	m_Node* preNode = nullptr;

	/* ���ۺ��� f = g + h */
	float f;
	float g;

	bool operator < (const m_Node& rhs) const {
		return f > rhs.f;
	}
};

struct m_Waypoint
{
	Point position;

	/* ��������һ����� */
	m_Waypoint* preWaypoint;

	m_Waypoint* nxtWaypoint;

	/* ������������ */
	int area;
};

class PathFinding
{
private:
	PathFinding();
	~PathFinding();

public:

	static PathFinding* getInstance();

	/* ��õ�ͼ */
	void getMap(TMXTiledMap* map);

	/*  ����A StarѰ·�㷨�ڵ�ͼ��Ѱ��·�� */
	bool AStarInArea(Point startPosition, Point endPosition, std::vector<Point>& Path);

	/* ����Bresenham�㷨�滮����֮���·�� */
	void BresenhamBetweenWaypoints(Point startPosition,Point endPosition,std::vector<Point>& Path);

	void updateUnsafePlace(Point position);

	bool isNotSafety(Point position) const;

	m_Waypoint findWayPointInArea(int area);

	/* �ж�һ�������������� */
	int findArea(Point position);

private:

	/* ������Ƭ��ͼ������ */
	void divideArea(int rows, int colums);

	void addWayPoints(Point position);

	static float h(Point nowPoint, Point endPoint);

	static PathFinding* m_Instance;

	TMXTiledMap* m_TiledMap;;

	std::set <Point> _isNotSafety;

	/* ���溽������� */
	std::vector <m_Waypoint> Waypoints;

	/* ��ͼÿ�е���Ƭ�� */
	int numbersOfRows;

	/* ��ͼÿ�е���Ƭ�� */
	int numbersOfColumns;

	/* �������ֵ�ͼ������ */
	int x1, x2, y1, y2;
};

inline void PathFinding::updateUnsafePlace(Point position)
{
	_isNotSafety.insert(position);
}

inline bool PathFinding::isNotSafety(Point position) const
{
	std::set <Point>::iterator it;
	it = _isNotSafety.find(position);
	return it != _isNotSafety.end();
}

inline m_Waypoint PathFinding::findWayPointInArea(int area)
{
	for (int ix = 0; ix <= Waypoints.size() - 1; ix++)
	{
		if (Waypoints[ix].area == area)
		{
			return Waypoints[ix];
		}
	}
	return Waypoints[0];
}

#endif
