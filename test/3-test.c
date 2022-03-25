#include "test.h"

#define READONLY 1
#define DEFAULT  1
#define CAPACITY 10

#define TOSTR(n) qt_string_number_double(n, 'g', 6)

typedef struct context {
	void *context;
	void *ui_lineEdit;
} context_t;

/* Global variables */
double result = 0.0;
int flag_add = 0;
int flag_div = 0;
int flag_mul = 0;
int flag_minus = 0;

/* Just for fun ^_^ */
int _strcmp(char *s1, char *s2)
{
	while ((*s1 == *s2) && *s1) {
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

/* Callbacks definitions */
void on_num_pressed(void *context)
{
	context_t *ctx;
	char *disp;
	char *endptr;
	double current_value;

	ctx = (context_t *) context;
	disp = (char *) qt_lineEdit_text(ctx->ui_lineEdit);
	if (!_strcmp(disp, "0.0") || !_strcmp(disp, "0")) {
		qt_lineEdit_setText(ctx->ui_lineEdit, qt_abstractButton_text(ctx->context));
	} else {
		current_value = strtod((char *) qt_lineEdit_text(ctx->ui_lineEdit), &endptr);
		current_value = (current_value * 10) + strtod((char *) qt_abstractButton_text(ctx->context), &endptr);
		qt_lineEdit_setText(ctx->ui_lineEdit, TOSTR(current_value));
	}
}

void on_math_btn_pressed(void *context)
{
	context_t *ctx;
	char *sign;
	char *endptr;

	ctx = (context_t *) context;
	result = strtod((char *) qt_lineEdit_text(ctx->ui_lineEdit), &endptr);

	sign = (char *) qt_abstractButton_text(ctx->context);
	if (!_strcmp(sign, "+"))
		flag_add = 1;
	else if (!_strcmp(sign, "-"))
		flag_minus = 1;
	else if (!_strcmp(sign, "*"))
		flag_mul = 1;
	else
		flag_div = 1;
	qt_lineEdit_setText(ctx->ui_lineEdit, "");
}

void on_equal_btn_pressed(void *context)
{
	context_t *ctx;
	char *endptr;
	double tmp;

	ctx = (context_t *) context;
	tmp = strtod((char *) qt_lineEdit_text(ctx->ui_lineEdit), &endptr);
	if (flag_add) {
		result += tmp;
		flag_add = 0;
	} else if (flag_minus) {
		result -= tmp;
		flag_minus = 0;
	} else if (flag_mul) {
		result *= tmp;
		flag_mul = 0;
	} else {
		result /= tmp;
		flag_div = 0;
	}
	qt_lineEdit_setText(ctx->ui_lineEdit, TOSTR(result));
}

void on_sign_btn_pressed(void *context)
{
	context_t *ctx;
	char *endptr;
	double current_val;

	ctx = (context_t *) context;
	current_val = strtod((char *) qt_lineEdit_text(ctx->ui_lineEdit), &endptr);
	current_val *= -1;
	qt_lineEdit_setText(ctx->ui_lineEdit, TOSTR(current_val));
}

/**
 * test3 - A simple calculator app designed with Qt Designer and programmed in C.
 */
void test3(int ac, char *av[])
{
	void *ap, *loader, *file, *wp;
	void *btns[CAPACITY];
	char btn_name[6] = {'B', 't', 'n', '_'};
	unsigned int i;
	void *ui_lineEdit;
	context_t btn_ctx[CAPACITY];
	context_t ui_add, ui_mul, ui_div, ui_minus, ui_equal, ui_sign;

	ap = qt_application_new(&ac, av);
	loader = qt_uiloader_new(NULL);
	file = qt_file_new("calculatrice.ui", ap);
	qt_file_open(file, READONLY);
	wp = qt_uiloader_load(loader, file, NULL);
	if (!wp) {
		fprintf(stderr, "Error while loading the ui file.\n");
		exit(98);
	}

	/* Locate the created QWidgets by object names */
	ui_lineEdit = qt_object_findChild(wp, "lineEdit_display", DEFAULT);
	qt_lineEdit_setText(ui_lineEdit, "0.0");

	for (i = 0; i < CAPACITY; ++i) {
		btn_name[4] = (i + '0');
		btns[i] = qt_object_findChild(wp, btn_name, DEFAULT);
		if (!btns[i]) {
			fprintf(stderr, "Error: Can't find %s\n", btn_name);
			exit(i + 1);
		}
		btn_ctx[i].context = btns[i];
		btn_ctx[i].ui_lineEdit = ui_lineEdit;
		qt_abstractButton_pressed_connect(btns[i], NULL, &btn_ctx[i], on_num_pressed);
	}

	ui_add.context = qt_object_findChild(wp, "Btn_add", DEFAULT);
	ui_add.ui_lineEdit = ui_lineEdit;
	qt_abstractButton_pressed_connect(ui_add.context, NULL, &ui_add, on_math_btn_pressed);

	ui_minus.context = qt_object_findChild(wp, "Btn_minus", DEFAULT);
	ui_minus.ui_lineEdit = ui_lineEdit;
	qt_abstractButton_pressed_connect(ui_minus.context, NULL, &ui_minus, on_math_btn_pressed);

	ui_div.context = qt_object_findChild(wp, "Btn_div", DEFAULT);
	ui_div.ui_lineEdit = ui_lineEdit;
	qt_abstractButton_pressed_connect(ui_div.context, NULL, &ui_div, on_math_btn_pressed);

	ui_mul.context = qt_object_findChild(wp, "Btn_mul", DEFAULT);
	ui_mul.ui_lineEdit = ui_lineEdit;
	qt_abstractButton_pressed_connect(ui_mul.context, NULL, &ui_mul, on_math_btn_pressed);

	ui_equal.context = qt_object_findChild(wp, "Btn_equal", DEFAULT);
	ui_equal.ui_lineEdit = ui_lineEdit;
	qt_abstractButton_pressed_connect(ui_equal.context, NULL, &ui_equal, on_equal_btn_pressed);

	ui_sign.context = qt_object_findChild(wp, "Btn_signs", DEFAULT);
	ui_sign.ui_lineEdit = ui_lineEdit;
	qt_abstractButton_pressed_connect(ui_sign.context, NULL, &ui_sign, on_sign_btn_pressed);

	qt_file_close(file);
	qt_widget_show(wp);
	qt_application_exec(ap);

	qt_object_delete(file);
	qt_object_delete(loader);
	qt_object_delete(wp);
	qt_object_delete(ap);
}

