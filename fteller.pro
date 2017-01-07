#
# fortune application
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
#CONFIG += debug_and_release
DEFINES += DELIBERATE_DEBUG

#MAKEFILE = Make_$${MYNAME}

#CONFIG(debug, debug|release) {
#  TARGET = bin/$${MYNAME}_d
#  OBJECTS_DIR = tmp/debug/obj
#  message ("DEBUG cxx-flags used $${QMAKE_CXXFLAGS_DEBUG}")
#  message ("DEBUG c-flags used $${QMAKE_CFLAGS_DEBUG}")
#} else {
#  TARGET = $${MYNAME}
#  OBJECTS_DIR = tmp/release/obj
#  QMAKE_CXXFLAGS_RELEASE -= -g
#  QMAKE_CFLAGS_RELEASE -= -g
#  message ("RELEASE cxx-flags used $${QMAKE_CXXFLAGS_RELEASE}")
#  message ("RELEASE c-flags used $${QMAKE_CFLAGS_RELEASE}")
#}



UI_DIR = tmpui
MOC_DIR = tmpmoc
RCC_DIR = tmprcc
OBJECTS_DIR = tmpobj
RESOURCES = $${MYNAME}.qrc

FORMS = \
        ui/$${MYNAME}.ui \
        ui/DebugLog.ui \
        ui/config-edit.ui \
        

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

