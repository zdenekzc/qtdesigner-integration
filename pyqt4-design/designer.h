
/* designer.h */

#include <QtDesigner/QtDesigner>
#include <QtDesigner/QDesignerComponents>

#include "internals/qdesigner_integration_p.h"

/* ---------------------------------------------------------------------- */

class LocalDesignerIntegration : public qdesigner_internal::QDesignerIntegration
{
   public:
      explicit LocalDesignerIntegration(QDesignerFormEditorInterface * core, QObject *parent = 0) :
         qdesigner_internal::QDesignerIntegration (core, parent)
      {
          setSlotNavigationEnabled (true);
      }
};

/* ---------------------------------------------------------------------- */

class Designer
{
   public:
      QDesignerFormEditorInterface * core;
      QObject * integration;
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

          // new qdesigner_internal::QDesignerIntegration (core, window);
          integration = new LocalDesignerIntegration (core, window);
          qdesigner_internal::QDesignerIntegration::initializePlugins (core);

          /*
          formDesigner = core->formWindowManager()->createFormWindow();

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
