#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

static const QLatin1String s_settingsFileName("settings.ini");

namespace Font {
    static const QLatin1String family("Segoe UI");
    static constexpr int pointSize = 11;
}

namespace Port {
    static const QLatin1String name("port");
    static constexpr int min = 1;
    static constexpr int max = 65535;
    static constexpr int def = 45678;
}

#endif // CONSTANTS_H
