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
	ActionWidget(QWidget *parent = 0, int index_assign = 0);
	~ActionWidget();

signals:
	void info_added();
	void info_cleared(int index_emit);

public slots:
	void text_changed();

private:
	int index;
	QGridLayout* layout;
	QLabel* label_name;
	QLabel* label_declare;
	QLineEdit* lineEdit_name;
	QLineEdit* lineEdit_declare;
	QTextEdit* textEdit_define;
};

#endif // ACTIONWIDGET_H
