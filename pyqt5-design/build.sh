#!/bin/sh

use_sip6=false

if test -f /etc/arch-release ; then
   use_sip6=true
fi

if grep -q 36 /etc/fedora-release 2>&1 >/dev/null ; then
   use_sip6=true
fi

if $use_sip6 ; then

   sip-build --verbose --target-dir=. --no-make || exit 1

   cd _build && make && cd .. || exit 1
   cp _build/designer/libdesigner.so designer.so || exit 1

   # required file pyproject.toml
   python run.py

   # pacman -S sip (python-pyqt5-sip) python-pyqt5 pyqt-builder
   # conflict with sip4 python-sip4

   # dnf install python3-qt5-devel PyQt-builder (sip6) python3-devel qt5-qttools-devel

   # Fedora 36: see python3-poppler-qt5- ... .fc36.src.rpm
   # Archlinux: see python-poppler-qt5, http://github.com/frescobaldi/python-poppler-qt5/blob/master/pyproject.toml

   # https://www.riverbankcomputing.com/static/Docs/PyQt-builder/pyproject_toml.html

else

   test -f Makefile && make clean
   python configure.py || exit 1
   make || exit 1
   python run.py
   # gdb -ex r --args python3 run.py

   # dnf install python3-sip-devel python3-qt5-devel qt5-qttools-devel
   # apt-get install pyqt5-dev python3-sip-dev qttools5-dev
   # pacman -S sip4 python-sip4 (python-pyqt5-sip) python-pyqt5 pkgconf

fi

