#ifndef __PATH_FINDING__
#define __PATH_FINDING__

#include "cocos2d.h"
#include "MathUtils.h"

struct m_Node
{
	Point position;

	m_Node* preNode = nullptr;

	/* 估价函数 f = g + h */
	float f;
	float g;

	bool operator < (const m_Node& rhs) const {
		return f > rhs.f;
	}
};

struct m_Waypoint
{
	Point position;

	/* 相连的下一个结点 */
	m_Waypoint* preWaypoint;

	m_Waypoint* nxtWaypoint;

	/* 航点所属区域 */
	int area;
};

class PathFinding
{
private:
	PathFinding();
	~PathFinding();

public:

	static PathFinding* getInstance();

	/* 获得地图 */
	void getMap(TMXTiledMap* map);

	/*  利用A Star寻路算法在地图中寻找路径 */
	bool AStarInArea(Point startPosition, Point endPosition, std::vector<Point>& Path);

	/* 利用Bresenham算法规划航点之间的路径 */
	void BresenhamBetweenWaypoints(Point startPosition,Point endPosition,std::vector<Point>& Path);

	void updateUnsafePlace(Point position);

	bool isNotSafety(Point position) const;

	m_Waypoint findWayPointInArea(int area);

	/* 判断一个点所属的区域 */
	int findArea(Point position);

private:

	/* 划分瓦片地图的区域 */
	void divideArea(int rows, int colums);

	void addWayPoints(Point position);

	static float h(Point nowPoint, Point endPoint);

	static PathFinding* m_Instance;

	TMXTiledMap* m_TiledMap;;

	std::set <Point> _isNotSafety;

	/* 储存航点的数组 */
	std::vector <m_Waypoint> Waypoints;

	/* 地图每行的瓦片数 */
	int numbersOfRows;

	/* 地图每列的瓦片数 */
	int numbersOfColumns;

	/* 用来划分地图的区域 */
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
	for (unsigned int ix = 0; ix <= Waypoints.size() - 1; ix++)
	{
		if (Waypoints[ix].area == area)
		{
			return Waypoints[ix];
		}
	}
	return Waypoints[0];
}

#endif
