/*!
\file
\brief Abstract task class
\authors Alexey Lukin
\copyright Alexey Lukin
*/

#include "worker.h"



Worker::Worker(QObject *parent)
    : m_parent{parent},
      m_thread{nullptr}
{
}



void Worker::startThread()
{
    if (m_thread != nullptr)
        return;

    m_thread = new QThread(m_parent);
    moveToThread(m_thread);
    connect(m_thread, &QThread::finished, this, &QObject::deleteLater);
    m_thread->start();
}



void Worker::stopThread()
{
    if (m_thread == nullptr)
        return;

    m_thread->quit();
    m_thread->wait();
}
