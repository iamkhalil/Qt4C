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
	void *ap, *wp, *form, *lp, *file, *loader, *widget;
	char *context;

	ap = wp = form = lp = file = loader = widget = NULL;

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

	if ((file = qt_file_new("filename.txt", ap)) != NULL) {
		puts("filename.txt created successfully.");
		if (qt_file_open(file, 2) == 0) {
			puts("Failed to open filename.txt");
			exit(5);
		}
		puts("Open!");
		qt_file_close(file);
		puts("Close!");
	}

	loader = qt_uiloader_new(NULL);
	if (!loader) {
		puts("Failed to instantiate QUiLoader class.");
		exit(6);
	}
	file = qt_file_new("calculatrice.ui", ap);
	qt_file_open(file, 1); // ReadOnly
	widget = qt_uiloader_load(loader, file, NULL);

	qt_widget_show(wp);
	qt_widget_show(widget);

	qt_application_exec(ap);

	qt_object_delete(file);
	qt_object_delete(lp);
	qt_object_delete(form);
	qt_object_delete(wp);
	qt_object_delete(widget);
	qt_object_delete(ap);
}

