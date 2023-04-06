#include "mainwindow.h"

#include "application.h"
#include "aspectratiowidget.h"

#include <QApplication>
#include <QGraphicsLineItem>

#define globalColor(color) static_cast<Qt::GlobalColor>(color)

namespace SettingsNames {
    static const QLatin1String background("Background");
    static const QLatin1String cross("Cross");
    static const QLatin1String sight("Sight");
    static const QLatin1String parameters("Parameters");

    static const QLatin1String color("color");
    static const QLatin1String width("width");
    static const QLatin1String size("size");
    static const QLatin1String aspectRatio("aspect_ratio");
}

typedef QMap<Qt::GlobalColor, QString> ColorMap;

namespace Colors {
    static const ColorMap names = {
        {Qt::black, QStringLiteral("Черный")},
        {Qt::white, QStringLiteral("Белый")},
        {Qt::gray, QStringLiteral("Серый")},
        {Qt::red, QStringLiteral("Красный")}
    };
}

namespace Background {
    static constexpr qreal scale = 6000.0 / 360.0;
    static const IntList colors ({Qt::black, Qt::white, Qt::gray});
}

namespace Sight {
    static constexpr qreal size = 20.0;
    static constexpr qreal pxSize = 1024.0;
    static constexpr qreal scale = size / pxSize;

    static const IntList colors ({Qt::red, Qt::black});

