#pragma once

#include <vector>
#include <list>
#include <map>

using namespace std;

class Point
{
public:

	Point();
	Point(vector<double>& coordinates);
	~Point();

	void	clear();
	int		getSize();

	void	pushCoordinate(double* coordinate);
	double	getCoordinate(int no);

	bool	isVisited();

	void	setState(int state);
	int		getState();

	void	setSource(void* source);
	void	getSource(void* source);

private:
	void*			m_source;
	vector<double>	m_coordinates;
	int				m_state;		// -1 - not visited; 0 - noise; 1...n - core member of cluster n;
};

typedef list<Point> Points;
typedef map<int, Points> Clusters;