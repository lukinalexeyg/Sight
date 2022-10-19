#ifndef NETWORK_H
#define NETWORK_H

#include "worker.h"

#include <QUdpSocket>

class Network : public Worker
{
    Q_OBJECT

public:
    explicit Network(QObject *parent = nullptr);

signals:   
    void dataReceived(const QByteArray &data);

private:
    QUdpSocket *m_udpSocket;
    int m_port;

private:
    void initSettings();

    void readSocket();
};

#endif // NETWORK_H
