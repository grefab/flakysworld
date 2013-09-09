#include "thingview.h"
#include <QBrush>
#include <QPen>

ThingView::ThingView(const Thing& thing, QGraphicsItem *parent) :
        QGraphicsPolygonItem(parent)
{
    /* colorize! */
    setAppearanceDependingOnID(thing.id());

    /* we need the body only to connect to it. no reference is stored. */
    connect(&thing, SIGNAL(changedPosition(QTransform)), this, SLOT(bodyChanged(QTransform)));

    /* initially set our location parameters */
    bodyChanged(thing.getWorldMap());

    /* adept our model's shape */
    setPolygon(thing.shape());
}

void ThingView::bodyChanged(QTransform transformation)
{
    /* mirroring on the x axis to take care for Qt's screen coordinates. */
    static const QTransform mirror(1, 0, 0, 0, -1, 0, 0, 0, 1);

    setTransform(transformation * mirror);
}

void ThingView::setAppearanceDependingOnID(QString id)
{
    QColor color = Qt::black;

    if ( id == "flaky") {
        color = QColor("#FF8000");
    } else {
        /* random color
        color = QColor(128 + qrand() % 128, 128 + qrand() % 128, 128 + qrand() % 128);
        */
    }

    setBrush(color);
    setPen(QPen(Qt::NoPen));
}
