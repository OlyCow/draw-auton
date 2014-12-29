#include "aboutwindow.h"
#include "ui_aboutwindow.h"

int AboutWindow::keys[10] = {	0x44, 0x45, 0x44, 0x49, 0x43,
								0x41, 0x54, 0x49, 0x4F, 0x4E	};

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::AboutWindow),
	current_pos(0)
{
	ui->setupUi(this);
	this->installEventFilter(this);
}

AboutWindow::~AboutWindow()
{
	delete ui;
}

void AboutWindow::on_pushButton_close_clicked()
{
	this->close();
}

bool AboutWindow::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* current_press = dynamic_cast<QKeyEvent*>(event);
		if (current_press->key() == keys[current_pos]) {
			current_pos++;
			if (current_pos == 10) {
				QString text_ee = "";
				text_ee += QString::fromUtf8("\xE7\x8C\xAE\xE7\xBB\x99");
				text_ee += QString::fromUtf8("\xE8\xB5\xB5\xE4\xB8\xB9\xE7\xAB\xB9");
				QLabel* label_ee = new QLabel(this);
				label_ee->setText(text_ee);
				label_ee->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
				ui->layout_window->addWidget(label_ee, 2, 0, 1, 2);
			}
		}
	}
	return false;
}
