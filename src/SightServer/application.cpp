#include "application.h"

#include <QJsonDocument>
#include <QJsonObject>



Application::Application(int argc, char *argv[])
    : QApplication{argc, argv},
      m_settingsFile(QStringLiteral("%1/settings.ini").arg(applicationDirPath())),
      m_network{new Network(this)}
{
    QApplication::setApplicationName(APP_NAME);
    QApplication::setApplicationVersion(APP_VERSION);
    QApplication::setOrganizationName(APP_COMPANY);

    m_mainWindow = new MainWindow;
    m_mainWindow->show();
    connect(m_mainWindow, &MainWindow::dataChanged, this, &Application::sendData);

    m_network->startThread();
}



Application::~Application()
{
    m_mainWindow->deleteLater();
    m_network->stopThread();
}



void Application::sendData(const QVariantMap &map)
{
    QMetaObject::invokeMethod(m_network, "sendData", Qt::QueuedConnection, Q_ARG(QByteArray, mapToJson(map)));
}



QByteArray Application::mapToJson(const QVariantMap &map) const
{
    const QJsonObject jsonObject = QJsonObject::fromVariantMap(map);
    const QJsonDocument jsonDocument(jsonObject);

    return jsonDocument.toJson(QJsonDocument::Compact);
}
