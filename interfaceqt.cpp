#include "interfaceqt.h"

InterfaceQt::InterfaceQt(QWidget *parent) : Interface(parent)
{

}

InterfaceQt::~InterfaceQt()
{

}

void InterfaceQt::show()
{
    mainWindow.show();
}

void InterfaceQt::displayData(DataSet *data)
{
    mainWindow.displayData(data);
}
