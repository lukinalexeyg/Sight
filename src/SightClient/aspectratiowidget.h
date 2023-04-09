#ifndef ASPECTRATIOWIDGET_H
#define ASPECTRATIOWIDGET_H

#include <QResizeEvent>
#include <QWidget>

class AspectRatioWidget : public QWidget
{
public:
    explicit AspectRatioWidget(qreal aspectRatio = 4.0/3.0, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

public:
    void setAspectRatio(qreal aspectRatio);

    qreal aspectRatio() const { return m_aspectRatio; }

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    qreal m_aspectRatio;
    QSize m_adjustedToSize;

private:
    void adjustToSize();
};

#endif // ASPECTRATIOWIDGET_H
