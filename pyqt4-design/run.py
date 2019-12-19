
from PyQt4.QtCore import *
from PyQt4.QtGui import *
# from PyQt4.QtDesigner import *

import sys
import designer

class Info (QTextEdit) :
   def __init__ (self, parent = None) :
       super (Info, self).__init__ (parent)
   def navigateToSlot (self, objectName, signalSignature, parameterNames) :
       self.append ("navigateToSlot (" + objectName + ", " + signalSignature + ", " + parameterNames.join (",") + ")")
       print ("navigateToSlot (" + objectName + ", " + signalSignature + ", " + parameterNames.join (",") + ")")
   def onTabChange (self) :
       self.append ("tab changed")
       print ("tab changed")


app = QApplication (sys.argv)
win = QMainWindow ()

design = designer.Designer ()
design.init (win)

core = design.core
form = core.formWindowManager ().createFormWindow ()

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
# left.currentChanged.connect (info.onTabChange)
# QObject.connect (left, SIGNAL ("currentChanged (int)"), info.onTabChange)
QObject.connect (design.integration, SIGNAL ("navigateToSlot(QString, QString, QStringList)"), info.navigateToSlot)

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
