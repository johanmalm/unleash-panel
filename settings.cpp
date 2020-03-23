#include "settings.h"

#include <QSettings>
#include <QString>
#include <QVariant>
#include <QScreen>
#include <QGuiApplication>

Globals g;

static int resolvePercentage(QVariant value, int fullAmount)
{
    QString v = value.toString();
    if (v.contains("%"))
        return  int(v.replace("%", "").toInt() / 100.0 * fullAmount);
    else
        return v.toInt();
}

void setValueIfMissing(QSettings *s, QString key, QString value)
{
    if (!s->contains(key))
        s->setValue(key, value);
}

void initSettings(void)
{
    QSettings s;

    g.screenWidth = QGuiApplication::primaryScreen()->geometry().width();
    g.screenHeight = QGuiApplication::primaryScreen()->geometry().height();

    setValueIfMissing(&s, "panel/width", "100%");
    g.panelWidth = resolvePercentage(s.value("panel/width"), g.screenWidth);

    setValueIfMissing(&s, "panel/height", "30");
    g.panelHeight = s.value("panel/height").toInt();

    setValueIfMissing(&s, "panel/padding-x", "2");
    g.panelPaddingX = s.value("panel/padding-x").toInt();

    setValueIfMissing(&s, "panel/padding-y", "2");
    g.panelPaddingY = s.value("panel/padding-y").toInt();

    setValueIfMissing(&s, "task/width", "120");
    g.taskWidth = s.value("task/width").toInt();

    setValueIfMissing(&s, "task/spacing", "1");
    g.taskSpacing = s.value("task/spacing").toInt();

    if (!s.contains("task/color-fill"))
        s.setValue("task/color-fill", QColor(255, 200, 100, 200));
    g.taskColorFill = s.value("task/color-fill").value<QColor>();
}

// vim: set ts=4 sw=4 et:
