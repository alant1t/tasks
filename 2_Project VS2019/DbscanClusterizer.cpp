#include "DbscanClusterizer.h"

DbscanClusterizer::DbscanClusterizer() {
	m_points.clear();
	m_clusters.clear();
	m_nDimensions = 0;
	m_nRequiredNearby = 0;
	m_epsNeighbourhood = 0;
}

DbscanClusterizer::~DbscanClusterizer() {

}

void DbscanClusterizer::initialize()
{
	m_points.clear();
	m_clusters.clear();
	m_nDimensions = 0;
	m_nRequiredNearby = 0;
	m_epsNeighbourhood = 0;
}

void DbscanClusterizer::setPureData(Points& data) {
	m_points = data;
}

void DbscanClusterizer::getClusteredData(Points& data) {
	data = m_points;
}

void DbscanClusterizer::setRequiredNearby(int* requiredNearby) {
	if (requiredNearby != NULL) {
		m_nRequiredNearby = *requiredNearby;
	}
}

void DbscanClusterizer::setNeighbourhood(double* neighbourhood) {
	if (neighbourhood != NULL) {
		m_epsNeighbourhood = *neighbourhood;
	}
}

void DbscanClusterizer::addPoint(Point& point) {
	m_points.push_back(point);
}

void DbscanClusterizer::computeDimensions() {
	if (m_points.size() != 0 ) {
		m_nDimensions = m_points.front().getSize();
	}
}

double DbscanClusterizer::computeDistance(Point* p1, Point* p2) {
	if (m_nDimensions == -1) {
		return -1;
	}
	
	double distance = 0.0;
	double sum = 0.0;
	for ( int i = 0; i < m_nDimensions; i++) {
		sum += sqr( p1->getCoordinate(i) - p2->getCoordinate(i) );
	}
	distance = sqrt(sum);

	return distance;
}

int DbscanClusterizer::findNeighbours(Point* p1, list<Point*>& neighbours) {
	int nNeigbours = 0;
	int nPoints = m_points.size();
	list<Point*> tempNeighbours;

	list<Point>::iterator it = m_points.begin();
	while (it != m_points.end()) {
		if (p1 != &(*it)) {
			if (computeDistance(p1, &(*it)) < m_epsNeighbourhood) {
				tempNeighbours.push_back(&(*it));
				nNeigbours++;
			}
		}
		it++;
	}

	neighbours.swap(tempNeighbours);
	return nNeigbours;
}

void DbscanClusterizer::expandCluster(Point* point, list<Point*>& neighbours, int clusterNo) {
	point->setState(clusterNo);

	list<Point*> neighbourNeighbours;
	int nNeighbours = 0;
	Point* pickedOne;
	while ( !neighbours.empty() ) {
		pickedOne = neighbours.front();
		neighbours.pop_front();
		if ( !pickedOne->isVisited() ) {
			nNeighbours = findNeighbours(pickedOne, neighbourNeighbours);
			for (Point* p : neighbourNeighbours) {
				neighbours.push_back(p);
			}
		}
		pickedOne->setState(clusterNo);
	}
	return;
}

void DbscanClusterizer::clusterize() {
	
	// Create list of points to classify.
	list<Point*>		pointsToClassify;
	list<Point>::iterator it = m_points.begin();
	while ( it != m_points.end() ) {
		pointsToClassify.push_back(&(*it));
		it++;
	}
	
	list<Point*>		neighbours; 
	int nNeighbours = 0;
	Point* pickedOne;
	int clusterNo = 0;
	while ( !pointsToClassify.empty() ) {
		// Pick point.
		pickedOne = pointsToClassify.front();
		pointsToClassify.pop_front();

		if ( !pickedOne->isVisited() ) {
			// Find all neighbours.
			nNeighbours = findNeighbours(pickedOne, neighbours);
			// Classify it.
			if (nNeighbours < m_nRequiredNearby) {
				pickedOne->setState(0);
				neighbours.clear();
			}
			else {
				clusterNo++;
				expandCluster(pickedOne, neighbours, clusterNo);
			}
		}
	}

	// Classify probably noisy points.
	// Pick point, find neighbours
	// If any neighbour is core, than point is edge
	// else it is noise
	list<Point*> probablyNoise;

	it = m_points.begin();
	while (it != m_points.end()) {
		if (it->getState() == 0) {
			probablyNoise.push_back(&(*it));
		}
		it++;
	}

	while (!probablyNoise.empty()) {
		pickedOne = probablyNoise.front();
		probablyNoise.pop_front();
		nNeighbours = findNeighbours(pickedOne, neighbours);

		int state = 0;
		for (Point* p : neighbours) {
			state = p->getState();
			if ( state != 0 ) {
				pickedOne->setState(state);
				break;
			}
		}
	}

	// Create and fill cluster containers.
	Clusters clusters;
	Cluster tempCluster;
	int clusterKey;
	map<int, Cluster>::iterator i;
	for (Point p : m_points) {
		clusterKey = p.getState();
		i = clusters.find(clusterKey);
		if (i == clusters.end()) {
			tempCluster.pushX(p.getCoordinate(0));
			tempCluster.pushY(p.getCoordinate(1));
			clusters.emplace(pair<int, Cluster>(clusterKey, tempCluster));
		}
		else {
			i->second.pushX(p.getCoordinate(0));
			i->second.pushY(p.getCoordinate(1));
		}
	}
	m_clusters = clusters;
}

void DbscanClusterizer::getClusters(Clusters& clusters) {
	clusters = m_clusters;
}