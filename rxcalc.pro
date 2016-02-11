` #
 # Copyright 2014, 2015 Verkhovin Vyacheslav
 #
 # This file is part of RxCalc.
 #
 # RxCalc is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # RxCalc is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with RxCalc. If not, see <http://www.gnu.org/licenses/>.
 #

TARGET   = rxcalc
VERSION  = 0.6.4
TEMPLATE = app

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += APP_NAME=\\\"RxCalc\\\"

SOURCES +=  sources/main.cpp \
            sources/rxcalc.cpp \
            sources/stage.cpp \
            sources/system.cpp \
            sources/rxtable.cpp \
            sources/rxtablecell.cpp

HEADERS +=  sources/main.h \
            sources/rxcalc.h \
            sources/stage.h \
            sources/system.h \
            sources/rxtable.h \
            sources/rxtablecell.h

RESOURCES   +=  resources/images.qrc

OTHER_FILES +=  README.md \
                LICENSE \
                windows/replace.bat \
                windows/rxcalc.iss \
                resources/images.qrc

# use 'make build' for create .deb package
unix {
    #TODO - add icon for .rxcp files

    target.path = /usr/bin

    menu.path = /usr/share/applications
    menu.files = linux/rxcalc.desktop

    debianmenu.path = /usr/share/menu
    debianmenu.files = linux/rxcalc.menu

    pixmap.path = /usr/share/pixmaps
    pixmap.files = linux/rxcalc.xpm

    mimelnk.path = /usr/share/mimelnk/application
    mimelnk.files = linux/x-rxcalc-project.desktop

    mime.path = /usr/share/mime/packages
    mime.files = linux/x-rxcalc-project.xml

    #translations.path = /usr/share/rxcalc
    #translations.files = translations

    #documentation.path = /usr/share/doc/rxcalc
    #documentation.files = docs

    #manpage.path = /usr/share/man/man8
    #manpage.files = manpage/rxcalc.8.gz

    INSTALLS += target menu debianmenu pixmap mimelnk mime # translations documentation manpage

    QMAKE_EXTRA_TARGETS += build
    build.depends = all
    build.commands =  cp $$PWD/linux/description-pak $$OUT_PWD && \
        checkinstall --default -D --install=no --fstrans=yes --pkgname=$$TARGET --pkgversion=$$VERSION --deldesc=yes --backup=no --pkglicense=gpl3 --maintainer=arhiv6@users.sf.net --pkggroup=electronics --requires="libqtgui4"
}

win32 {
    QMAKE_TARGET_COPYRIGHT = (c) Verkhovin Vyacheslav
    RC_ICONS = resources/rxcalc.ico

    QMAKE_EXTRA_TARGETS += build
    build.depends = release
    build.commands = windeployqt .\\release\\rxcalc.exe && \
        $$PWD\\windows\\replace.bat     $$PWD\\windows\\rxcalc.iss  \"{VERSION}\"   \"$$VERSION\"   > .\\rxcalc.tmp && \
        $$PWD\\windows\\replace.bat     .\\rxcalc.tmp               \"{INPUTDIR}\"  \"$$PWD\"       > .\\rxcalc.iss && \
        DEL .\\rxcalc.tmp && DEL .\\release\\*.o && DEL .\\release\\*.cpp && iscc.exe rxcalc.iss
}
