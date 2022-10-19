/*!
\file QSettings wrapper class
\authors Alexey Lukin
\copyright Alexey Lukin
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

/*!
\brief QSettings wrapper
*/
class Settings : public QSettings
{
    Q_OBJECT

public:
    /*!
    Constructs a Settings object.
    */
    explicit Settings(QObject *parent = nullptr);

    /*!
    Constructs a Settings object.
    */
    explicit Settings(const QString &fileName, QSettings::Format format, QObject *parent = nullptr);

    /*!
    Constructs a Settings object.
    */
    explicit Settings(QSettings::Format format,
                      QSettings::Scope scope,
                      const QString &organization,
                      const QString &application = QString(),
                      QObject *parent = nullptr);

    /*!
    Constructs a Settings object.
    */
    explicit Settings(QSettings::Scope scope,
                      const QString &organization,
                      const QString &application = QString(),
                      QObject *parent = nullptr);

    /*!
    Constructs a Settings object.
    */
    explicit Settings(const QString &organization, const QString &application = QString(), QObject *parent = nullptr);

    /*!
    Initialize setting.
    \param name name of the setting
    \param value value of the setting
    \param allowedValues allowed values of the setting
    */
    template <typename T>
    void initValue(const QString &name, T &v, const QList<T> &allowedValues = QList<T>())
    {
        const QVariant a = value(name, v);
        T newValue = a.value<T>();

        if (!allowedValues.isEmpty() && !allowedValues.contains(newValue)) {
            if (allowedValues.contains(v))
                newValue = v;
            else
                newValue = allowedValues.first();
        }

        setValue(name, v);
        v = newValue;
    }

    /*!
    Initialize number setting.
    \param name name of the setting
    \param v value of the setting
    \param min minimal value of the setting
    \param max maximal value of the setting
    */
    template <typename T>
    void initNumberValue(const QString &name, T &v, T min, T max)
    {
        const QVariant a = value(name, v);
        v = a.value<T>();
        v = qBound(min, v, max);
        setValue(name, v);
    }
};

#endif // SETTINGS_H
