#include "drawwindow.h"
#include "ui_drawwindow.h"

DrawWindow::DrawWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::DrawWindow),
	setupWindow(new SetupWindow(this)),
	aboutWindow(new AboutWindow(this)),
	helpWindow(new HelpWindow(this)),
	list_history(new ActionList),
	isDragging(false),
	isSnapping(false)
{
	ui->setupUi(this);

	canned_declares = "void Move(int inches);\n";
	canned_declares += "void MoveForward(int inches);\n";
	canned_declares += "void MoveBackward(int inches);\n";
	canned_declares += "void Turn(int degrees);\n";
	canned_declares += "void TurnLeft(int degrees);\n";
	canned_declares += "void TurnRight(int degrees);\n";

	canned_definitions = "";
	canned_definitions += "void MoveForward(int inches) {\n";
	canned_definitions += "\tMove(inches);\n";
	canned_definitions += "}\n";
	canned_definitions += "void MoveBackward(int inches) {\n";
	canned_definitions += "\tMove(-inches);\n";
	canned_definitions += "}\n";
	canned_definitions += "void TurnLeft(int degrees) {\n";
	canned_definitions += "\tTurn(degrees);\n";
	canned_definitions += "}\n";
	canned_definitions += "void TurnRight(int degrees) {\n";
	canned_definitions += "\tTurn(-degrees);\n";
	canned_definitions += "}\n";

	QRectF bounds = QRectF(-10, -10, 164, 164);
	field.addRect(bounds, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::white));

	QRectF tiles = QRectF(0, 0, 144, 144);
	field.addRect(tiles, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::lightGray));

	QRectF zone_ramp_out_R = QRectF(0, 0, 30, 66);
	QRectF zone_ramp_in_R = QRectF(0, 0, 28, 64);
	QRectF zone_park_out_R = QRectF(47, 0, 47, 23);
	QRectF zone_park_in_R = QRectF(49, 0, 43, 21);
	QRectF ramp_R = QRectF(0, 0, 23.75, 57);
	field.addRect(zone_ramp_out_R, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::red));
	field.addRect(zone_ramp_in_R, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::lightGray));
	field.addRect(zone_park_out_R, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::red));
	field.addRect(zone_park_in_R, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::lightGray));
	field.addRect(ramp_R, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::red));

	QRectF zone_ramp_out_B = QRectF(144-30, 144-66, 30, 66);
	QRectF zone_ramp_in_B = QRectF(144-28, 144-64, 28, 64);
	QRectF zone_park_out_B = QRectF(144-47-47, 144-23, 47, 23);
	QRectF zone_park_in_B = QRectF(144-43-49, 144-21, 43, 21);
	QRectF ramp_B = QRectF(144-23.75, 144-57, 23.75, 57);
	field.addRect(zone_ramp_out_B, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::blue));
	field.addRect(zone_ramp_in_B, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::lightGray));
	field.addRect(zone_park_out_B, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::blue));
	field.addRect(zone_park_in_B, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::lightGray));
	field.addRect(ramp_B, QPen(Qt::NoBrush, 0, Qt::NoPen), QBrush(Qt::blue));

	field.setSceneRect(-5, -5, 149, 149);
	ui->graphicsView->setScene(&field);

	installEventFilter(this);

	QObject::connect(	setupWindow,		&SetupWindow::added_custom_define,
						this,				&DrawWindow::add_custom_action);
	QObject::connect(	setupWindow,		&SetupWindow::removed_custom_define,
						this,				&DrawWindow::remove_custom_action);

	QObject::connect(	ui->graphicsView,	&GraphicsViewEdit::mouse_pressed,
						this,				&DrawWindow::add_move);
	QObject::connect(	ui->graphicsView,	&GraphicsViewEdit::mouse_moved,
						this,				&DrawWindow::update_move);
	QObject::connect(	ui->graphicsView,	&GraphicsViewEdit::mouse_released,
						this,				&DrawWindow::end_move);

	QObject::connect(	ui->pushButton_clear,	&QPushButton::clicked,
						this,					&DrawWindow::on_pushButton_clear_clicked); //TODO: get rid of this
}

DrawWindow::~DrawWindow()
{
	on_pushButton_clear_clicked();

	delete currentLine;
	delete circleHome;
	delete circleCurrent;

	delete ui;
	delete setupWindow;
	delete helpWindow;
	delete aboutWindow;
	delete list_history;
}

void DrawWindow::resizeEvent(QResizeEvent* event)
{
	ui->graphicsView->fitInView(field.itemsBoundingRect(), Qt::KeepAspectRatio);
	QMainWindow::resizeEvent(event);
}

