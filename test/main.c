#include "src/wrapper.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	void *ap, *wp, *o;
	int ret;

	ap = wp = o = NULL;

	ap = qt_application_new(&argc, argv);
	if (!ap) {
		perror("Error: can't instantiate QApplication class.");
		exit(1);
	}

	ret = qt_application_setStyle(ap, "windows");
	if (!ret) {
		perror("Error: failed to set style.");
		exit(2);
	}

	wp = qt_widget_new(NULL, 1);
	if(!wp) {
		puts("Error: can't instantiate QWidget class.");
		exit(3);
	}

	qt_widget_setWindowTitle(wp, "Welcome to C/QT");
	printf("WINDOW TITLE = %s\n", qt_widget_windowTitle(wp));

	// printf("app=%p\twiget=%p\n", ap, wp);
	qt_debug_print(ap);
	qt_debug_print(wp);

	o = qt_object_new(NULL);
	if(!o) {
		puts("Error: can't instantiate QObject class.");
		exit(4);
	}

	qt_object_setObjectName(o, "QT is CUTE!");
	printf("%s\n", (char *) qt_object_objectName(o));

	qt_widget_show(wp);
	ret = qt_application_exec(ap);
	printf("exec() return value: %d\n",ret);

	// free resources previously allocated with the new operator
	qt_object_delete(o);
	qt_object_delete(wp);
	qt_object_delete(ap);

	return 0;
}

