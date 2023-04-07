#include "mainwindow.h"

#include "application.h"
#include "constants.h"
#include "slider.h"

namespace SettingsNames {
    static const QLatin1String parameters("Parameters");
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    initSettings();

    setWindowTitle(QStringLiteral("Сервер"));

    setFixedWidth(500);
    setFixedHeight(170);

    const QFont font(Font::family, Font::pointSize);
    setFont(font);

    setWidgets();
}



MainWindow::~MainWindow()
{
    QSettings settings(APP->settingsFilePath(), QSettings::IniFormat);

    settings.beginGroup(SettingsNames::parameters);
    settings.setValue(Api::angle.id, m_parameters.value(Api::angle.id));
    settings.setValue(Api::horizontalShift.id,  m_parameters.value(Api::horizontalShift.id));
    settings.setValue(Api::verticalShift.id,  m_parameters.value(Api::verticalShift.id));
    settings.endGroup();
}



void MainWindow::initSettings()
{
    LSettings settings(APP->settingsFilePath(), QSettings::IniFormat);

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



void MainWindow::setWidgets()
{
    m_gridLayout = new QGridLayout;
    m_gridLayout->setSpacing(15);

    addParameterRow(Api::angle);
    addParameterRow(Api::horizontalShift);
    addParameterRow(Api::verticalShift);

    m_pushButton = new QPushButton(QStringLiteral("Отправить"));
    connect(m_pushButton, &QPushButton::pressed, this, &MainWindow::onPushButtonPressed);

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addLayout(m_gridLayout);
    vBoxLayout->addStretch();
    vBoxLayout->addWidget(m_pushButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(vBoxLayout);
    setCentralWidget(centralWidget);
}



void MainWindow::addParameterRow(const Api::Parameter &parameter)
{
    const qreal value = m_parameters.value(parameter.id);

    QString nameText = parameter.text;
    if (!parameter.unit.isEmpty())
        nameText.append(QStringLiteral(", %1").arg(parameter.unit));

    QLabel *nameLabel = new QLabel(nameText);

    Slider *slider = new Slider(Qt::Orientation::Horizontal);
    slider->setMinimum(parameter.minValue);
    slider->setMaximum(parameter.maxValue);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setTickInterval(1.0);
    slider->setValue(value);

    QLabel *valueLabel = new QLabel;
    valueLabel->setFixedWidth(50);
    valueLabel->setAlignment(Qt::AlignHCenter);

    connect(slider, &Slider::realValueChanged, this, [this, &parameter, valueLabel](const qreal value) {
        m_parameters.insert(parameter.id, value);
        valueLabel->setText(valueToString(value));
    });

    valueLabel->setText(valueToString(slider->realValue()));

    const int currentRow = m_gridLayout->rowCount();

    m_gridLayout->addWidget(nameLabel, currentRow, 0);
    m_gridLayout->addWidget(slider, currentRow, 1);
    m_gridLayout->addWidget(valueLabel, currentRow, 2);

    m_labels.insert(parameter.id, valueLabel);
}



void MainWindow::onPushButtonPressed()
{
    QVariantMap map;

    for (auto it = m_parameters.cbegin(); it != m_parameters.cend(); ++it)
        map.insert(it.key(), it.value());

    emit dataChanged(map);
}



QString MainWindow::valueToString(const qreal value)
{
    return QString::number(value, 'g', 2);
}
