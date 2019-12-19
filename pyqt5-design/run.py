
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtDesigner import *

import sys
import designer

class Info (QTextEdit) :
   def __init__ (self, parent = None) :
       super (Info, self).__init__ (parent)
   def navigateToSlot (self, objectName, signalSignature, parameterNames) :
       # self.append ("navigateToSlot (" + objectName + ", " + signalSignature + ", " + parameterNames.join (",") + ")")
       # print ("navigateToSlot (" + objectName + ", " + signalSignature + ", " + parameterNames.join (",") + ")")
       self.append ("navigateToSlot (" + objectName + ", " + signalSignature + ")")
       print ("navigateToSlot (" + objectName + ", " + signalSignature + ")")

app = QApplication (sys.argv)
win = QMainWindow ()

design = designer.Designer ()
design.init (win)

core = design.core
form = design.form

left = QTabWidget (win)
right = QTabWidget (win)

left.addTab (core.widgetBox (), "widgets")
left.addTab (core.objectInspector (), "objects")

right.addTab (core.propertyEditor (), "properties")
right.addTab (core.actionEditor (), "actions")
right.addTab (design.resourceEditor, "resources")
right.addTab (design.signalSlotEditor, "signals/slots")

hsplitter = QSplitter (win)
hsplitter.addWidget (left)
hsplitter.addWidget (form)
hsplitter.addWidget (right)

hsplitter.setStretchFactor (0, 10)
hsplitter.setStretchFactor (1, 10)
hsplitter.setStretchFactor (2, 10)

info = Info (win)
# QObject.connect (design.integration, SIGNAL ("navigateToSlot(QString, QString, QStringList)"), info.navigateToSlot)
design.integration.navigateToSlot.connect (info.navigateToSlot)

vsplitter = QSplitter (win)
vsplitter.setOrientation (Qt.Vertical)
vsplitter.addWidget (hsplitter)
vsplitter.addWidget (info)

vsplitter.setStretchFactor (0, 30)
vsplitter.setStretchFactor (1, 10)

win.setCentralWidget (vsplitter)

file = QFile ("example.ui")
file.open (QFile.ReadOnly)
form.setContents (file)

design.setTopLevel (win)
core.formWindowManager().setActiveFormWindow (form)

win.show ()
app.exec_ ()


def showObject (obj, level) :
    print ("   " * level, obj.objectName(), ":" ,  obj.metaObject().className ())
    for c in obj.children() :
       showObject (c, level+1)
 
for w in app.allWindows() :
    showObject (w, 1)
for w in app.topLevelWindows() :
    showObject (w, 1)

showObject (app, 1)
showObject (win, 1)
# print (win.children ())

