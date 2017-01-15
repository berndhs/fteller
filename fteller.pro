#
# fortune teller application
#

#/****************************************************************
# * This file is distributed under the following license:
# *
# * Copyright (C) 2017, Bernd Stramm
# *
# *  This program is free software; you can redistribute it and/or
# *  modify it under the terms of the GNU General Public License
# *  as published by the Free Software Foundation; either version 2
# *  of the License, or (at your option) any later version.
# *
# *  This program is distributed in the hope that it will be useful,
# *  but WITHOUT ANY WARRANTY; without even the implied warranty of
# *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# *  GNU General Public License for more details.
# *
# *  You should have received a copy of the GNU General Public License
# *  along with this program; if not, write to the Free Software
# *  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
# *  Boston, MA  02110-1301, USA.
# ****************************************************************/

MYNAME = fteller

TEMPLATE = app

QT += core widgets gui
QT += quick
QT += quickwidgets
QT += qml

DEFINES += DELIBERATE_DEBUG



UI_DIR = tmpui
MOC_DIR = tmpmoc
RCC_DIR = tmprcc
OBJECTS_DIR = tmpobj
RESOURCES = $${MYNAME}.qrc

FORMS = \
        ui/$${MYNAME}.ui \
        ui/DebugLog.ui \
        ui/config-edit.ui \
    ui/DebugLog.ui \
    ui/config-edit.ui
        

HEADERS = \
          src/$${MYNAME}.h \
          src/main.h \
          src/gpl2.h \
          src/cmdoptions.h \
          src/config-edit.h \
          src/delib-debug.h \
          src/deliberate.h \
          src/version.h \


SOURCES = \
          src/$${MYNAME}.cpp \
          src/main.cpp \
          src/cmdoptions.cpp \
          src/config-edit.cpp \
          src/delib-debug.cpp \
          src/deliberate.cpp \
          src/version.cpp \

