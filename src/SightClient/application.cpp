#include "application.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>



Application::Application(int argc, char *argv[])
    : QApplication{argc, argv},
      m_settingsFile(QStringLiteral("%1/settings.ini").arg(applicationDirPath())),
      m_mainWindow{new MainWindow},
      m_network{new Network(this)}
{
    setApplicationName(APP_NAME);
    setApplicationVersion(APP_VERSION);
    setOrganizationName(APP_COMPANY);

    m_network->startThread();
    connect(m_network, &Network::dataReceived, this, &Application::onNetworkDataReceived);

    m_mainWindow->show();
}



Application::~Application()
{
    delete m_mainWindow;
    m_network->stopThread();
}



void Application::onNetworkDataReceived(const QByteArray &data)
{
    QJsonParseError jsonParseError;
    const QVariantMap map = QJsonDocument::fromJson(data, &jsonParseError).object().toVariantMap();

    if (jsonParseError.offset == QJsonParseError::NoError)
        m_mainWindow->setData(map);
}
