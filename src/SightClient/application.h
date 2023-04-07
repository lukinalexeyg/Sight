#ifndef APPLICATION_H
#define APPLICATION_H

#include "mainwindow.h"
#include "network.h"

#include <QApplication>

#define APP qobject_cast<Application*>(qApp)

class Application : public QApplication
{
    Q_OBJECT

public:
    explicit Application(int argc = 0, char *argv[] = 0);

    ~Application();

    QString settingsFilePath() const { return m_settingsFilePath; }

private:
    QString m_settingsFilePath;
    MainWindow *m_mainWindow;
    Network *m_network;

private:
    void onNetworkDataReceived(const QByteArray &data);
};

#endif // APPLICATION_H
