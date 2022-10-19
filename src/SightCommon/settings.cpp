/*!
\file QSettings wrapper class
\authors Alexey Lukin
\copyright Alexey Lukin
*/

#include "settings.h"



Settings::Settings(QObject *parent)
    : QSettings(parent)
{
}



Settings::Settings(const QString &fileName, const QSettings::Format format, QObject *parent)
    : QSettings(fileName, format, parent)
{
}



Settings::Settings(const Format format, const Scope scope, const QString &organization, const QString &application, QObject *parent)
    : QSettings(format, scope, organization, application, parent)
{

}



Settings::Settings(Scope scope, const QString &organization, const QString &application, QObject *parent)
    : QSettings(scope, organization, application, parent)
{
}



Settings::Settings(const QString &organization, const QString &application, QObject *parent)
    : QSettings(organization, application, parent)
{
}
