QT       += core gui \
            charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chart.cpp \
    comboboxdelegate.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    plotter.cpp \
    proiz.cpp \
    proxymodel.cpp \
    spinboxdelegate.cpp \
    tablemodel.cpp \
    tableview.cpp

HEADERS += \
    chart.hpp \
    comboboxdelegate.hpp \
    dialog.hpp \
    mainwindow.hpp \
    plotter.hpp \
    proiz.hpp \
    proxymodel.hpp \
    spinboxdelegate.hpp \
    tablemodel.hpp \
    tableview.hpp

FORMS += \
    chart.ui \
    dialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    translations/CourseWork_ru_RU.ts \
    translations/CourseWork_en_US.ts \
    translations/CourseWork_no_NO.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ico.qrc



