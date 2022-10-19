#ifndef NETWORK_H
#define NETWORK_H

#include "worker.h"

#include <QUdpSocket>

class Network : public Worker
{
    Q_OBJECT

public:
    explicit Network(QObject *parent = nullptr);

public slots:
    void sendData(const QByteArray &data);

private:
    QUdpSocket *m_udpSocket;
    int m_port;

private:
    void initSettings();
};

#endif // NETWORK_H
