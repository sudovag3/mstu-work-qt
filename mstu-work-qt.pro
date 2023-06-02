#-------------------------------------------------
#
# Project created by QtCreator 2023-03-20T16:01:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mstu-work-qt
TEMPLATE = app


SOURCES += main.cpp\
    authors.cpp \
    documentation.cpp \
    librarianform.cpp \
        mainwindow.cpp \
    authwindow.cpp \
    user.cpp \
    admin.cpp \
    student.cpp \
    librarian.cpp \
    adminform.cpp \
    edituserform.cpp \
    book.cpp \
    editbookform.cpp \
    bookform.cpp \
    studentbook.cpp \
    studentform.cpp

HEADERS  += mainwindow.h \
    authors.h \
    authwindow.h \
    documentation.h \
    librarianform.h \
    user.h \
    admin.h \
    student.h \
    librarian.h \
    adminform.h \
    user_find.h \
    edituserform.h \
    book.h \
    editbookform.h \
    bookform.h \
    book_find.h \
    studentbook.h \
    studentform.h

FORMS += mainwindow.ui \
    authors.ui \
    authwindow.ui \
    adminform.ui \
    documentation.ui \
    librarianform.ui \
    studentform.ui \
    editbookform.ui \
    bookform.ui \
    edituserform.ui

DISTFILES += \
    .gitignore

RESOURCES +=
