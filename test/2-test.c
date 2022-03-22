#include "test.h"

#define READONLY 1

void test2(int ac, char *av[])
{
	void *ap, *wp, *file, *loader, *resource;
	const char *path = "/home/khalil/Qt4C/build/resource.rcc";

	ap = qt_application_new(&ac, av);

	resource = qt_resource_new(NULL, NULL);
	if (!resource) {
		puts("Error: can't instantiate QResource class.");
		exit(1);
	}
	if (!qt_resource_registerResource(resource, path, NULL)) {
		puts("Error while loading resource.rcc");
		exit(2);
	}

	file = qt_file_new("mainwindow.ui", ap);
	qt_file_open(file, READONLY);
	loader = qt_uiloader_new(NULL);
	wp = qt_uiloader_load(loader, file, NULL);
	qt_file_close(file);

	qt_widget_show(wp);
	qt_application_exec(ap);

	qt_object_delete(file);
	qt_object_delete(loader);
	qt_object_delete(wp);
	qt_object_delete(ap);
}

