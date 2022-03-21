#include "test.h"

#define READONLY 1

void test2(int ac, char *av[])
{
	void *ap, *wp, *file, *loader, *dir;

	ap = wp = loader = file = dir = NULL;

	ap = qt_application_new(&ac, av);
	loader = qt_uiloader_new(NULL);

	dir = qt_dir_new("../build/");
	if (!dir) {
		puts("Error: PATH.");
		exit(1);
	}

	qt_uiloader_setWorkingDirectory(loader, dir);

	file = qt_file_new("mainwindow.ui", ap);
	if (!file) {
		puts("Error: file.");
		exit(2);
	}

	qt_file_open(file, READONLY);
	wp = qt_uiloader_load(loader, file, NULL);
	if (!wp) {
		puts("Error: loader.");
		exit(3);
	}
	qt_file_close(file);
	qt_widget_show(wp);
	qt_application_exec(ap);

	qt_object_delete(file);
	qt_object_delete(loader);
	qt_object_delete(wp);
	qt_object_delete(ap);
}

