#ifndef WRAPPER_H
#define WRAPPER_H

#ifdef __cplusplus
extern "C" { /*
              * Enforce C linkage by preventing the C++ compiler from mangling
              * the name. So we can call QT/C++ functions from C.
              */
#endif

/* Function prototypes - API */

/* QApplication */
void *qt_application_new(int *ac, char **av);
int qt_application_exec(void *app);
int qt_application_setStyle(void *app, const char *style);

/* QObject */
void *qt_object_new(void *parent);
void qt_object_delete(void *object);
void qt_object_dumpObjectInfo(void *object);
void qt_object_dumpObjectTree(void *object);
void qt_object_setObjectName(void *object, const char *name);
const char *qt_object_objectName(void *object);
void *qt_object_parent(void *object);

/* QDebug */
void qt_debug_print(void *object);

/* QWidget */
void *qt_widget_new(void *parent, int flags);
void qt_widget_show(void *widget);
void qt_widget_setWindowTitle(void *widget, const char *title);
const char *qt_widget_windowTitle(void *widget);

/* QFormLayout */
void *qt_formLayout_new(void *parent);
void qt_formLayout_addRow(void *form, const char *labelText, void *field);

/* QLineEdit */
void *qt_lineEdit_new(const char *content, void *parent);
const char *qt_lineEdit_text(void *lineEdit);
void qt_lineEdit_setText(void *lineEdit, const char *text);
int qt_lineEdit_echoMode(void *lineEdit);
void qt_lineEdit_setEchoMode(void *lineEdit, int mode);

/* QAbstractButton */
void qt_abstractButton_setText(void *abstractButton, const char *text);
const char *qt_abstractButton_text(void *abstractButton);
void qt_abstractButton_clicked_connect(void *abstractButton,
				       void *receiver,
				       void *context,
				       void (*fn)(void *context, int checked));

void qt_abstractButton_pressed_connect(void *abstractButton,
				       void *receiver,
                                       void *context,
                                       void (*fn)(void *context));

/* QPushButton */
void *qt_pushButton_new(void *icon, const char *text, void *parent);

#ifdef __cplusplus
}
#endif

#endif /* WRAPPER_H */

