
%Module designer

%Import QtGui/QtGuimod.sip
%Import QtDesigner/QtDesignermod.sip

class Designer
{

%TypeHeaderCode
#include <designer.h>
%End

public:
      QDesignerFormEditorInterface * core;
      QObject * integration;

      QWidget * resourceEditor;
      QWidget * signalSlotEditor;

      void init (QWidget * window);
      void setTopLevel (QWidget * window);
};
