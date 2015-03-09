 #
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
VERSION  = 0.1
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
                LICENSE

