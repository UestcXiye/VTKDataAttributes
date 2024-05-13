#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VTKDataAttributes.h"

#include <QVTKOpenGLNativeWidget.h>

class VTKDataAttributes : public QMainWindow
{
	Q_OBJECT

public:
	VTKDataAttributes(QWidget* parent = nullptr);
	~VTKDataAttributes();

private:
	Ui::VTKDataAttributesClass ui;

	QVTKOpenGLNativeWidget* _pVTKWidget = nullptr;
};
