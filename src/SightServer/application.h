#ifndef APPLICATION_H
#define APPLICATION_H

#include "network.h"
#include "mainwindow.h"

#include <QApplication>

#define app qobject_cast<Application*>(qApp)

class Application : public QApplication
{
    Q_OBJECT

public:
    explicit Application(int argc = 0, char *argv[] = 0);

    ~Application();

    QString settingsFile() const { return m_settingsFile; }

private:
    QString m_settingsFile;
    MainWindow *m_mainWindow;
    Network *m_network;

private:
    void sendData(const QVariantMap &map);

    QByteArray mapToJson(const QVariantMap &map) const;
};

#endif // APPLICATION_H
