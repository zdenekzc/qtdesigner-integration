#include "sender.h"
#include "ui_sender.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>

Sender::Sender(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sender)
{
    ui->setupUi(this);
}

Sender::~Sender()
{
    delete ui;
}

void Sender::on_actionRun_triggered ()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (bus.isConnected ())
    {
        QDBusInterface ifc ("org.example.receiver", "/", "", bus);
        if (ifc.isValid())
        {
            ifc.call ("hello", "Hello from Qt");
            ui->textEdit->append ("Message sent");

            QDBusReply <QString> reply = ifc.call ("hello2", "Hello2 from Qt");
            if (reply.isValid())
                ui->textEdit->append ("Reply was: " + reply.value());
        }
    }
}

int main (int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sender w;
    w.show();

    return a.exec();
}



