#include "aspectratiowidget.h"



AspectRatioWidget::AspectRatioWidget(qreal aspectRatio, QWidget *parent, const Qt::WindowFlags f)
    : QWidget(parent, f),
      m_aspectRatio(aspectRatio),
      m_adjustedToSize(-1, -1)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
}



void AspectRatioWidget::setAspectRatio(const qreal aspectRatio)
{
    if (m_aspectRatio == aspectRatio)
        return;

    m_aspectRatio = aspectRatio;
    adjustToSize();
}



void AspectRatioWidget::resizeEvent(QResizeEvent*)
{
    adjustToSize();
}



void AspectRatioWidget::adjustToSize()
{
    const QSize size = this->size();

    if (size == m_adjustedToSize)
        return;

    m_adjustedToSize = size;

    const qreal fullWidth = size.width();
    const qreal fullHeight = size.height();
    const qreal width = qMin(fullWidth, fullHeight * m_aspectRatio);
    const qreal height = qMin(fullHeight, fullWidth / m_aspectRatio);
    const int hMargin = qRound((fullWidth - width) / 2);
    const int vMargin = qRound((fullHeight - height) / 2);

    setContentsMargins(hMargin, vMargin, hMargin, vMargin);
}
