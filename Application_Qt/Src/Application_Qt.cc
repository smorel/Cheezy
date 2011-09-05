#include <QtCore>
#include <QtGui>

#include "External.hpp"
#include "Private.hpp"
#include "Public.hpp"


static std::string kQtImplementation = "Qt";
#include "IconManager_Qt.cpp"
#include "SourceCodeController_Qt.cpp"
#include "SplitterController_Qt.cpp"
#include "TabController_Qt.cpp"
#include "MainController_Qt.cpp"
#include "ApplicationController_Qt.cpp"
#include "MenuController_Qt.cpp"
#include "ActionController_Qt.cpp"
#include "ToolbarController_Qt.cpp"

void linkApplicationQt(){
}