    static const ColorMap files = {
        {Qt::red, QStringLiteral(":/svg/crosshair red.svg")},
        {Qt::black, QStringLiteral(":/svg/crosshair black.svg")}
    };
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
      m_backgroundColor(Qt::black),
      m_backgroundAspectRatio(4.0/3.0),
      m_sightColor(Qt::red),
      m_crossColor(Qt::green),
      m_crossWidth(0.2),
      m_crossSize(10.0)
{
    initSettings();

    setWindowTitle(QStringLiteral("Клиент"));

    setMinimumWidth(640);
    setMinimumHeight(600);

    const QFont font(QLatin1String("Segoe UI"), 11);
    setFont(font);

    setWidgets();
}



MainWindow::~MainWindow()
{
    QSettings settings(app->settingsFile(), QSettings::IniFormat);

    settings.beginGroup(SettingsNames::background);
    settings.setValue(SettingsNames::color, m_backgroundColor);
    settings.endGroup();

    settings.beginGroup(SettingsNames::sight);
    settings.setValue(SettingsNames::color, m_sightColor);
    settings.endGroup();

    settings.beginGroup(SettingsNames::parameters);
    settings.setValue(Api::angle.id, m_parameters.value(Api::angle.id));
    settings.setValue(Api::horizontalShift.id, m_parameters.value(Api::horizontalShift.id));
    settings.setValue(Api::verticalShift.id, m_parameters.value(Api::verticalShift.id));
    settings.endGroup();
}



void MainWindow::initSettings()
{
    LSettings settings(app->settingsFile(), QSettings::IniFormat);

    settings.beginGroup(SettingsNames::background);
    settings.initValue(SettingsNames::color, m_backgroundColor, Background::colors);
    settings.initNumberValue(SettingsNames::aspectRatio, m_backgroundAspectRatio, 1.0, 2.0);
    settings.endGroup();

    settings.beginGroup(SettingsNames::cross);
    settings.initNumberValue(SettingsNames::color, m_crossColor, static_cast<int>(Qt::color0), static_cast<int>(Qt::darkYellow));
    settings.initNumberValue(SettingsNames::width, m_crossWidth, 0.1, 1.0);
    settings.initNumberValue(SettingsNames::size, m_crossSize, 1.0, 20.0);
    settings.endGroup();

    settings.beginGroup(SettingsNames::sight);
    settings.initValue(SettingsNames::color, m_sightColor, Sight::colors);
    settings.endGroup();

    settings.beginGroup(SettingsNames::parameters);
    initParameter(settings, Api::angle);
    initParameter(settings, Api::horizontalShift);
    initParameter(settings, Api::verticalShift);
    settings.endGroup();
}



void MainWindow::initParameter(LSettings &settings, const Api::Parameter &parameter)
{
    qreal value = parameter.defaultValue;
    settings.initNumberValue(parameter.id, value, parameter.minValue, parameter.maxValue);
    m_parameters.insert(parameter.id, value);
}



void MainWindow::showEvent(QShowEvent*)
{
    m_boxLayout->activate();
    setGraphicsViewScale();
}



void MainWindow::resizeEvent(QResizeEvent*)
{
    setGraphicsViewScale();
}



void MainWindow::setWidgets()
{
    setGraphicsScene();

    m_graphicsView = new QGraphicsView(m_graphicsScene);

    m_boxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    m_boxLayout->addWidget(m_graphicsView);
    m_boxLayout->setMargin(0);

    AspectRatioWidget *aspectWidget = new AspectRatioWidget;
    aspectWidget->setLayout(m_boxLayout);

    m_gridLayout = new QGridLayout;
    m_gridLayout->setSpacing(10);
    m_gridLayout->setColumnMinimumWidth(0, 140);
    m_gridLayout->setColumnMinimumWidth(1, 140);
    m_gridLayout->setColumnMinimumWidth(2, 320);

    addLabels();
    addComboBoxes();

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addStretch();
    hBoxLayout->addLayout(m_gridLayout);
    hBoxLayout->addStretch();

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(aspectWidget);
    vBoxLayout->addLayout(hBoxLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(vBoxLayout);
    setCentralWidget(centralWidget);

    resize(1024, 768);
}



void MainWindow::setGraphicsScene()
{
    m_graphicsScene = new QGraphicsScene(this);
    m_graphicsScene->setBackgroundBrush(globalColor(m_backgroundColor));

    QPen pen;
    pen.setColor(globalColor(m_crossColor));
    pen.setWidth(m_crossWidth);

    const qreal halfCrossSize = m_crossSize / 2.0;

    QGraphicsLineItem *graphicsLineItem1 = new QGraphicsLineItem;
    graphicsLineItem1->setLine(-halfCrossSize, 0.0, halfCrossSize, 0.0);
    graphicsLineItem1->setPen(pen);

    QGraphicsLineItem *graphicsLineItem2 = new QGraphicsLineItem;
    graphicsLineItem2->setLine(0.0, -halfCrossSize, 0.0, halfCrossSize);
    graphicsLineItem2->setPen(pen);

    m_graphicsScene->addItem(graphicsLineItem1);
    m_graphicsScene->addItem(graphicsLineItem2);

    setSightColor(globalColor(m_sightColor));
}



void MainWindow::addLabels()
{
    QLabel *label1 = new QLabel(QStringLiteral("Цвет фона:"));
    label1->setAlignment(Qt::AlignCenter);

    QLabel *label2 = new QLabel(QStringLiteral("Цвет прицела:"));
    label2->setAlignment(Qt::AlignCenter);

    m_gridLayout->addWidget(label1, 1, 0);
    m_gridLayout->addWidget(label2, 1, 1);

    addLabel(Api::angle, 0);
    addLabel(Api::horizontalShift,  1);
    addLabel(Api::verticalShift, 2);
}



void MainWindow::addLabel(const Api::Parameter &parameter, const int row)
{
    const qreal value = m_parameters.value(parameter.id);

    QLabel *label = new QLabel;    
    label->setText(labelText(parameter.id, value));
    m_gridLayout->addWidget(label, row, 2);
    m_labels.insert(parameter.id, label);
}



void MainWindow::addComboBoxes()
{
    QComboBox *backgroundComboBox = new QComboBox;
    setComboBox(backgroundComboBox, Background::colors, globalColor(m_backgroundColor), 0);

    connect(backgroundComboBox, &QComboBox::currentTextChanged, this, [this](const QString &text) {
        const Qt::GlobalColor color = Colors::names.key(text);
        m_graphicsScene->setBackgroundBrush(color);
        m_backgroundColor = color;
    });

    QComboBox *sightComboBox = new QComboBox;
    setComboBox(sightComboBox, Sight::colors, globalColor(m_sightColor), 1);

    connect(sightComboBox, &QComboBox::currentTextChanged, this, [this](const QString &text) {
        setSightColor(Colors::names.key(text));
    });
}



void MainWindow::setComboBox(QComboBox *comboBox, const IntList &colors, const Qt::GlobalColor color, const int column)
{
    int currentIndex = 0;
    int i = 0;

    const QString currentName = Colors::names.value(color);

    for (const int color : colors) {
        const QString name = Colors::names.value(globalColor(color));

        comboBox->addItem(name);

        if (name == currentName)
            currentIndex = i;

        ++i;
    }

    comboBox->setCurrentIndex(currentIndex);

    m_gridLayout->addWidget(comboBox, 2, column);
}



void MainWindow::setData(const QVariantMap &map)
{
    bool sightPosChanged = false;

    for (auto it = map.cbegin(); it != map.cend(); ++it) {
        if (!m_parameters.contains(it.key()))
            continue;

        const qreal value = it.value().toDouble();

        m_parameters.insert(it.key(), value);

        QLabel *label = m_labels.value(it.key());
        label->setText(labelText(it.key(), value));

        if (it.key() == Api::angle.id)
            setGraphicsViewScale();

        else if (it.key() == Api::horizontalShift.id || it.key() == Api::verticalShift.id)
            sightPosChanged = true;
    }

    if (sightPosChanged)
        updateSight();
}



void MainWindow::setGraphicsViewScale()
{
    const QSizeF size = getViewSize();

    m_graphicsView->setSceneRect(-size.width() / 2.0, -size.height() / 2.0, size.width(), size.height());
    m_graphicsView->fitInView(m_graphicsView->sceneRect());
}



void MainWindow::setSightColor(const Qt::GlobalColor color)
{
    QGraphicsSvgItem *graphicsSvgItem = m_graphicsSvgItems.value(color, nullptr);

    if (graphicsSvgItem == nullptr)
        addSight(color);

    for (auto it = m_graphicsSvgItems.cbegin(); it != m_graphicsSvgItems.cend(); ++it) {
        if (it.key() == color)
            it.value()->show();
        else
            it.value()->hide();
    }

    m_sightColor = color;
}



void MainWindow::addSight(const Qt::GlobalColor color)
{
    QGraphicsSvgItem *graphicsSvgItem = new QGraphicsSvgItem(Sight::files.value(color));
    graphicsSvgItem->setScale(Sight::scale);
    setSightPos(graphicsSvgItem);
    m_graphicsScene->addItem(graphicsSvgItem);
    m_graphicsSvgItems.insert(color, graphicsSvgItem);
}



void MainWindow::updateSight()
{
    QGraphicsSvgItem *graphicsSvgItem = m_graphicsSvgItems.value(globalColor(m_sightColor), nullptr);
    setSightPos(graphicsSvgItem);
}



void MainWindow::setSightPos(QGraphicsSvgItem *graphicsSvgItem)
{
    const QSizeF size = getViewSize();

    const qreal x = (size.width() * m_parameters.value(Api::horizontalShift.id) - Sight::size) / 2.0;
    const qreal y = (size.height() * m_parameters.value(Api::verticalShift.id) - Sight::size) / 2.0;

    graphicsSvgItem->setPos(x, y);
}



QString MainWindow::labelText(const QString &name, const qreal value) const
{
    const Api::Parameter *parameter = Api::parameters.value(name);

    QString text = QStringLiteral("%1: %2").arg(parameter->text).arg(value);

    if (!parameter->unit.isEmpty())
        text.append(QStringLiteral(" %1").arg(parameter->unit));

    return text;
}



QSizeF MainWindow::getViewSize() const
{
    const qreal width = m_parameters.value(Api::angle.id) * Background::scale;
    const qreal height = width / m_backgroundAspectRatio;

    return QSizeF(width, height);
}
