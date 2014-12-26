#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

class SetupWindow;

class ActionWidget : public QWidget
{
	Q_OBJECT

	friend class SetupWindow;

public:
	ActionWidget(QWidget *parent = 0);
	~ActionWidget();

signals:

public slots:

private:
	QGridLayout* layout;
	QLabel* label_name;
	QLabel* label_declare;
	QLineEdit* lineEdit_name;
	QLineEdit* lineEdit_declare;
	QTextEdit* textEdit_define;
};

#endif // ACTIONWIDGET_H
