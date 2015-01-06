#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include "definitions.h"

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QIcon>

class ActionDefine;
class SetupWindow;

class ActionWidget : public QWidget
{
	Q_OBJECT

	friend class ActionDefine;
	friend class SetupWindow;

public:
	ActionWidget(QWidget *parent = 0, int index = 0);
	~ActionWidget();

	void setIndex(int input)	{index = input;}

	int getIndex()	{return index;}

signals:
	void info_added();
	void info_cleared(int index);
	void info_updated(ActionWidget*);
	void param_added();
	void param_cleared(int index);

public slots:
	void info_changed();
	void param_changed();

private:
	int index;

	QGridLayout* layout_main;
	QWidget* widget_layout_call;
	QHBoxLayout* layout_call;
	QLabel* label_name;
	QLabel* label_declare;
	QLabel* label_icon;
	QLabel* label_call_A;
	QLabel* label_call_B;
	QLabel* label_define;
	QLineEdit* lineEdit_name;
	QLineEdit* lineEdit_declare;
	QComboBox* comboBox_param;
	QComboBox* comboBox_icon;
	QPushButton* pushButton_set_icon;
	QTextEdit* textEdit_define;
};

#endif // ACTIONWIDGET_H
