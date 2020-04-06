#include "ClusterizerDialog.h"


ClusterizerDialog::ClusterizerDialog(QWidget *parent)
	: QMainWindow(parent)
{
	m_isProcessSuccessful = false;
	m_fileHandler = nullptr;
	m_clusterizer = nullptr;
	m_graph = new GraphHandler;
	m_fileName = "";
	m_nRequiredNearby = 0;
	m_epsNeighbourhood = 0.0;
	m_purePoints.clear();
	m_classifiedPoints.clear();
	m_clusters.clear();

	ui.setupUi(this);

	ui.gridLayout->addWidget(m_graph, 1, 0, 1, 2);
	ui.refreshButton->setEnabled(false);
		
	
	// Размещаем график
	connect( ui.readButton, SIGNAL(clicked()), this, SLOT(doTheThing()) );
	connect( ui.saveButton, SIGNAL(clicked()), this, SLOT(saveData()) );
	connect( ui.refreshButton, SIGNAL(clicked()), this, SLOT(refresh() ));
}

ClusterizerDialog::~ClusterizerDialog() 
{
	if (m_fileHandler != nullptr)	{	delete m_fileHandler; }
	if (m_clusterizer != nullptr)	{ delete m_clusterizer; }
	if (m_graph != nullptr)			{ delete m_graph; }
}

void ClusterizerDialog::doTheThing() {
	clear();
	readData();
	classifyData();
	showClusters(m_clusters);
	ui.refreshButton->setEnabled(true);
}

void ClusterizerDialog::refresh() {
	// Check if any data is loaded.
	if (m_purePoints.empty()) {
		ui.refreshButton->setEnabled(false);
		return;
	}

	// Clear.
	if (m_fileHandler != nullptr) { m_fileHandler->initialize(); }
	if (m_clusterizer != nullptr) { m_clusterizer->initialize(); }
	if (m_graph != nullptr) { m_graph->initialize(); }
	m_classifiedPoints.clear();
	m_clusters.clear();
		
	// Read user input.
	m_epsNeighbourhood = ui.epsLineEdit->text().toDouble();
	m_nRequiredNearby = ui.nReqLineEdit->text().toInt();
	
	// Clusterize.
	classifyData();
	showClusters(m_clusters);
}

void ClusterizerDialog::readData() 
{
	string inputPath;
	inputPath = QFileDialog::getOpenFileName(this, "Выбор входного каталога",
		"", tr("Text Files (*.txt)")).toStdString();
	if (inputPath.size() == 0) {
		return;
	}

	if (m_fileHandler == NULL) {
		m_fileHandler = new FileHandler();
	}

	string error = "";
	string generalInfo = "";
	string specialInfo = "";
	if (m_fileHandler != NULL) {
		m_fileHandler->initialize();
		try {
			int		tempN;
			double	tempEps;
			Points	tempPurePoints;

			tempN = ui.nReqLineEdit->text().toInt();
			tempEps = ui.epsLineEdit->text().toDouble();

			if (tempN <= 0) {
				return;
			}

			m_fileHandler->read(inputPath, &tempPurePoints);

			m_purePoints = tempPurePoints;
			m_epsNeighbourhood = tempEps;
			m_nRequiredNearby = tempN;
			
			m_isProcessSuccessful = true;
		}
		catch (string str) {
			generalInfo = str;
		}
		catch (exception & e) {
			generalInfo = "Err!!Прочитать файл не удалось.";
			error = e.what();
			specialInfo = "Описание ошибки: \"" + error + "\"";
		}
	}
	else {
		generalInfo = "Err!!Прочитать файл не удалось.";
		specialInfo = "Описание ошибки: \"Ошибка выделения памяти.\"";
	}

	if (m_isProcessSuccessful) {
		generalInfo = "Inf!!Файл успешно загружен.";
		m_isProcessSuccessful = false;
	}
	
	// this->showMessage(generalInfo + " " + specialInfo);

	return;
}

