# -*- mode: Makefile -*-
#*****************************************************************************\
# $Id: xxdiff.pro 405 2001-11-22 17:51:48Z blais $
# $Date: 2001-11-22 12:51:48 -0500 (Thu, 22 Nov 2001) $
#
# Copyright (C) 2001  Martin Blais <blais@iro.umontreal.ca>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#****************************************************************************/
#
# Generate with xxdiff.t template, as `tmake -t xxdiff.t xxdiff.pro > Makefile'
#

TEMPLATE = xxdiff
CONFIG = release qt warn_on

debug:TMAKE_CXXFLAGS += -DXX_DEBUG

XX_VERSION=2.1

TMAKE_CFLAGS_DEBUG += -DXX_VERSION="\"$$XX_VERSION-devel ($(COMPILE_DATE))\""
TMAKE_CFLAGS_RELEASE += -DXX_VERSION="\"$$XX_VERSION\""

INCLUDEPATH += .

LEXYACC  = resParser
LEXYACC_OBJ  = $$LEXYACC.l.c $$LEXYACC.y.c $$LEXYACC.y.h
TMAKE_CLEAN += $$LEXYACC_OBJ


#
# win32-msvc
#

win32-msvc:TMAKE_CXXFLAGS += -GX -DWINDOWS
win32-msvc:INCLUDEPATH += winfixes

#
# irix-n32
#

irix-n32:TMAKE_CXXFLAGS += -woff 1375,1424,3201,1209,1110 -LANG:std
irix-n32:TMAKE_CXXFLAGS += -DCOMPILER_MIPSPRO

# always disable full warnings for C code.
irix-n32:TMAKE_CFLAGS_WARN_ON =
irix-n32:TMAKE_CC = cc
irix-n32:TMAKE_CFLAGS = $$TMAKE_CXXFLAGS

irix-n32:TMAKE_MOC = ${QTDIR}/bin/moc

irix-n32:TMAKE_LIBS += -lC -lCio -lm
irix-n32:TMAKE_LIBDIR_QT = $(QTDIR)/lib32
irix-n32:TMAKE_LIBS += -Wl,-rpath -Wl,$(QTDIR)/lib32

irix-n32:TMAKE_CFLAGS_RELEASE += -OPT:Olimit=4000


#
# linux-g++
#

linux-g++:TMAKE_CXXFLAGS += -DCOMPILER_GNU

# debugging memory problems
#linux-g++:TMAKE_CXXFLAGS += -fcheck-memory-usage
#linux-g++:TMAKE_LIBS += -lmpatrol -lbfd -liberty

#
# solaris-cc
#

solaris-cc:TMAKE_CXXFLAGS += -DCOMPILER_SUNWSPRO


# Add diff files to link against directly
DIFFUTILS_DIR = ../diffutils-2.7

# TMAKE_LIBS +=  \
# 	$$DIFFUTILS_DIR/analyze.o \
# 	$$DIFFUTILS_DIR/cmpbuf.o \
# 	$$DIFFUTILS_DIR/dir.o \
# 	$$DIFFUTILS_DIR/io.o \
# 	$$DIFFUTILS_DIR/util.o \
# 	$$DIFFUTILS_DIR/context.o \
# 	$$DIFFUTILS_DIR/ed.o \
# 	$$DIFFUTILS_DIR/ifdef.o \
# 	$$DIFFUTILS_DIR/normal.o \
# 	$$DIFFUTILS_DIR/side.o \
# 	$$DIFFUTILS_DIR/fnmatch.o \
# 	$$DIFFUTILS_DIR/regex.o \
# 	$$DIFFUTILS_DIR/version.o \
# 	$$DIFFUTILS_DIR/diff.o \
# 	$$DIFFUTILS_DIR/diff3.o

HEADERS = \
	optionsDialog.h \
	searchDialog.h \
	app.h \
	app.inline.h \
	cmdline.h \
	suicideMessageBox.h \
	defs.h \
	types.h \
	diffs.h \
	diffs.inline.h \
	builder.h \
	builder.inline.h \
	builderFiles2.h \
	builderFiles3.h \
	builderDirs2.h \
	builderConflicts.h \
	exceptions.h \
	buffer.h \
	buffer.inline.h \
	help.h \
	hordiffImp.h \
	line.h \
	line.inline.h \
	main.h \
	overview.h \
	resParser.h \
	resources.h \
	resources.inline.h \
	accelUtil.h \
	text.h \
	merged.h \
	lineNumbers.h \
	util.h \
	markersFileDialog.h \
	getopt.h \
	diffutils.h \
	diffutils_hack.h \
	doc.qml \
	version.h

SOURCES = \
	optionsDialog.cpp \
	searchDialog.cpp \
	app.cpp \
	cmdline.cpp \
	suicideMessageBox.cpp \
	main.cpp \
	overview.cpp \
	text.cpp \
	merged.cpp \
	lineNumbers.cpp \
	util.cpp \
	help.cpp \
	exceptions.cpp \
	builder.cpp \
	builderFiles2.cpp \
	builderFiles3.cpp \
	builderDirs2.cpp \
	builderConflicts.cpp \
	diffs.cpp \
	hordiffImp.cpp \
	line.cpp \
	buffer.cpp \
	resources.cpp \
	accelUtil.cpp \
	resParser.cpp \
	markersFileDialog.cpp \
	getopt.c \
	getopt1.c \
	version.c

#	diffutils.cpp \

INTERFACES = \
	markersWidgetBase.ui \
	optionsDialogBase.ui \
	searchDialogBase.ui

TARGET = xxdiff

#DEPENDPATH=../../include

#REQUIRES=large-config
