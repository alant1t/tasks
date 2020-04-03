/*

rev.0 01.09.2019 Создание класса

	Текущая программа генерирует внешний вид и логику функционирования графика

**********************************
*/

#ifndef GRAPHHANDLER
#define GRAPHHANDLER

#include <QVector>

using namespace std;

#include "qcustomplot.h"

typedef QVector<QCPGraphData> VEC_QCP_GR_DATA;

class GraphHandler : public QCustomPlot
{
public:
	GraphHandler();
	~GraphHandler();


	void initialize();
	void setData(vector<double>* keys, vector<double>* values);
	void setApperiance();
	void plotData();
		
private:
	VEC_QCP_GR_DATA m_PointsToPlot;
	int				nGraphs;
	

};

#endif // !GRAPHHANDLER

