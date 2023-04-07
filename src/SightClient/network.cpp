#include "network.h"

#include "application.h"
#include "constants.h"
#include "lsettings.h"

#include <QApplication>
#include <QDataStream>
#include <QIODevice>
#include <QNetworkDatagram>
#include <QNetworkInterface>
#include <QHostInfo>



Network::Network(QObject *parent)
    : Worker{parent},
      m_udpSocket{new QUdpSocket(this)},
      m_port(Port::def)
{
    initSettings();

    m_udpSocket->bind(QHostAddress::AnyIPv4, m_port);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &Network::readSocket);
}



void Network::initSettings()
{
    LSettings settings(APP->settingsFilePath(), QSettings::IniFormat);

    settings.beginGroup(metaObject()->className());
    settings.initNumberValue(Port::name, m_port, Port::min, Port::max);
    settings.endGroup();
}



void Network::readSocket()
{
    while (m_udpSocket->hasPendingDatagrams())
        emit dataReceived(m_udpSocket->receiveDatagram().data());
}
