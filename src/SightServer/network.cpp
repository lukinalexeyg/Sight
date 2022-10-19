#include "network.h"

#include "application.h"
#include "settings.h"

#include <QNetworkDatagram>
#include <QNetworkInterface>



Network::Network(QObject *parent)
    : Worker{parent},
      m_udpSocket{new QUdpSocket(this)},
      m_port(45678)
{
    initSettings();

    m_udpSocket->bind(QHostAddress::AnyIPv4, m_port);
}



void Network::initSettings()
{
    Settings settings(app->settingsFile(), QSettings::IniFormat);

    settings.beginGroup(metaObject()->className());
    settings.initNumberValue(QStringLiteral("port"), m_port, 1, 65535);
    settings.endGroup();
}



void Network::sendData(const QByteArray &data)
{
    for (const auto &networkInterface : QNetworkInterface::allInterfaces())
        for (const auto &networkAddressEntry : networkInterface.addressEntries())
            if (networkAddressEntry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                m_udpSocket->writeDatagram(data, networkAddressEntry.broadcast(), m_port);
}
