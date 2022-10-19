#include "network.h"

#include <QDataStream>
#include <QIODevice>
#include <QNetworkDatagram>
#include <QNetworkInterface>
#include <QHostInfo>

constexpr auto s_localPort = 45678;
constexpr auto s_timeoutInterval = 500;



Network::Network(QObject *parent)
    : Worker{QLatin1String("Worker"), parent},
      m_udpSocket{new QUdpSocket(this)},
      m_timer{new QTimer(this)}
{
    m_udpSocket->bind(QHostAddress::AnyIPv4, s_localPort);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &Network::readSocket);

    m_timer->setSingleShot(true);
    m_timer->setInterval(s_timeoutInterval);
    connect(m_timer, &QTimer::timeout, this, &Network::onTimerTimeout);
}



void Network::sendData(const QByteArray &data)
{
    m_timer->stop();

    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << data;

    qDebug() << byteArray;

    for (const auto &networkInterface : QNetworkInterface::allInterfaces())
        for (const auto &networkAddressEntry : networkInterface.addressEntries())
            if (networkAddressEntry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                m_udpSocket->writeDatagram(byteArray, networkAddressEntry.broadcast(), s_localPort);

    m_timer->start();
    emit statusChanged(Status::Sending);
}



void Network::readSocket()
{
    while (m_udpSocket->hasPendingDatagrams()) {
        const QNetworkDatagram networkDatagram = m_udpSocket->receiveDatagram();
        QDataStream dataStream(networkDatagram.data());
        QString inputMessage;
        dataStream >> inputMessage;

        const quint32 ipV4Address = networkDatagram.senderAddress().toIPv4Address();
        const QString host = networkDatagram.senderAddress().toString();
//        const quint32 thisIPv4Address = System::localIPAddress(QString("%1/%2").arg(host).arg(24)).toIPv4Address();

//        if (name != QHostInfo::localHostName() || ipV4Address == m_ipV4Address) {
//        }

        qDebug() << ipV4Address << host << inputMessage;
    }
}



void Network::onTimerTimeout()
{
    emit statusChanged(Status::Error);
}
