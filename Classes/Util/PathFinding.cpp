#include "Util/PathFinding.h"

PathFinding* PathFinding::m_Instance = nullptr;

PathFinding::PathFinding()
{

}

PathFinding::~PathFinding()
{
}

PathFinding* PathFinding::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new (std::nothrow) PathFinding;
	}
	return m_Instance;
}

void PathFinding::getMap(TMXTiledMap* map)
{
	/* 导入外部地图 */
	m_TiledMap = map;

	/* 划分区域 */
	divideArea(m_TiledMap->getMapSize().width, m_TiledMap->getMapSize().height);

	auto ObjectGroup = m_TiledMap->getObjectGroup("objects");
	
	int index = 1;

	/* 加入航点 
	while (index<=20)
	{
		auto PlaceValueMap = ObjectGroup->getObject("Waypoint" + Value(index).asString());

		float WayPointX = PlaceValueMap.at("x").asFloat();
		float WayPointY = PlaceValueMap.at("y").asFloat();

		Point waypoint = Point(WayPointX, WayPointY);
		addWayPoints(waypoint);

		index++;
	}*/
}

bool PathFinding::AStarInArea(cocos2d::Point startPosition, Point endPosition,std::vector<Point>& Path)
{
	if (!Path.empty())
		Path.clear();

	startPosition = MathUtils::PositionToTiled(startPosition, m_TiledMap);
	endPosition = MathUtils::PositionToTiled(endPosition, m_TiledMap);

	std::map<cocos2d::Point, int> InOpenList;

	std::set<cocos2d::Point> InCloseList;

	std::priority_queue <m_Node*> openList;

	m_Node* start=new m_Node();

	start->position = startPosition;

	start->g = 0;

	start->f = start->g + h(startPosition, endPosition);

	openList.push(start);

	InOpenList[startPosition] = start->f;

	bool success = false;

	int cnt = 0;

	int size = openList.size();

	while (size!=0 && cnt<=10000)
	{
		cnt++;
		m_Node* nowPosition = openList.top();
		openList.pop();
		size--;

		/* 已经找到终点 */
		if (nowPosition->position == endPosition)
		{
			success = true;
			while (nowPosition != nullptr)
			{
				Path.push_back(MathUtils::TiledToPosition(nowPosition->position,m_TiledMap));
				m_Node* tmp = nowPosition;
				nowPosition = nowPosition->preNode;
				delete tmp;
			}

			while (!openList.empty())
			{
				m_Node* position = openList.top();
				delete position;
				openList.pop();
			}

			break;
		}
		else
		{
			InOpenList.erase(nowPosition->position);
			InCloseList.insert(nowPosition->position);

			for (int deltax = -1; deltax <= 1; deltax++)
			{
				for (int deltay = -1; deltay <= 1; deltay++)
				{
					if ((deltax != 0 || deltay != 0))
					{
						m_Node* nextPosition=new m_Node();
						nextPosition->position = nowPosition->position;
						nextPosition->g = nowPosition->g;

						nextPosition->position.x += deltax;
						nextPosition->position.y += deltay;

						if (nextPosition->position.x < 0 || nextPosition->position.x>60 ||
							nextPosition->position.y < 0 || nextPosition->position.y>60)
						{
							continue;
						}

						if (InCloseList.find(nextPosition->position) != InCloseList.end()
							|| isNotSafety(nextPosition->position))
						{
							delete nextPosition;
							continue;
						}

						nextPosition->g++;
						nextPosition->f = nextPosition->g + h(nextPosition->position, endPosition);

						/* 如果不在openList 中*/
						if (InOpenList.find(nextPosition->position) == InOpenList.end())
						{
							nextPosition->preNode = nowPosition;
							InOpenList[nextPosition->position] = nextPosition->f;
							openList.push(nextPosition);
							size++;
						}
						else
						{
							if (nextPosition->f < InOpenList[nextPosition->position])
							{
								nextPosition->preNode = nowPosition;
								InOpenList[nextPosition->position] = nextPosition->f;
								openList.push(nextPosition);
							}
						}
					}
				}
			}

		}
	}
	if (success)
		return true;
	else
		return false;

}


