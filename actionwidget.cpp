#include "actionwidget.h"

ActionWidget::ActionWidget(QWidget *parent, int index_assign) :
	QWidget(parent),
	index(index_assign),
	layout(new QGridLayout(this)),
	label_name(new QLabel("Action Name:", this)),
	label_declare(new QLabel("Declaration/\nCall:", this)),
	lineEdit_name(new QLineEdit(this)),
	lineEdit_declare(new QLineEdit(this)),
	textEdit_define(new QTextEdit(this))
{
	layout->layout()->setMargin(0);

	lineEdit_name->setStyleSheet("font: bold 10pt");
	lineEdit_name->setFocusPolicy(Qt::ClickFocus);
	lineEdit_name->setClearButtonEnabled(true);

	lineEdit_declare->setStyleSheet("font: 10pt \"Droid Sans Mono\"");
	lineEdit_declare->setFocusPolicy(Qt::ClickFocus);
	lineEdit_declare->setClearButtonEnabled(true);

	textEdit_define->setStyleSheet("font: 10pt \"Droid Sans Mono\"");
	textEdit_define->setFocusPolicy(Qt::ClickFocus);
	textEdit_define->setLineWrapMode(QTextEdit::NoWrap);
	textEdit_define->setAcceptRichText(false);

	layout->addWidget(label_name, 0, 0);
	layout->addWidget(lineEdit_name, 0, 1);
	layout->addWidget(label_declare, 1, 0);
	layout->addWidget(lineEdit_declare, 1, 1);
	layout->addWidget(textEdit_define, 2, 0, 1, 2);

	QObject::connect(this->lineEdit_name, &QLineEdit::textChanged, this, &ActionWidget::text_changed);
}

ActionWidget::~ActionWidget()
{
	delete layout;
	delete label_name;
	delete label_declare;
	delete lineEdit_name;
	delete lineEdit_declare;
	delete textEdit_define;
}

void ActionWidget::text_changed()
{
	if (lineEdit_name->text().size() == 0) {
		emit info_cleared(index);
	} else if (lineEdit_name->text().size() == 1) {
		emit info_added();
	}
}
