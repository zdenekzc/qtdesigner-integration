#include "integration.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>

LocalDesignerIntegration::LocalDesignerIntegration (QDesignerFormEditorInterface *core, QObject *parent)
   : QDesignerIntegration (core, parent),
     m_formEditor (core)
{
   // setSlotNavigationEnabled (true);

   setFeatures (features () | SlotNavigationFeature);

   connect (this, SIGNAL(navigateToSlot(QString, QString, QStringList)),
            this, SLOT(slotNavigateToSlot(QString, QString, QStringList)));
}

void LocalDesignerIntegration::slotNavigateToSlot (const QString & objectName, const QString & signalSignature, const QStringList & parameterNames)
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (bus.isConnected ())
    {
        QDBusInterface ifc ("org.example.receiver", "/", "", bus);
        if (ifc.isValid())
        {
            ifc.call ("hello", "navigateToSlot " + objectName + "." + signalSignature);

            // QDBusReply <QString> reply = ifc.call ("hello2", "Hello2 from Qt");
            // if (reply.isValid())
            //    ui->textEdit->append ("Reply was: " + reply.value());
        }
    }
}

#include "integration.moc"
