#include "GraphHandler.h"

GraphHandler::GraphHandler()
{
	m_PointsToPlot.clear();
	nGraphs = 0;
	setApperiance();
	this->replot();
}

GraphHandler::~GraphHandler() {

}

void GraphHandler::initialize()
{
	m_PointsToPlot.clear();
	nGraphs = 0;
	this->clearGraphs();
	this->replot();
}

void GraphHandler::setApperiance() {
	
	this->setLocale(QLocale(QLocale::Russian, QLocale::Russia));
	//Очищаем старую разметку
	this->plotLayout()->clear();

	//Устанавливаем и настраиваем заголовок
	//this->plotLayout()->insertRow(0);
	//QCPTextElement* title = new QCPTextElement(this);
	////title->setText(tr("Graph"));
	//this->plotLayout()->addElement(0, 0, title);

	//Устанавливаем и настраиваем главный холст
	this->plotLayout()->insertRow(0);
	QCPAxisRect* mainAxisRect = new QCPAxisRect(this);
	//mainAxisRect->axis(QCPAxis::atLeft)->setLabel("Random wobbly lines value");
	this->plotLayout()->addElement(0, 0, mainAxisRect);

	//Настраиваем взаимодействия
		
	//Настраиваем дополнительные объекты
}

void GraphHandler::setData(vector<double>* keys, vector<double>* values) {
	//Функция преобразует два входных вектора
	//в вектор, удобный для QCustomPlot - QVector<QCPGraphData>
	
	if (keys->size() == values->size()) {
		QCPGraphData tempGraphData;
		VEC_QCP_GR_DATA tempGraph;
    
		int i = 0;
		while (i != keys->size()) {
			tempGraphData.key = keys->at(i);
			tempGraphData.value = values->at(i);
			tempGraph.push_back(tempGraphData);
			i++;
		}
		m_PointsToPlot.swap(tempGraph);
	}
}

void GraphHandler::plotData() {
    //Добавляем один график
	this->addGraph();

	// Set graph color
	QColor color;
	QCPScatterStyle scatter(QCPScatterStyle::ssDisc, 6);
	switch (nGraphs)
	{
	case 0:
		color.setRgb(255, 0, 0, 255);
		//scatter.setShape(QCPScatterStyle::ssCircle);
		break;
	case 1:
		color.setRgb(255, 155, 0, 255);
		//scatter.setShape(QCPScatterStyle::ssCross);
		break;
	case 2:
		color.setRgb(255, 255, 0, 255);
		//scatter.setShape(QCPScatterStyle::ssDiamond);
		break;
	case 3:
		color.setRgb(0, 255, 0, 255);
		//scatter.setShape(QCPScatterStyle::ssSquare);
		break;
	case 4:
		color.setRgb(0, 255, 255, 255);
		//scatter.setShape(QCPScatterStyle::ssPlus);
		break;
	case 5:
		color.setRgb(255, 0, 255, 255);
		//scatter.setShape(QCPScatterStyle::ssTriangle);
		break;
	}
	
	//Отрисовываем график по нашим данным
	this->graph(nGraphs)->data()->set(m_PointsToPlot);
	this->graph(nGraphs)->setLineStyle(QCPGraph::lsNone);
	this->graph(nGraphs)->setScatterStyle(scatter);
	this->graph(nGraphs)->setPen(QPen(color));

	//Установим область, которая будет показываться на графике
	this->rescaleAxes(true);
	this->axisRect()->axis(QCPAxis::atBottom)->scaleRange(1.1);
	this->axisRect()->axis(QCPAxis::atLeft)->scaleRange(1.2);
	
	// Increase graph counter
	nGraphs++;
}



