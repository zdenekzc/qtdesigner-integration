
/* form.cc */

#include "form.h"

#include <QAction>
#include <QPushButton>
#include <QSplitter>

#include <QApplication>

#include <QFile>

#include <QtDesigner/QtDesigner>
#include <QtDesigner/QDesignerComponents>
#include <QPluginLoader>

#include "integration.h"

#include <iostream>

#include <cassert>

/* ---------------------------------------------------------------------- */

void FormWindow::setup ()
{
   #if 0
   QDesignerComponents::initializeResources();
   #endif

   QDesignerFormEditorInterface* core = QDesignerComponents::createFormEditor (this);

   core->setWidgetBox (QDesignerComponents::createWidgetBox (core, 0));

   core->setPropertyEditor (QDesignerComponents::createPropertyEditor (core, this));
   core->setActionEditor (QDesignerComponents::createActionEditor (core, 0));
   core->setObjectInspector (QDesignerComponents::createObjectInspector (core, 0));

   // create propertyEditor before QDesignerIntegration
   // otherwise changes in propertyEditor are not displayed on designed form

   // create QDesignerIntegration before createFormWindow
   // otherwise propertyEditor and objectInspector are not updated when user selects designed widget

   // new qdesigner_internal::QDesignerIntegration (core, this);
   new LocalDesignerIntegration (core, this);
   QDesignerIntegration::initializePlugins (core);

   QDesignerFormWindowInterface * form = core->formWindowManager()->createFormWindow();

   /* components */

   mainMenu = new QMenuBar (this);

   left = new QTabWidget (this);
   // left->setTabPosition (QTabWidget::West);

   right = new QTabWidget (this);
   // right->setTabPosition (QTabWidget::East);

   info = new QTextEdit (this);
   statusBar = new QStatusBar (this);

   /* tabs */

   left->addTab (core->objectInspector(), "objects");
   left->addTab (core->widgetBox (), "widgets");

   right->addTab (core->propertyEditor (), "properties");
   right->addTab (core->actionEditor (), "actions");

   /* layout */

   hsplitter = new QSplitter (this);
   hsplitter->addWidget (left);
   hsplitter->addWidget (form);
   hsplitter->addWidget (right);

   hsplitter->setStretchFactor (0, 10);
   hsplitter->setStretchFactor (1, 10);
   hsplitter->setStretchFactor (2, 10);

   vsplitter = new QSplitter (this);
   vsplitter->setOrientation (Qt::Vertical);
   vsplitter->addWidget (hsplitter);
   vsplitter->addWidget (info);

   vsplitter->setStretchFactor (0, 30);
   vsplitter->setStretchFactor (1, 10);

   /* menu, toolbar, statusbar */

   this->setMenuBar (mainMenu);
   this->setCentralWidget (vsplitter);
   this->setStatusBar (statusBar);

   /* menu */

   fileMenu = mainMenu->addMenu ("&File");
   viewMenu = mainMenu->addMenu ("&View");
   editMenu = mainMenu->addMenu ("&Edit");

   /* actions */

   QAction * quit = new QAction (this);
   quit->setText ("&Quit");
   quit->setShortcut (Qt::CTRL + Qt::Key_Q);
   quit->setIcon (QIcon::fromTheme ("application-exit"));
   QObject::connect (quit, SIGNAL(triggered()), this, SLOT(close()));

   fileMenu->addAction (quit);

   QAction * show_info = new QAction (this);
   show_info->setText ("info");
   show_info->setCheckable (true);
   show_info->setChecked (true);
   QObject::connect (show_info, SIGNAL(triggered(bool)), info, SLOT(setVisible(bool)));

   viewMenu->addAction (show_info);

   /* open file */

   QFile file ("example.ui");
   file.open (QFile::ReadOnly);
   form->setContents (&file);

   /* complete */

   core->setTopLevel (this);
   core->formWindowManager()->setActiveFormWindow (form);
   // connect (form, SIGNAL(changed()), this, SLOT(formChanged()));
}

/* ---------------------------------------------------------------------- */

FormWindow::FormWindow (QWidget* parent) :
   QMainWindow (parent),
   mainMenu (NULL),
   fileMenu (NULL),
   editMenu (NULL),
   viewMenu (NULL),
   vsplitter (NULL),
   hsplitter (NULL),
   left (NULL),
   right (NULL),
   info (NULL),
   statusBar (NULL)
{
   setup ();
}

/* ---------------------------------------------------------------------- */

extern "C" int main (int argc, char * * argv)
{
   QApplication app (argc, argv);
   app.setApplicationName ("qt-design");

   FormWindow * win = new FormWindow ();
   win->show ();

   return app.exec();
}

/* ---------------------------------------------------------------------- */

#include "form.moc"

/* ---------------------------------------------------------------------- */
