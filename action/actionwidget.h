#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QIcon>

#include "definitions.h"

class ActionDefine;
class SetupWindow;

class ActionWidget : public QWidget
{
	Q_OBJECT

	friend class SetupWindow;

public:
	ActionWidget(int index, ActionDefine* parentDefine, QWidget *parentWidget = NULL);
	~ActionWidget();

	void setIndex(int input)			{ index = input; }
	void set_parent(ActionDefine* ptr)	{ parent = ptr; }

	int getIndex()				{ return index; }
	ActionDefine* get_parent()	{ return parent; }

	int get_icon()			{ return comboBox_icon->currentIndex(); }
	QString* get_name()		{ return new QString(lineEdit_name->text()); }
	QString* get_declare()	{ return new QString(lineEdit_declare->text()); }
	QString* get_define()	{ return new QString(textEdit_define->toPlainText()); }

signals:
	void info_added();
	void info_cleared(int index);
	void info_updated(ActionWidget*);
	void param_added(QString*);
	void param_cleared(int index);

public slots:
	void info_changed();
	void param_changed();

private:
	int index;
	ActionDefine* parent;

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
