#ifndef SLIDER_H
#define SLIDER_H

#include <QSlider>

class Slider : public QSlider
{
    Q_OBJECT

public:
    explicit Slider(Qt::Orientation orientation, QWidget *parent = nullptr);

    explicit Slider(QWidget *parent = nullptr);

public:
    void setScale(qreal scale);

    qreal scale() const { return m_scale; }

    void setMinimum(qreal value);

    qreal realMinimum() const;

    void setMaximum(qreal value);

    qreal realMaximum() const;

    void setTickInterval(qreal interval);

    void setValue(qreal value);

    qreal realTickInterval() const;

    qreal realValue() const;

signals:
    void realValueChanged(qreal value);

private:
    qreal m_scale = 0.01;
    qreal m_realMinimum;
    qreal m_realMaximum;

private:
    void onValueChanged();
};

#endif // SLIDER_H
