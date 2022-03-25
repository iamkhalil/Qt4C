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
int qt_object_disconnect(void *connection);
void *qt_object_destroyed_connect(void *object,
				  void *receiver,
				  void *context,
				  void (*fn)(void *context));

void qt_object_dumpObjectInfo(void *object);
void qt_object_dumpObjectTree(void *object);
void qt_object_setObjectName(void *object, const char *name);
const char *qt_object_objectName(void *object);
void *qt_object_parent(void *object);
void *qt_object_findChild(void *object, const char *name, int options);

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
void qt_lineEdit_setPlaceholderText(void *lineEdit, const char *text);
const char *qt_lineEdit_placeholderText(void *lineEdit);
void qt_lineEdit_textChanged_connect(void *lineEdit,
				     void *receiver,
				     void *context,
				     void (*fn)(void *context, void *lineEdit));

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

/* QFile */
void *qt_file_new(const char *name, void *parent);
int qt_file_open(void *file, int mode);
void qt_file_close(void *file);

/* QDir */
void *qt_dir_new(const char *path);
char *qt_dir_absoluteFilePath(void *dir, const char *filename);

/* QUiLoader */
void *qt_uiloader_new(void *parent);
void *qt_uiloader_load(void *loader, void *device, void *parentWidget);
void qt_uiloader_setWorkingDirectory(void *loader, void *dir);

/* QResoure */
void *qt_resource_new(const char *file, void *locale);
int qt_resource_registerResource(void *resource, const char *rccFileName, const char *mapRoot);

/* QString */
char *qt_string_number_double(double n, char format, int precision);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WRAPPER_H */

