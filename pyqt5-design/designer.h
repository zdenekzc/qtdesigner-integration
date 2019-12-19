
/* designer.h */

#ifndef _DESIGNER_H_
#define _DESIGNER_H_


#include <QtWidgets/QWidget>
#include <QtDesigner/QtDesigner>
#include <QtDesigner/QDesignerComponents>
#include <QtDesigner/QDesignerIntegration>

/* ---------------------------------------------------------------------- */

class LocalDesignerIntegration : public QDesignerIntegration
{
   public:
      explicit LocalDesignerIntegration(QDesignerFormEditorInterface * core, QObject *parent = 0) :
         QDesignerIntegration (core, parent)
      {
         // setSlotNavigationEnabled (true);
         setFeatures (features () | SlotNavigationFeature);
      }

   signals:
      void navigateToSlot(const QString &objectName, const QString &signalSignature, const QStringList &parameterNames);
};

/* ---------------------------------------------------------------------- */

class Designer
{
   public:
      QDesignerFormEditorInterface * core;
      QDesignerFormWindowInterface * form;
      LocalDesignerIntegration * integration;
      QWidget * resourceEditor;
      QWidget * signalSlotEditor;
      
   public:

      void init (QWidget * window)
      {
          core = QDesignerComponents::createFormEditor (window);

          core->setWidgetBox (QDesignerComponents::createWidgetBox (core, window));
          core->setPropertyEditor (QDesignerComponents::createPropertyEditor (core, window));
          core->setActionEditor (QDesignerComponents::createActionEditor (core, window));
          core->setObjectInspector (QDesignerComponents::createObjectInspector (core, window));
          core->setActionEditor (QDesignerComponents::createActionEditor (core, window));

          resourceEditor = QDesignerComponents::createResourceEditor (core, window);
          signalSlotEditor = QDesignerComponents::createSignalSlotEditor (core, window);

          // create propertyEditor before QDesignerIntegration
          // otherwise changes in propertyEditor are not displayed on designed form

          // create QDesignerIntegration before createFormWindow
          // otherwise propertyEditor and objectInspector are not updated when user selects designed widget

          // new QDesignerIntegration (core, window);
          integration = new LocalDesignerIntegration (core, window);
          QDesignerIntegration::initializePlugins (core);

          form = core->formWindowManager()->createFormWindow();

          /*
          objectInspector = core->objectInspector();
          widgetBox = core->widgetBox ();

          propertyEditor = core->propertyEditor ();
          actionEditor = core->actionEditor ();
          */
       }

       void setTopLevel (QWidget * window)
       {
          core->setTopLevel (window);
       }
};

/* ---------------------------------------------------------------------- */

#endif
