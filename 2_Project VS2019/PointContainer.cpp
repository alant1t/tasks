#include "PointContainer.h"

Point::Point() {
	m_source = nullptr;
	m_coordinates.clear();
	m_state = -1; // not visited
}

Point::Point(vector<double>& coordinates) {
	m_source = nullptr;
	m_coordinates.clear();
	m_coordinates = coordinates;
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

void Point::setSource(void* source) {
	m_source = source;
}

void Point::getSource(void* source) {
	source = m_source;
}

