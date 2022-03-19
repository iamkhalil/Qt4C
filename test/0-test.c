#include "test.h"

/* Callbacks defintion */
void on_button_clicked(void *context, int checked)
{
	(void) context;
	(void) checked;
	puts("[CALLBACK]: Clicked!");
}

void on_button_pressed(void *context)
{
	(void) context;

	puts("[CALLBACK]: Pressed!");
}

/* Test definition */
void test0(int ac, char *av[])
{
	void *ap, *wp, *o, *form, *lineEdit, *lineEdit2, *btn, *btn2;
	int ret;

	ap = wp = o = form = lineEdit = btn = btn2 = NULL;

	ap = qt_application_new(&ac, av);
	if (!ap) {
		perror("Error: can't instantiate QApplication class.");
		exit(1);
	}

	ret = qt_application_setStyle(ap, "Fusion");
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

	// printf("app=%p\twidget=%p\n", ap, wp);
	qt_debug_print(ap);
	qt_debug_print(wp);

	lineEdit = qt_lineEdit_new("default text", wp);
	if(!lineEdit) {
		puts("Error: can't instantiate QlineEdit class.");
		exit(4);
	}

	form = qt_formLayout_new(wp);
	if(!form) {
		puts("Error: can't instantiate QFormLayout class.");
		exit(5);
	}

	qt_formLayout_addRow(form, "label", lineEdit);

	lineEdit2 = qt_lineEdit_new("text!", wp);
	if(!lineEdit2) {
		puts("Error: can't instantiate QlineEdit class.");
		exit(6);
	}

	qt_formLayout_addRow(form, "Password", lineEdit2);

	printf("lineEdit2 = %s\n", qt_lineEdit_text(lineEdit2));
	qt_lineEdit_setEchoMode(lineEdit2, 2); // password
	qt_lineEdit_setText(lineEdit2, "crackme!");
	printf("Echo Mode = %d\n", qt_lineEdit_echoMode(lineEdit2));

	btn = qt_pushButton_new(NULL, "Click", wp);
	btn2 = qt_pushButton_new(NULL, "Press", wp);
	if(!btn || !btn2) {
		puts("Error: can't instantiate QPushButton class.");
		exit(8);
	}
	qt_formLayout_addRow(form, NULL, btn);
	qt_formLayout_addRow(form, NULL, btn2);

	qt_abstractButton_clicked_connect(btn, NULL, NULL, on_button_clicked);
	qt_abstractButton_pressed_connect(btn2, NULL, NULL, &on_button_pressed);

	o = qt_object_new(NULL);
	if(!o) {
		puts("Error: can't instantiate QObject class.");
		exit(7);
	}

	qt_object_setObjectName(o, "QT is CUTE!");
	printf("%s\n", (char *) qt_object_objectName(o));

	qt_widget_show(wp);
	ret = qt_application_exec(ap);
	printf("exec() return value: %d\n", ret);

	/* free resources previously allocated with the new operator */
	qt_object_delete(o);
	qt_object_delete(lineEdit);
	qt_object_delete(lineEdit2);
	qt_object_delete(btn);
	qt_object_delete(btn2);
	qt_object_delete(form);
	qt_object_delete(wp);
	qt_object_delete(ap);
}

