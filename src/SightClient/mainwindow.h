#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "api.h"
#include "lsettings.h"

#include <QComboBox>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>

typedef QList<int> IntList;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public:
    void setData(const QVariantMap &map);

protected:
    virtual void showEvent(QShowEvent *event);

    virtual void resizeEvent(QResizeEvent *event);

private:
    QBoxLayout *m_boxLayout;
    QGraphicsView *m_graphicsView;
    QGraphicsScene *m_graphicsScene;
    QMap<Qt::GlobalColor, QGraphicsSvgItem*> m_graphicsSvgItems;
    QGridLayout *m_gridLayout;
    QMap<QString, qreal> m_parameters;
    QMap<QString, QLabel*> m_labels;

    int m_backgroundColor;
    qreal m_backgroundAspectRatio;
    int m_sightColor;

    int m_crossColor;
    qreal m_crossWidth;
    qreal m_crossSize;

private:
    void initSettings();

    void initParameter(LSettings &settings, const Api::Parameter &parameter);

    void setWidgets();

    void setGraphicsScene();

    void setGraphicsViewScale();

    void addLabels();

    void addLabel(const Api::Parameter &parameter, int row);

    void addComboBoxes();

    void setComboBox(QComboBox *comboBox, const IntList &colors, Qt::GlobalColor color, int column);

    void setSightColor(Qt::GlobalColor color);

    void updateSight();

    void addSight(Qt::GlobalColor color);

    void setSightPos(QGraphicsSvgItem *graphicsSvgItem);

    QString labelText(const QString &name, const qreal value) const;

    QSizeF getViewSize() const;
};

#endif // MAINWINDOW_H
