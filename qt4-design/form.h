
/* form.h */

#ifndef FORM_H
#define FORM_H

#include <QMainWindow>

#include <QMenuBar>
#include <QSplitter>
#include <QTextEdit>
#include <QStatusBar>

class FormWindow : public QMainWindow
{
   Q_OBJECT

   public:
      QMenuBar * mainMenu;

      QMenu * fileMenu;
      QMenu * editMenu;
      QMenu * viewMenu;

      QSplitter * vsplitter;
      QSplitter * hsplitter;

      QTabWidget * left;
      QTabWidget * right;

      QTextEdit * info;
      QStatusBar * statusBar;

   private:
      void setup ();

   public:
       explicit FormWindow (QWidget * parent = 0);
       // virtual ~ FormWindow ();
};

#endif // FORM_H
