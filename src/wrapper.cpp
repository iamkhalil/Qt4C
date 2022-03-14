#include "wrapper.h"

#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QDebug>

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
