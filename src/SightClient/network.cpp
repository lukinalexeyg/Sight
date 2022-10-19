#include "network.h"

#include "application.h"
#include "settings.h"

#include <QApplication>
#include <QDataStream>
#include <QIODevice>
#include <QNetworkDatagram>
#include <QNetworkInterface>
#include <QHostInfo>



Network::Network(QObject *parent)
    : Worker{parent},
      m_udpSocket{new QUdpSocket(this)},
      m_port(45678)
{
    initSettings();

    m_udpSocket->bind(QHostAddress::AnyIPv4, m_port);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &Network::readSocket);
}



void Network::initSettings()
{
    Settings settings(app->settingsFile(), QSettings::IniFormat);

    settings.beginGroup(metaObject()->className());
    settings.initNumberValue(QStringLiteral("port"), m_port, 1, 65535);
    settings.endGroup();
}



void Network::readSocket()
{
    while (m_udpSocket->hasPendingDatagrams())
        emit dataReceived(m_udpSocket->receiveDatagram().data());
}
