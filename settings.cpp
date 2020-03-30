#include "settings.h"

#include <QSettings>
#include <QString>
#include <QVariant>
#include <QScreen>
#include <QGuiApplication>
#include <QDebug>

Globals g;

static int resolvePercentage(QVariant value, int fullAmount)
{
    QString v = value.toString();
    if (v.contains("%"))
        return int(v.replace("%", "").toInt() / 100.0 * fullAmount);
    else
        return v.toInt();
}

static void setValueIfMissing(QSettings *s, QString key, QString value)
{
    if (!s->contains(key))
        s->setValue(key, value);
}

static int initInt(QSettings *s, QString key, QString value)
{
    setValueIfMissing(s, key, value);
    return s->value(key).toInt();
}

static QString initString(QSettings *s, QString key, QString value)
{
    setValueIfMissing(s, key, value);
    return s->value(key).toString();
}

static QColor initColor(QSettings *s, QString key, QString hexValue)
{
    setValueIfMissing(s, key, hexValue);
    return QColor(s->value(key).toString());
}

void initSettings(void)
{
    QSettings s;

    g.screenWidth = QGuiApplication::primaryScreen()->geometry().width();
    g.screenHeight = QGuiApplication::primaryScreen()->geometry().height();

    g.fontFamily = initString(&s, "core/font-family", "Sans");
    g.fontSize = initInt(&s, "core/font-size", "8");

    setValueIfMissing(&s, "panel/width", "100%");
    g.panelWidth = resolvePercentage(s.value("panel/width"), g.screenWidth);

    g.panelHeight = initInt(&s, "panel/height", "30");
    g.panelPaddingX = initInt(&s, "panel/padding-x", "2");
    g.panelPaddingY = initInt(&s, "panel/padding-y", "2");
    g.panelColorBackground =
            initColor(&s, "panel/color-background", "#ff111111");
    g.panelColorBorder = initColor(&s, "panel/color-border", "#00000000");

    g.taskWidth = initInt(&s, "task/width", "120");
    g.taskSpacing = initInt(&s, "task/spacing", "1");
    g.taskPaddingX = initInt(&s, "task/padding-x", "10");
    g.taskColorBackground = initColor(&s, "task/color-background", "#00000000");
    g.taskColorHoverBackground =
            initColor(&s, "task/color-hover-background", "#18aaaaaa");
    g.taskColorFont = initColor(&s, "task/color-font", "#ffeeeeee");

    //    qDebug() << "taskColorHoverBackground=" <<
    //    g.taskColorHoverBackground.name(QColor::HexArgb);
}

// vim: set ts=4 sw=4 et:
