#include "wrapper.h"

#include <QApplication>
#include <QObject>
#include <QMetaObject>
#include <QWidget>
#include <QDebug>
#include <QFormLayout>
#include <QLineEdit>
#include <QAbstractButton>
#include <QPushButton>
#include <QFile>
#include <QtUiTools>

#define TO_C(T) (static_cast<void *>(T))

void *qt_application_new(int *ac, char **av)
{
	const char *tmp[] = { "RTFM" };

	if (!ac)
		*ac = 1;
	if (!av)
		av = (char **) tmp;

        return TO_C(new (std::nothrow) QApplication(*ac, av));
}

int qt_application_exec(void *app)
{
	return static_cast<QApplication *>(app)->exec();
}

int qt_application_setStyle(void *app, const char *style)
{
        auto a = static_cast<QApplication *>(app);

        return (a->setStyle(QString(style)) != nullptr);
}

void *qt_object_new(void *parent)
{
	return TO_C(new (std::nothrow) QObject(static_cast<QObject *>(parent)));
}

void qt_object_delete(void *object)
{
	delete static_cast<QObject *>(object);
}

int qt_object_disconnect(void *connection)
{
	return (int) QObject::disconnect(*static_cast<QMetaObject::Connection *>(connection));
}

void *qt_object_destroyed_connect(void *object,
				  void *receiver,
				  void *context,
				  void (*fn)(void *context))
{
	QMetaObject::Connection c;

	if (receiver) {
		c = QObject::connect(static_cast<QObject *>(object),
				&QObject::destroyed,
				static_cast<QObject *>(receiver),
				[=]() { (*fn)(context); });
	} else {
		c = QObject::connect(static_cast<QObject *>(object),
				&QObject::destroyed,
				[=]() { (*fn)(context); });
	}
	return TO_C(new (std::nothrow) QMetaObject::Connection(c));
}

void qt_object_dumpObjectInfo(void *object)
{
	static_cast<QObject *>(object)->dumpObjectInfo();
}

void qt_object_dumpObjectTree(void *object)
{
	static_cast<QObject *>(object)->dumpObjectTree();
}

void qt_object_setObjectName(void *object, const char *name)
{
	static_cast<QObject *>(object)->setObjectName(name);
}

const char *qt_object_objectName(void *object)
{
	QString s = static_cast<QObject *>(object)->objectName();

	return s.toLocal8Bit().constData();
}

void *qt_object_parent(void *object)
{
	return TO_C(static_cast<QObject *>(object)->parent());
}

void qt_debug_print(void *object)
{
	auto o = static_cast<QObject *>(object);
	qDebug() << "[DEBUG]: " << o << '\n';
}

void *qt_widget_new(void *parent, int flags)
{
	return TO_C(new (std::nothrow) QWidget(static_cast<QWidget *>(parent),
				static_cast<QFlags<Qt::WindowType>>(flags)));
}

void qt_widget_show(void *widget)
{
	static_cast<QWidget *>(widget)->show();
}

void qt_widget_setWindowTitle(void *widget, const char *title)
{
        static_cast<QWidget *>(widget)->setWindowTitle(QString(title));
}

const char *qt_widget_windowTitle(void *widget)
{
        auto title = static_cast<QWidget *>(widget)->windowTitle();

        return title.toLocal8Bit().constData();
}

void *qt_formLayout_new(void *parent)
{
	return TO_C(new (std::nothrow) QFormLayout(static_cast<QWidget *>(parent)));
}

void qt_formLayout_addRow(void *form, const char *labelText, void *field)
{
	auto f = static_cast<QFormLayout *>(form);

	if (labelText) {
		f->addRow(QString(labelText), static_cast<QWidget *>(field));
		return;
	}
	f->addRow(static_cast<QWidget *>(field));
}

void *qt_lineEdit_new(const char *content, void *parent)
{
	if (content)
		return TO_C(new (std::nothrow) QLineEdit(QString(content),
					static_cast<QWidget *>(parent)));
	return TO_C(new (std::nothrow) QLineEdit(static_cast<QWidget *>(parent)));
}

const char *qt_lineEdit_text(void *lineEdit)
{
	auto s = static_cast<QLineEdit *>(lineEdit)->text();

	return s.toLocal8Bit().constData();
}

void qt_lineEdit_setText(void *lineEdit, const char *text)
{
	static_cast<QLineEdit *>(lineEdit)->setText(QString(text));
}

int qt_lineEdit_echoMode(void *lineEdit)
{
	return static_cast<QLineEdit *>(lineEdit)->echoMode();
}

void qt_lineEdit_setEchoMode(void *lineEdit, int mode)
{
	static_cast<QLineEdit *>(lineEdit)->setEchoMode(
			static_cast<QLineEdit::EchoMode>(mode));
}

void qt_lineEdit_setPlaceholderText(void *lineEdit, const char *text)
{
	static_cast<QLineEdit *>(lineEdit)->setPlaceholderText(text);
}

const char *qt_lineEdit_placeholderText(void *lineEdit)
{
	auto s = static_cast<QLineEdit *>(lineEdit)->placeholderText();

	return s.toLocal8Bit().constData();
}

void qt_lineEdit_textChanged_connect(void *lineEdit,
				     void *receiver,
				     void *context,
				     void (*fn)(void *context, void *lineEdit))
{
	if (receiver) {
		QObject::connect(static_cast<QLineEdit *>(lineEdit),
				 &QLineEdit::textChanged,
				 static_cast<QObject *>(receiver),
				 [=]() { (*fn)(context, lineEdit); });
		return;
	}
	QObject::connect(static_cast<QLineEdit *>(lineEdit),
			 &QLineEdit::textChanged,
			 [=]() { (*fn)(context, lineEdit); });
}

void qt_abstractButton_setText(void *abstractButton, const char *text)
{
	static_cast<QAbstractButton *>(abstractButton)->setText(text);
}

const char *qt_abstractButton_text(void *abstractButton)
{
	auto s = static_cast<QAbstractButton *>(abstractButton)->text();

	return s.toLocal8Bit().constData();
}

void qt_abstractButton_clicked_connect(void *abstractButton,
				       void *receiver,
				       void *context,
				       void (*fn)(void *context, int checked))
{
	if (receiver) {
		QObject::connect(static_cast<QAbstractButton *>(abstractButton),
				&QAbstractButton::clicked,
				static_cast<QObject *>(receiver),
				[=](int checked) { (*fn)(context, checked); });
		return;
	}
	QObject::connect(static_cast<QAbstractButton *>(abstractButton),
			&QAbstractButton::clicked,
			[=](int checked) { (*fn)(context, checked); });
}

void qt_abstractButton_pressed_connect(void *abstractButton,
                                       void *receiver,
                                       void *context,
                                       void (*fn)(void *context))
{
        if (receiver) {
		QObject::connect(static_cast<QAbstractButton *>(abstractButton),
				&QAbstractButton::pressed,
				static_cast<QObject *>(receiver),
				[=]() { (*fn)(context); });
		return;
	}
	QObject::connect(static_cast<QAbstractButton *>(abstractButton),
			&QAbstractButton::pressed,
			[=]() { (*fn)(context); });
}

void *qt_pushButton_new(void *icon, const char *text, void *parent)
{
	if (!icon)
		return TO_C(new (std::nothrow) QPushButton(QString(text),
					static_cast<QWidget *>(parent)));
	return TO_C(new (std::nothrow) QPushButton(*static_cast<QIcon *>(icon),
				QString(text), static_cast<QWidget *>(parent)));
}

void *qt_file_new(const char *name, void *parent)
{
	if (!name && !parent)
		return TO_C(new (std::nothrow) QFile());
	else if (!parent)
		return TO_C(new (std::nothrow) QFile(name));
	else if (!name)
		return TO_C(new (std::nothrow) QFile(static_cast<QObject *>(parent)));
	else
		return TO_C(new (std::nothrow) QFile(name, static_cast<QObject *>(parent)));
}

int qt_file_open(void *file, int mode)
{
	return (int) static_cast<QFile *>(file)->open(static_cast<QFlags<QIODevice::OpenModeFlag>>(mode));
}

void qt_file_close(void *file)
{
	static_cast<QFile *>(file)->close();
}

void *qt_dir_new(const char *path)
{
        return TO_C(new (std::nothrow) QDir(path));
}

char *qt_dir_absoluteFilePath(void *dir, const char *filename)
{
        auto s = static_cast<QDir *>(dir)->absoluteFilePath(filename);

        return s.toLocal8Bit().data();
}

void *qt_uiloader_new(void *parent)
{
	return TO_C(new (std::nothrow) QUiLoader(static_cast<QObject *>(parent)));
}

void *qt_uiloader_load(void *loader, void *device, void *parentWidget)
{
	return TO_C(static_cast<QUiLoader *>(loader)->load(static_cast<QIODevice *>(device),
						static_cast<QWidget *>(parentWidget)));
}

void qt_uiloader_setWorkingDirectory(void *loader, void *dir)
{
        static_cast<QUiLoader *>(loader)->setWorkingDirectory(*static_cast<QDir *>(dir));
}
