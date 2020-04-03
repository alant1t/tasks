#pragma once

#include <QMainWindow>

#include "ui_ClusterizerDialog.h"

#include "PointContainer.h"
#include "FileHandler.h"
#include "DbscanClusterizer.h"
#include "GraphHandler.h"




class ClusterizerDialog : public QMainWindow
{
	Q_OBJECT

public:
	ClusterizerDialog(QWidget *parent = Q_NULLPTR);
	~ClusterizerDialog();

	

public slots:
	void doTheThing();

	void readData();
	void saveData();
	void clear();
	
	void classifyData();
	void showClusters(Clusters& clusters);
	
private:
	Ui::ClusterizerDialog ui;

	bool			m_isProcessSuccessful;
	
	string			m_fileName;
	int				m_nRequiredNearby;
	double			m_epsNeighbourhood;
		
	FileHandler*	m_fileHandler;
	DbscanClusterizer* m_clusterizer;
	GraphHandler*	m_graph;

	Points			m_purePoints;
	Points			m_classifiedPoints;
	Clusters		m_clusters;
};



