#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QDebug>

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QIcon>

#include "definitions.h"
#include "actionparam.h"

class ActionDefine;
class SetupWindow;

class ActionWidget : public QWidget
{
	Q_OBJECT

	friend class SetupWindow;

public:
	ActionWidget(ActionDefine* parentDefine, QWidget *parentWidget = NULL);
	~ActionWidget();

	void set_parent(ActionDefine* ptr)	{ parent = ptr; }
	ActionDefine* get_parent()			{ return parent; }

	void set_index(int input)	{ index = input; }
	int get_index()				{ return index; }

	void set_icon(int index)			{ comboBox_icon->setCurrentIndex(index); }
	void set_name(QString name)			{ lineEdit_name->setText(name); }
	void set_declare(QString declare)	{ lineEdit_declare->setText(declare); }
	void set_define(QString define)		{ textEdit_define->setText(define); }

	int get_icon()			{ return comboBox_icon->currentIndex(); }
	QString* get_name()		{ return new QString(lineEdit_name->text()); }
	QString* get_declare()	{ return new QString(lineEdit_declare->text()); }
	QString* get_define()	{ return new QString(textEdit_define->toPlainText()); }

signals:
	void info_added();
	void info_cleared(ActionWidget*);
	void info_updated(ActionWidget*);
	void param_added(ActionParam*);
	void param_cleared(ActionParam*);
	void param_cleared(int);

public slots:
	void info_changed();
	void param_changed();

private:
	ActionDefine* parent;
	int index;

	QHBoxLayout* layout_scroll;
	QScrollArea* scrollArea;
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
