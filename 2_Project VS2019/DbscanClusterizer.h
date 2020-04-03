#ifndef DBSCAN_CLUSTERIZER
#define DBSCAN_CLUSTERIZER

#define sqr(x) ((x) * (x))

#include <vector>
#include <list>
#include <math.h>

using namespace std;

#include "PointContainer.h"

class DbscanClusterizer
{
public:
	DbscanClusterizer();
	~DbscanClusterizer();

	virtual void	initialize();
	virtual void	setPureData(Points& data);
	virtual	void	getClusteredData(Points& data);
	virtual void	getClusters(Clusters& clusters);
	void			setRequiredNearby(int* requiredNearby);
	void			setNeighbourhood(double* neighbourhood);
	virtual void	addPoint(Point& point);
	virtual void	computeDimensions();

	virtual void	clusterize();

protected:
	
	virtual double	computeDistance(Point* p1, Point* p2); //computes Euclidean distance
	virtual int		findNeighbours(Point* p1, list<Point*>& neighbours);
	virtual void	expandCluster(Point* point, list<Point*>& neighbours, int clusterNo);

private:
	Points			m_points;
	Clusters		m_clusters;
	int				m_nDimensions;
	   
	int				m_nRequiredNearby;
	double			m_epsNeighbourhood;
};

#endif

