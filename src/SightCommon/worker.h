/*!
\file
\brief Abstract task class
\authors Alexey Lukin
\copyright Alexey Lukin
*/

#ifndef WORKER_H
#define WORKER_H

#include <QThread>

/*!
\brief Abstract task class
*/
class Worker : public QObject
{
    Q_OBJECT

public:
    /*!
    Constructs a Worker object.
    \param parent parent of a private QThread member
    */
    explicit Worker(QObject *parent);

    /*!
    Moves the object to the new thread and starts it.
    */
    void startThread();

    /*!
    Stops the thread and delete the object later.
    */
    void stopThread();

private:
    QObject *m_parent;
    QThread *m_thread;
};

#endif // WORKER_H
