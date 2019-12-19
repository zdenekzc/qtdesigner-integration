#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QObject>
#include "internals/qdesigner_integration_p.h"

class LocalDesignerIntegration : public qdesigner_internal::QDesignerIntegration
{
   Q_OBJECT

   public:
      explicit LocalDesignerIntegration(QDesignerFormEditorInterface * core, QObject *parent = 0);
      virtual ~LocalDesignerIntegration() { }

   private slots:
      void slotNavigateToSlot(const QString &objectName, const QString &signalSignature, const QStringList &parameterNames);

   private:
      QDesignerFormEditorInterface * m_formEditor;
};

#endif
