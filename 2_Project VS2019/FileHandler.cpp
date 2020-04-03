#include "FileHandler.h"

FileHandler::FileHandler() {
	m_fileName.clear();
	m_fileOutputStrings.clear();
	m_dataContainer = NULL;
}

FileHandler::~FileHandler() {

}

void FileHandler::initialize() {
	m_fileName.clear();
	m_fileOutputStrings.clear();
	m_dataContainer = NULL;
}

//----------------------------------
// Загрузка данных из файла.
//----------------------------------
void FileHandler::read(string fileName, Points* dataContainer) {
	m_fileName = fileName;
	m_dataContainer = dataContainer;
	
	m_fileOutputStrings.clear();
	this->openFile(fileName);
	this->analyzeFile();
}

void FileHandler::openFile(string fileName) {
	fstream inf;
	inf.open(m_fileName, ios::in);
	if (!inf.is_open()) {
		string error = "Err!!Не удалось открыть файл.";
		throw error;
	}

	for (string str; getline(inf, str); ) {
		m_fileOutputStrings.push_back(str);
	}

	if (inf.bad()) {
		string error = "Err!!Ошибка при чтении файла.";
		throw error;
	}
	else if (inf.eof()) {

	}
	else if (inf.fail()) {
		string error = "Err!!Неверный формат файла.";
		throw error;
	}

	inf.close();
	return;
}

void FileHandler::analyzeFile() {
	vector<string>::iterator it = m_fileOutputStrings.begin();
	if (it == m_fileOutputStrings.end()) {
		string error = "Err!!Файл пуст.";
		throw error;
	}
	
	// Data block analysis.
	// string in file looks like this:
	// [-0.59910108  0.75331446]
	Points tempContainer;

	string			buff;
	vector<double>	coordinates;
	char			c;
	while (it != m_fileOutputStrings.end()) {
		if (*it == "") {
			continue;
		}
		
		buff.clear();
		coordinates.clear();
;		for (int i = 1; i < (it->size() - 1); i++ ) {
			c = it->at(i);
			if ( c != ' ' ) {
				buff.push_back(c);
			}
			else {
				if (buff.empty()) {
					continue;
				}
				coordinates.push_back(stod(buff));
				buff.clear();
			}			
		}
		if ( !buff.empty() ) {
			coordinates.push_back(stod(buff));
		}
		tempContainer.push_back(Point(coordinates));
		
		it++;
	}
	*m_dataContainer = tempContainer;
	return;
}




//----------------------------------
// Проверка данных на полноту.
//----------------------------------
void FileHandler::checkData(Points* dataContainer) {
	
}



//----------------------------------
// Выгрузка текстового документа.
//----------------------------------
void FileHandler::write(string fileName, Points& dataContainer) {
	fstream outf;
	outf.open(fileName, ios::out);
	if (!outf.is_open()) {
		string error = "Err!!Не удалось открыть файл.";
		throw error;
	}

	for (Point p : dataContainer ) {
		outf	<< p.getCoordinate(0) << " " 
				<< p.getCoordinate(1) << " " 
				<< p.getState() << "\n";
	}

	outf.close();
	return;
	
}