#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "api.h"
#include "settings.h"

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

signals:
    void dataChanged(const QVariantMap &data);

private:
    QGridLayout *m_gridLayout;
    QPushButton *m_pushButton;
    QMap<QString, QLabel*> m_labels;
    QMap<QString, qreal> m_parameters;

private:
    void initSettings();

    void initParameter(Settings &settings, const Api::Parameter &parameter);

    void setWidgets();

    void addParameterRow(const Api::Parameter &parameter);

    void onPushButtonPressed();

    static QString valueToString(qreal value);
};

#endif // MAINWINDOW_H
