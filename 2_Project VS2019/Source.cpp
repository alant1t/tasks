#include "ClusterizerDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	ClusterizerDialog* dlg = new ClusterizerDialog;
	dlg->show();
	return a.exec();
}