#include "actionwidget.h"

ActionWidget::ActionWidget(QWidget *parent, int index) :
	QWidget(parent),
	index(index),
	layout_main(new QGridLayout(this)),
	widget_layout_call(new QWidget(this)),
	layout_call(new QHBoxLayout(this)),
	label_name(new QLabel("Display Name:", this)),
	label_declare(new QLabel("Declaration:", this)),
	label_icon(new QLabel("Icon:", this)),
	label_call_A(new QLabel("[return_type] [fn_name](", this)),
	label_call_B(new QLabel(");", this)),
	label_define(new QLabel("Definition:", this)),
	lineEdit_name(new QLineEdit(this)),
	lineEdit_declare(new QLineEdit(this)),
	comboBox_param(new QComboBox(this)),
	comboBox_icon(new QComboBox(this)),
	textEdit_define(new QTextEdit(this))
{
	layout_main->layout()->setMargin(0);
	layout_call->layout()->setMargin(0);

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

	widget_layout_call->setLayout(layout_call);

	layout_call->addWidget(label_call_A);
	layout_call->addWidget(comboBox_param);
	layout_call->addWidget(label_call_B);

	layout_main->addWidget(label_name, 0, 1);
	layout_main->addWidget(lineEdit_name, 0, 2);
	layout_main->addWidget(label_declare, 1, 1);
	layout_main->addWidget(lineEdit_declare, 1, 2);
	layout_main->addWidget(widget_layout_call, 2, 1, 1, 2);
	layout_main->addWidget(label_icon, 0, 0);
	layout_main->addWidget(comboBox_icon, 1, 0, 2, 1);
	layout_main->addWidget(label_define, 3, 0, 1, 3);
	layout_main->addWidget(textEdit_define, 4, 0, 1, 3);

	//QObject::connect(this->lineEdit_name, &QLineEdit::textChanged, this, &ActionWidget::text_changed);
}

ActionWidget::~ActionWidget()
{
	delete layout_main;
	delete layout_call;
	delete label_name;
	delete label_declare;
	delete label_icon;
	delete label_call_A;
	delete label_call_B;
	delete label_define;
	delete lineEdit_name;
	delete lineEdit_declare;
	delete comboBox_param;
	delete comboBox_icon;
	delete textEdit_define;
}

void ActionWidget::text_changed()
{
//	if (lineEdit_name->text().size() == 0) {
//		emit info_cleared(index);
//	} else if (lineEdit_name->text().size() == 1) {
//		emit info_added();
//	}
}
