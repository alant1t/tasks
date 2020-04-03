#ifndef FILE_HANDLER
#define FILE_HANDLER

#include <fstream>
#include <string>

#include <QString>
#include <QDateTime>

#include "PointContainer.h"


class FileHandler {
public:
	FileHandler();
	~FileHandler();

	void initialize();
	void read(string fileName, Points* dataContainer);

	void checkData(Points* dataContainer);
	void write(string fileName, Points& dataContainer);

private:
	string              m_fileName;
	vector<string>      m_fileOutputStrings;
	Points*				m_dataContainer;
	
	//основные методы
	void openFile(string fileName);
	void analyzeFile();

	//вспомогательные методы

};

#endif