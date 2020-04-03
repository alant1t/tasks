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

private:
	vector<double>	m_coordinates;
	int				m_state;		// -1 - not visited; 0 - noise; 1...n - core member of cluster n;
};

typedef list<Point> Points;

class Cluster
{
public:
	Cluster();
	~Cluster();

	void pushX(double x);
	void pushY(double y);
	void setCoords(vector<double>& abscisses, vector<double>& ordinates);
	void getCoords(vector<double>& abscisses, vector<double>& ordinates);

private:
	vector<double> m_abscisses;
	vector<double> m_ordinates;
};

typedef map<int, Cluster> Clusters;