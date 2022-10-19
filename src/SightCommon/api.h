#ifndef API_H
#define API_H

#include <QMap>

namespace Api {

struct Parameter {
    QString id;
    QString text;
    QString unit;
    qreal minValue;
    qreal maxValue;
    qreal defaultValue;
};

static const Parameter angle = {
    QStringLiteral("angle"),
    QStringLiteral("Угол камеры по горизонтали"),
    QStringLiteral("град."),
    2.0,
    5.0,
    3.5
};

static const Parameter horizontalShift = {
    QStringLiteral("horizontal_shift"),
    QStringLiteral("Отступ по горизонтали"),
    QString(),
    -1.0,
    1.0,
    0.0
};

static const Parameter verticalShift = {
    QStringLiteral("vertical_shift"),
    QStringLiteral("Отступ по вертикали"),
    QString(),
    -1.0,
    1.0,
    0.0
};

static const QMap<QString, Parameter> parameters = {
    {angle.id, angle},
    {horizontalShift.id, horizontalShift},
    {verticalShift.id, verticalShift}
};

}

#endif // API_H
