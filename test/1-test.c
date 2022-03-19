#include "test.h"

void on_lineEdit_textChanged(void *context, void *lineEdit)
{
	(void) context;
	char *s;

	s = (char *) qt_lineEdit_text(lineEdit);
	printf("[CALLBACK]: text = %s\n", s);
}

void test1(int ac, char *av[])
{
	void *ap, *wp, *form, *lp;
	char *context;

	ap = wp = form = lp = NULL;

	ap = qt_application_new(&ac, av);
	if (!ap) {
		puts("Error: can't instantiate QApplication class.");
		exit(1);
	}

	wp = qt_widget_new(NULL, 1);
	if(!wp) {
		puts("Error: can't instantiate QWidget class.");
		exit(2);
	}

	qt_widget_setWindowTitle(wp, "Test QLineEdit");

	form = qt_formLayout_new(wp);
	if(!form) {
		puts("Error: can't instantiate QFormLayout class.");
		exit(3);
	}

	lp = qt_lineEdit_new("Lorem Ipsum", wp);
	if(!lp) {
		puts("Error: can't instantiate QLineEdit class.");
		exit(4);
	}
	qt_formLayout_addRow(form, "Input:", lp);

	context = (char *) qt_lineEdit_text(lp);
	printf("[MAIN]: text = %s\n", context);

	qt_lineEdit_textChanged_connect(lp, NULL, NULL, on_lineEdit_textChanged);

	qt_widget_show(wp);
	qt_application_exec(ap);

	qt_object_delete(lp);
	qt_object_delete(form);
	qt_object_delete(wp);
	qt_object_delete(ap);
}

