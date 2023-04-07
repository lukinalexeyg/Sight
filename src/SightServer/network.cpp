#include "network.h"

#include "application.h"
#include "constants.h"
#include "lsettings.h"

#include <QNetworkDatagram>
#include <QNetworkInterface>



Network::Network(QObject *parent)
    : Worker{parent},
      m_udpSocket{new QUdpSocket(this)},
      m_port(Port::def)
{
    initSettings();

    m_udpSocket->bind(QHostAddress::AnyIPv4, m_port);
}



void Network::initSettings()
{
    LSettings settings(APP->settingsFilePath(), QSettings::IniFormat);

    settings.beginGroup(metaObject()->className());
    settings.initNumberValue(Port::name, m_port, Port::min, Port::max);
    settings.endGroup();
}



void Network::sendData(const QByteArray &data)
{
    for (const auto &networkInterface : QNetworkInterface::allInterfaces())
        for (const auto &networkAddressEntry : networkInterface.addressEntries())
            if (networkAddressEntry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                m_udpSocket->writeDatagram(data, networkAddressEntry.broadcast(), m_port);
}