void PathFinding::BresenhamBetweenWaypoints(Point startPosition, Point endPosition, std::vector<Point>& Path)
{
	int stepx=0, stepy=0;

	startPosition = MathUtils::PositionToTiled(startPosition, m_TiledMap);
	endPosition = MathUtils::PositionToTiled(endPosition, m_TiledMap);

	Point nextPosition=startPosition;

	int deltax = endPosition.x - startPosition.x;
	int deltay = endPosition.y - startPosition.y;
	
	if (deltax < 0)
		stepx = -1;
	else
		stepx = 1;

	if (deltay < 0)
		stepy = -1;
	else
		stepy = 1;

	deltax = abs(deltax * 2);
	deltay = abs(deltay * 2);

	if (deltax > deltay)
	{
		int fraction = deltax * 2 - deltay;
		while (nextPosition.y != endPosition.y)
		{
			if (fraction > 0)
			{
				nextPosition.x += stepx;
				fraction -= deltay;
			}
			nextPosition.y = nextPosition.y + stepy;
			fraction = fraction + deltax;
			Path.push_back(MathUtils::TiledToPosition(nextPosition,m_TiledMap));
		}
	}
	else
	{
		int fraction = deltax - deltay;
		while (nextPosition.x != endPosition.x)
		{
			if (fraction >= 0)
			{
				nextPosition.y = nextPosition.y + stepy;
				fraction -= deltax;
			}
			nextPosition.x = nextPosition.x + stepx;
			fraction = fraction + deltax;
			Path.push_back(MathUtils::TiledToPosition(nextPosition,m_TiledMap));
		}
	}
}

void PathFinding::divideArea(int rows, int colums)
{
	x1 = rows / 3;
	x2 = rows / 3 * 2;
	y1 = colums / 3;
	y2 = colums / 3 * 2;
}

void PathFinding::addWayPoints(Point position)
{
	m_Waypoint waypoint;
	waypoint.position = position;
	if (Waypoints.empty())
	{
		Waypoints.push_back(waypoint);
	}
	else
	{
		waypoint.preWaypoint = &Waypoints[Waypoints.size() - 1];

		Waypoints[Waypoints.size() - 1].nxtWaypoint = &waypoint;

		Waypoints.push_back(waypoint);
	}
	waypoint.area = findArea(waypoint.position);
}

int PathFinding::findArea(Point position)
{

	position = MathUtils::PositionToTiled(position, m_TiledMap);

	if (position.x > 0 && position.x <= x1)
	{
		if (position.y > 0 && position.x <= y1)
		{
			return 1;
		}
		if (position.y > y1 && position.y <= y2)
		{
			return 4;
		}
		if (position.y > y2 && position.y <= numbersOfColumns) 
		{
			return 7;
		}
	}
	else if (position.x > x1 && position.x <= x2)
	{
		if (position.y > 0 && position.x <= y1)
		{
			return 2;
		}
		if (position.y > y1 && position.y <= y2)
		{
			return 5;
		}
		if (position.y > y2 && position.y <= numbersOfColumns)
		{
			return 8;
		}
	}
	else if (position.x > x2 && position.x <= numbersOfRows)
	{
		if (position.y > 0 && position.x <= y1)
		{
			return 3;
		}
		if (position.y > y1 && position.y <= y2)
		{
			return 6;
		}
		if (position.y > y2 && position.y <= numbersOfColumns)
		{
			return 9;
		}
	}

	return 0;
}

float PathFinding::h(Point nowPosition, Point endPosition)
{
	return fabs(endPosition.x - nowPosition.x) + fabs(endPosition.y - nowPosition.y);
}


