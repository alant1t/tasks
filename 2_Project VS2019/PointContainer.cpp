#include "PointContainer.h"

Point::Point() {
	m_coordinates.clear();
	m_state = -1; // not visited
}

Point::Point(vector<double>& coordinates) {
	m_coordinates.clear();
	m_coordinates.swap(coordinates);
	m_state = -1; // not visited
}

Point::~Point() {

}

void Point::clear() {
	m_coordinates.clear();
	m_state = -1; // not visited
}

int Point::getSize() {
	return m_coordinates.size();
}

void Point::pushCoordinate(double* coordinate) {
	if (coordinate != NULL) {
		m_coordinates.push_back(*coordinate);
	}
}

double	Point::getCoordinate(int no) {
	return m_coordinates.at(no);
}

bool Point::isVisited() {
	if (m_state == -1) {
		return false;
	}
	else {
		return true;
	}
}

int Point::getState() {
	return m_state;
}

void Point::setState(int state) {
	m_state = state;
	return;
}




Cluster::Cluster()
{
}

Cluster::~Cluster()
{
}

void Cluster::setCoords(vector<double>& abscisses, vector<double>& ordinates)
{
	m_abscisses = abscisses;
	m_ordinates = ordinates;
}

void Cluster::getCoords(vector<double>& abscisses, vector<double>& ordinates)
{
	abscisses = m_abscisses;
	ordinates = m_ordinates;
}

void Cluster::pushX(double x)
{
	m_abscisses.push_back(x);
}

void Cluster::pushY(double y)
{
	m_ordinates.push_back(y);
}