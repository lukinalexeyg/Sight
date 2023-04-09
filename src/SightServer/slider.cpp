#include "slider.h"



Slider::Slider(Qt::Orientation orientation, QWidget *parent)
    : QSlider{orientation, parent}
{
    connect(this, &QSlider::valueChanged, this, &Slider::onValueChanged);
}



Slider::Slider(QWidget *parent)
    : QSlider{parent}
{
    connect(this, &QSlider::valueChanged, this, &Slider::onValueChanged);
}



void Slider::setScale(const qreal scale)
{
    if (m_scale == scale)
        return;

    m_scale = scale;
    setMinimum(m_realMinimum);
    setMaximum(m_realMaximum);
}



void Slider::setMinimum(const qreal value)
{
    const int intValue = qRound(value / m_scale);
    QSlider::setMinimum(intValue);
    m_realMinimum = realMinimum();
}



qreal Slider::realMinimum() const
{
    return m_scale * minimum();
}



void Slider::setMaximum(const qreal value)
{
    const int intValue = qRound(value / m_scale);
    QSlider::setMaximum(intValue);
    m_realMaximum = realMaximum();
}



qreal Slider::realMaximum() const
{
    return m_scale * maximum();
}



void Slider::setTickInterval(const qreal interval)
{
    const int intInterval = qRound(interval / m_scale);
    QSlider::setTickInterval(intInterval);
}



void Slider::setValue(const qreal value)
{
    const int intValue = qRound(value / m_scale);
    QSlider::setValue(intValue);
}



qreal Slider::realTickInterval() const
{
    return m_scale * tickInterval();
}



qreal Slider::realValue() const
{
    return m_scale * value();
}



void Slider::onValueChanged()
{
    emit realValueChanged(realValue());
}
