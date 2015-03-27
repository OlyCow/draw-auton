#include "actionwidget.h"

ActionWidget::ActionWidget(ActionDefine* parentDefine, QWidget *parentWidget) :
	parent(parentDefine),
	index(0),
	QWidget(parentWidget),
	layout_scroll(new QHBoxLayout(this)),
	scrollArea(new QScrollArea(this)),
	layout_main(new QGridLayout()),
	widget_layout_call(new QWidget(this)),
	layout_call(new QHBoxLayout()),
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
	pushButton_set_icon(new QPushButton("", this)),
	textEdit_define(new QTextEdit(this))
{
	layout_scroll->addWidget(scrollArea);
	layout_scroll->setMargin(0);

	scrollArea->setLayout(layout_main);
	scrollArea->setMinimumHeight(270);
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setFrameShadow(QFrame::Plain);
	scrollArea->setLineWidth(0);

	layout_main->layout()->setMargin(4);
	layout_call->layout()->setMargin(0);

	lineEdit_name->setStyleSheet("font: bold 10pt");
	lineEdit_name->setFocusPolicy(Qt::ClickFocus);
	lineEdit_name->setClearButtonEnabled(true);

	lineEdit_declare->setStyleSheet("font: 10pt \"Droid Sans Mono\"");
	lineEdit_declare->setFocusPolicy(Qt::ClickFocus);
	lineEdit_declare->setClearButtonEnabled(true);

	label_call_A->setStyleSheet("font: 10pt \"Droid Sans Mono\"");
	label_call_B->setStyleSheet("font: 10pt \"Droid Sans Mono\"");

	comboBox_param->setStyleSheet("font: 10pt \"Droid Sans Mono\"");
	comboBox_param->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	comboBox_param->setFocusPolicy(Qt::ClickFocus);
	comboBox_param->setEditable(true);
	comboBox_param->setInsertPolicy(QComboBox::NoInsert);
	comboBox_param->lineEdit()->setClearButtonEnabled(true);

	comboBox_icon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	comboBox_icon->setIconSize(QSize(32, 45));
	comboBox_icon->setFocusPolicy(Qt::ClickFocus);
	for (int i=0; i<definitions::ICON_NUM; i++) {
		comboBox_icon->addItem(QIcon(definitions::icon[i]), "");
	}

	pushButton_set_icon->setFixedWidth(45);
	pushButton_set_icon->setFocusPolicy(Qt::ClickFocus);
	pushButton_set_icon->setIcon(QIcon(":/icons/aperture.png"));

	textEdit_define->setStyleSheet("font: 10pt \"Droid Sans Mono\"");
	textEdit_define->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
	textEdit_define->setMinimumHeight(140);
	textEdit_define->setFocusPolicy(Qt::ClickFocus);
	textEdit_define->setLineWrapMode(QTextEdit::NoWrap);
	textEdit_define->setAcceptRichText(false);

	widget_layout_call->setLayout(layout_call);
	layout_call->setSpacing(2);

	layout_call->addWidget(label_call_A);
	layout_call->addWidget(comboBox_param);
	layout_call->addWidget(label_call_B);
	layout_call->addSpacing(30);
	layout_call->addWidget(pushButton_set_icon);

	layout_main->addWidget(label_name, 0, 1);
	layout_main->addWidget(lineEdit_name, 0, 2);
	layout_main->addWidget(label_declare, 1, 1);
	layout_main->addWidget(lineEdit_declare, 1, 2);
	layout_main->addWidget(widget_layout_call, 2, 1, 1, 2);
	layout_main->addWidget(label_icon, 0, 0);
	layout_main->addWidget(comboBox_icon, 1, 0, 2, 1);
	layout_main->addWidget(label_define, 3, 0, 1, 3);
	layout_main->addWidget(textEdit_define, 4, 0, 1, 3);

	QObject::connect(	comboBox_param->lineEdit(),		&QLineEdit::editingFinished,
						this,							&ActionWidget::param_changed);

	QObject::connect(	lineEdit_name,		&QLineEdit::textChanged,
						this,				&ActionWidget::info_changed		);
	QObject::connect(	lineEdit_declare,	&QLineEdit::textChanged,
						this,				&ActionWidget::info_changed		);
	QObject::connect(	comboBox_param,		static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
						this,				&ActionWidget::info_changed		);
	QObject::connect(	comboBox_param,		&QComboBox::editTextChanged,
						this,				&ActionWidget::info_changed		);
	QObject::connect(	comboBox_icon,		static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
						this,				&ActionWidget::info_changed		);
	QObject::connect(	textEdit_define,	&QTextEdit::textChanged,
						this,				&ActionWidget::info_changed		);
}

ActionWidget::~ActionWidget()
{
	// TODO: pointer to parent should NOT be deleted here?
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
	delete pushButton_set_icon;
	delete textEdit_define;
	delete layout_main;
	delete scrollArea;
	delete layout_scroll;
}

std::vector<ActionParam*> ActionWidget::get_params()
{
	std::vector<ActionParam*> return_list;
	for (int i=0; i<comboBox_param->count(); i++) {
		ActionParam* new_param = new ActionParam(0, comboBox_param->itemText(i));
		return_list.push_back(new_param);
	}
	return return_list;
}

void ActionWidget::info_changed()
{
	bool do_add = false;
	bool do_clear = true;

	int total_size = 0;
	total_size += lineEdit_name->text().size();
	total_size += lineEdit_declare->text().size();
	total_size += textEdit_define->toPlainText().size();
	total_size += comboBox_param->currentText().size();

	do_add = do_add || (total_size > 0);
	do_add = do_add || (comboBox_icon->currentIndex() != 0);
	do_add = do_add || (comboBox_param->currentIndex() > 0);

	do_clear = do_clear && (total_size == 0);
	do_clear = do_clear && (comboBox_param->count() == 0);

	if (do_add) {
		emit info_added();
		emit info_updated(this);
	} else if (do_clear) {
		emit info_cleared(this);
	}
}

void ActionWidget::param_changed()
{
	int current_index = comboBox_param->currentIndex();
	if (comboBox_param->lineEdit()->text().size() == 0) {
		if (comboBox_param->count() > 0) {
			emit param_cleared(current_index);
			comboBox_param->removeItem(current_index);
			comboBox_param->hidePopup();
		}
	} else {
		bool isUnique = true;
		int originalIndex = 0;
		for (int i=0; i<comboBox_param->count(); i++) {
			if (comboBox_param->itemText(i) == comboBox_param->lineEdit()->text()) {
				isUnique = false;
				originalIndex = i;
				break;
			}
		}
		if (isUnique) {
			ActionParam* new_param = new ActionParam(0, comboBox_param->currentText());
			emit param_added(new_param);
			comboBox_param->addItem(comboBox_param->currentText());
		} else {
			comboBox_param->lineEdit()->clear();
			comboBox_param->setCurrentIndex(originalIndex);
		}
	}
}
