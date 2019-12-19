
%Module designer

%Import QtGui/QtGuimod.sip
%Import QtWidgets/QtWidgetsmod.sip
%Import QtDesigner/QtDesignermod.sip

class QDesignerIntegrationInterface : public QObject /Abstract/
{
%TypeHeaderCode
#include <QDesignerIntegration>
%End

public:
   explicit QDesignerIntegrationInterface(QDesignerFormEditorInterface *core /TranserThis/, QObject *parent = Q_NULLPTR);
   virtual ~QDesignerIntegrationInterface();

signals:
   void navigateToSlot(const QString &objectName, const QString &signalSignature, const QStringList &parameterNames);
};

class QDesignerIntegration : public QDesignerIntegrationInterface  /Abstract/
{
%TypeHeaderCode
#include <QDesignerIntegration>
%End

public:
   explicit QDesignerIntegration(QDesignerFormEditorInterface *core, QObject *parent = Q_NULLPTR);
   virtual ~QDesignerIntegration();
};

class LocalDesignerIntegration : public QDesignerIntegration /Abstract/
{
%TypeHeaderCode
#include <designer.h>
%End

public:
   explicit LocalDesignerIntegration(QDesignerFormEditorInterface * core, QObject *parent = 0);
};

class Designer
{

%TypeHeaderCode
#include <designer.h>
%End

public:
      QDesignerFormEditorInterface * core;
      QDesignerFormWindowInterface * form;
      LocalDesignerIntegration * integration;
      QWidget * resourceEditor;
      QWidget * signalSlotEditor;

      void init (QWidget * window);
      void setTopLevel (QWidget * window);
};