void ClusterizerDialog::classifyData()
{
	if (m_clusterizer == NULL) {
		m_clusterizer = new DbscanClusterizer;
	}

	string error = "";
	string generalInfo = "";
	string specialInfo = "";
	if (m_clusterizer != NULL) {
		try {
			m_clusterizer->setPureData(m_purePoints);
			m_clusterizer->setRequiredNearby(&m_nRequiredNearby);
			m_clusterizer->setNeighbourhood(&m_epsNeighbourhood);
			m_clusterizer->computeDimensions();
			m_clusterizer->clusterize();
			m_clusterizer->getClusteredData(m_classifiedPoints);
			m_clusterizer->getClusters(m_clusters);

			m_isProcessSuccessful = true;
		}
		catch (string str) {
			generalInfo = str;
		}
		catch (exception & e) {
			generalInfo = "Err!!Разбить данные на кластеры не удалось.";
			error = e.what();
			specialInfo = "Описание ошибки: \"" + error + "\"";
		}
	}
	else {
		generalInfo = "Err!!Разбить данные на кластеры не удалось.";
		specialInfo = "Описание ошибки: \"Ошибка выделения памяти.\"";
	}

	if (m_isProcessSuccessful) {
		generalInfo = "Inf!!Данные успешно обработаны.";
		m_isProcessSuccessful = false;
	}

	// this->showMessage(generalInfo + " " + specialInfo);

	return;
}

void ClusterizerDialog::showClusters(Clusters& clusters)
{
	vector<double> abscisses;
	vector<double> ordinates;
	Clusters::iterator	i;
	Points::iterator	j;

	i = clusters.begin();
	while (i != clusters.end()) {
		j = i->second.begin();
		while ( j != i->second.end() ) {
			abscisses.push_back(j->getCoordinate(0));
			ordinates.push_back(j->getCoordinate(1));
			
			j++;
		}
		m_graph->setData(&abscisses, &ordinates);
		m_graph->plotData();
		abscisses.clear();
		ordinates.clear();

		i++;
	}
	
	m_graph->replot();
	return;
}

void ClusterizerDialog::saveData()
{
	string outputPath;
	outputPath = QFileDialog::getSaveFileName(this, "Выбор в",
		"", tr("Text Files (*.txt)")).toStdString();
	if (outputPath.size() == 0) {
		return;
	}

	if (m_fileHandler == NULL) {
		m_fileHandler = new FileHandler();
	}

	string error = "";
	string generalInfo = "";
	string specialInfo = "";
	if (m_fileHandler != NULL) {
		m_fileHandler->initialize();
		try {
			m_fileHandler->write(outputPath, m_classifiedPoints);
			m_isProcessSuccessful = true;
		}
		catch (string str) {
			generalInfo = str;
		}
		catch (exception & e) {
			generalInfo = "Err!!Записать файл не удалось.";
			error = e.what();
			specialInfo = "Описание ошибки: \"" + error + "\"";
		}
	}
	else {
		generalInfo = "Err!!Записать файл не удалось.";
		specialInfo = "Описание ошибки: \"Ошибка выделения памяти.\"";
	}

	if (m_isProcessSuccessful) {
		generalInfo = "Inf!!Файл успешно загружен.";
		m_isProcessSuccessful = false;
	}

	// this->showMessage(generalInfo + " " + specialInfo);

	return;

}

void ClusterizerDialog::clear()
{
	m_isProcessSuccessful = false;
	if (m_fileHandler != nullptr) { m_fileHandler->initialize(); }
	if (m_clusterizer != nullptr) { m_clusterizer->initialize(); }
	if (m_graph != nullptr) { m_graph->initialize(); }
	m_fileName = "";
	m_nRequiredNearby = 0;
	m_epsNeighbourhood = 0.0;
	m_purePoints.clear();
	m_classifiedPoints.clear();
	m_clusters.clear();
}
