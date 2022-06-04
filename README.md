# Qt4C

## Description
This project tries to create a C wrapper library around common QT widgets so that it can be used as a basis for the development of GUI-based applications using the C programming language.

## Requirements
- Qt5 (you may also need to install the package `qttools5-dev` to get the Qt uitools module working on Linux)
- C++ compiler that supports C++11 features
- CMake >= 3.5

## API
The Qt4C api follows the Qt api mostly, which would make it easier to refer to the [Qt documentation](https://doc.qt.io/qt-5/qtwidgets-module.html). As an example:
```cpp
// ...

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
```
becomes:
```c
#include <wrapper.h>

int main(int argc, char *argv[])
{
    void *a, *w;

    a = qt_application_new(&argc, argv);
    w = qt_widget_new(NULL, 1); /* Indicates that the widget is a window */
    qt_widget_show(w);
    return qt_application_exec(a);
}
```

## Usage
To add Qt4C to your project, you can either clone the source code into your own
project tree:
```shell
$ git clone https://github.com/iamkhalil/Qt4C.git
```
or add it as a submodule:
```shell
$ git submodule add https://github.com/iamkhalil/Qt4C.git
```
Then you've to build it:
```shell
$ cd Qt4C
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```
You can now use Qt4C as a shared library with your C applications.
Here is an example CMakeLists.txt file:
```cmake
cmake_minimum_required(VERSION 3.20)
project(app)

add_subdirectory(Qt4C)
add_executable(myapp main.c)

target_include_directories(myapp PRIVATE Qt4C/src)
target_link_libraries(myapp PRIVATE wrapper)
```
## Example
[Calculator](https://github.com/iamkhalil/Qt4C/blob/master/test/3-test.c)
![calc](https://i.imgur.com/KP3pDsV.png)

## Author
- **Mohamed khalil El-Bechir** - [medkhalilelb@gmail.com](medkhalilelb@gmail.com) | [GitHub/iamkhalil](https://github.com/iamkhalil)
## Licence
MIT License