void DrawWindow::showEvent(QShowEvent* event)
{
	ui->graphicsView->fitInView(field.itemsBoundingRect(), Qt::KeepAspectRatio);
	QMainWindow::showEvent(event);
}

void DrawWindow::add_move(QPointF start)
{
	isDragging = true;
	QPointF rounded = ui->graphicsView->mapToScene(start.toPoint());
	if (isSnapping) {
		int round_x = 0;
		int round_y = 0;
		round_x = static_cast<int>(rounded.x());
		round_y = static_cast<int>(rounded.y());
		round_x = round(round_x/3.0);
		round_y = round(round_y/3.0);
		round_x *= 3;
		round_y *= 3;
		rounded = QPointF(round_x, round_y);
	}
	if (list_history->getSize() == 0) {
		startPoint = rounded;
		circleHome = field.addEllipse(	startPoint.x()-4,
										startPoint.y()-4,
										8,
										8					);
		circleHome->setPen(QPen(QBrush(QColor("orangered")), 2));
		circleHome->setBrush(QBrush(Qt::yellow));
	} else {
		startPoint = endPoint; // TODO: is this safe?
	}
	endPoint = rounded;
	currentLine = field.addLine(	startPoint.x(),
									startPoint.y(),
									endPoint.x(),
									endPoint.y()	);
	currentLine->setPen(QPen(QBrush(Qt::black), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	if (ui->toolButton_reverse->isChecked()) {
		currentLine->setPen(QPen(QBrush(Qt::black), 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
	}
}

void DrawWindow::update_move(QPointF end)
{
	if (isDragging) {
		endPoint = ui->graphicsView->mapToScene(end.toPoint());
		if (isSnapping) {
			int round_x = 0;
			int round_y = 0;
			round_x = static_cast<int>(endPoint.x());
			round_y = static_cast<int>(endPoint.y());
			round_x = round(round_x/3.0);
			round_y = round(round_y/3.0);
			round_x *= 3;
			round_y *= 3;
			endPoint = QPointF(round_x, round_y);
		}
		currentLine->setLine(	startPoint.x(),
								startPoint.y(),
								endPoint.x(),
								endPoint.y()	);
	}
}

void DrawWindow::end_move(QPointF end)
{
	if (isDragging) {
		endPoint = ui->graphicsView->mapToScene(end.toPoint());
		if (isSnapping) {
			int round_x = 0;
			int round_y = 0;
			round_x = static_cast<int>(endPoint.x());
			round_y = static_cast<int>(endPoint.y());
			round_x = round(round_x/3.0);
			round_y = round(round_y/3.0);
			round_x *= 3;
			round_y *= 3;
			endPoint = QPointF(round_x, round_y);
		}
		currentLine->setLine(	startPoint.x(),
								startPoint.y(),
								endPoint.x(),
								endPoint.y()	);
	}
	isDragging = false;
	MoveDirection direction = MOVE_FORWARD;
	if (ui->toolButton_reverse->isChecked()) {
		direction = MOVE_BACKWARD;
	}
	ActionMove* new_move = new ActionMove(direction, startPoint, endPoint);
	if (list_history->getSize() > 0) {
		Action* last_action_buf = list_history->getAction(list_history->getSize()-1);
		ActionMove* last_action = dynamic_cast<ActionMove*>(last_action_buf);
		QPointF vect_A(last_action->getStart() - last_action->getEnd());
		QPointF vect_B(endPoint - startPoint);
		float angle_A = atan2(vect_A.y(), vect_A.x());
		float angle_B = atan2(vect_B.y(), vect_B.x());
		float angle =  angle_A - angle_B;
		angle = angle * 180.0 / 3.14159;
		if (angle > 180) {
			angle -= 360;
		}
		if (angle < -180) {
			angle += 360;
		}
		if (ui->toolButton_reverse->isChecked()) {
			angle += 180;
			angle = fmod(angle, 180);
		}
		TurnDirection direction = TURN_LEFT;
		if (angle < 0) {
			direction = TURN_RIGHT;
			angle *= -1;
		}
		ActionTurn* turn = new ActionTurn(direction, startPoint, angle);
		list_history->addAction(turn);
	}
	list_history->addAction(new_move);
	list_lines.push_back(currentLine);
}

void DrawWindow::start_snap()
{
	isSnapping = true;
}
void DrawWindow::end_snap()
{
	isSnapping = false;
}

void DrawWindow::add_custom_action(ActionDefine* definition)
{
	list_defines.push_back(definition);
}
void DrawWindow::remove_custom_action(ActionDefine* definition)
{
	;
}

void DrawWindow::on_pushButton_setup_clicked()
{
	setupWindow->exec();
}
void DrawWindow::on_pushButton_help_clicked()
{
	helpWindow->exec();
}
void DrawWindow::on_pushButton_about_clicked()
{
	aboutWindow->exec();
}

void DrawWindow::on_pushButton_generateProgram_clicked()
{
	QString output_filename = QFileDialog::getSaveFileName(	this,
															"Choose location...",
															"Auton.c",
															"RobotC programs (*.c)");
	QProgressDialog* write_progress = new QProgressDialog(	"Writing program...",
															QString(),
															0,
															15,
															this);
	write_progress->setMinimumDuration(500);
	QFile output_program(output_filename);
	output_program.open(QIODevice::ReadWrite | QIODevice::Text);
	QTextStream output_stream(&output_program);
	write_progress->setValue(1);
	output_stream <<  SetupWindow::read_file("code/controller_config.txt");
	write_progress->setValue(2);
	output_stream << "\n";
	output_stream << "#include \"JoystickDriver.c\"\n\n";
	write_progress->setValue(3);
	output_stream << SetupWindow::read_file("code/additional_includes.txt");
	write_progress->setValue(4);
	output_stream << "\n";
	output_stream << canned_declares;
	output_stream << "\n";
	write_progress->setValue(5);
	output_stream << SetupWindow::read_file("code/misc_declare.txt");
	write_progress->setValue(6);
	output_stream << "\ntask main()\n{\n";
	write_progress->setValue(7);
	output_stream << SetupWindow::read_file("code/misc_init.txt");
	write_progress->setValue(8);
	output_stream << "\n\twaitForStart();\n\n";
	write_progress->setValue(9);
	output_stream << list_history->getCalls();
	output_stream << "}\n\n";
	write_progress->setValue(10);
	output_stream << SetupWindow::read_file("code/definition_move.txt");
	output_stream << "\n";
	write_progress->setValue(11);
	output_stream << SetupWindow::read_file("code/definition_turn.txt");
	write_progress->setValue(12);
	output_stream << "\n";
	output_stream << canned_definitions;
	output_stream << "\n";
	write_progress->setValue(13);
	output_stream << SetupWindow::read_file("code/misc__define.txt");
	output_stream << "\n";
	write_progress->setValue(14);
	output_stream.flush();
	write_progress->setValue(15);
}

void DrawWindow::on_pushButton_exportDiagram_clicked()
{
	QString output_filename = QFileDialog::getSaveFileName(	this,
															"Choose location...",
															"Auton Diagram.png",
															"PNG images (*.png)");
	QSize output_size = field.itemsBoundingRect().size().toSize()*8;
	QImage output_image(output_size, QImage::Format_ARGB32);
	output_image.fill(Qt::transparent);
	QPainter output_painter(&output_image);
	output_painter.setRenderHint(QPainter::Antialiasing);
	ui->graphicsView->render(	&output_painter,
								QRect(),
								QRect(ui->graphicsView->mapFromScene(-10, -10), ui->graphicsView->mapFromScene(154, 154)),
								Qt::KeepAspectRatio);
	output_image.save(output_filename, "png", 0);
}

void DrawWindow::on_pushButton_undo_clicked()
{
	if (list_history->getSize() > 0) {
		list_history->deleteAction();
		field.removeItem(currentLine);
		list_lines.pop_back();
		if (list_history->getSize() == 0) {
			currentLine = NULL;
			endPoint = QPointF(0, 0);
			field.removeItem(circleHome);
			circleHome = NULL;
		} else {
			list_history->deleteAction();
			currentLine = list_lines.back();
			ActionMove* past =
					dynamic_cast<ActionMove*>
					(list_history->getAction(list_history->getSize()-1));
			endPoint = past->getEnd();
		}
	}
}

void DrawWindow::on_pushButton_clear_clicked()
{
	while (list_history->getSize() > 0) {
		ui->pushButton_undo->click();
	}
}

bool DrawWindow::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* converted = dynamic_cast<QKeyEvent*>(event);
		if (converted->key() == Qt::Key_Shift) {
			start_snap();
		}
	}
	if (event->type() == QEvent::KeyRelease) {
		QKeyEvent* converted = dynamic_cast<QKeyEvent*>(event);
		if (converted->key() == Qt::Key_Shift) {
			end_snap();
		}
	}
	return false;
}

void DrawWindow::on_toolButton_add_clicked()
{
	setupWindow->show();
	setupWindow->show_new_custom_tab();
}
