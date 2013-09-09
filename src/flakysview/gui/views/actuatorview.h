#ifndef ACTUATORVIEW_H
#define ACTUATORVIEW_H

#include <QObject>
#include <QGraphicsPolygonItem>
#include <QString>
#include <QPointF>
#include <QList>
#include <QTimer>

class ActuatorView : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

public:
    explicit ActuatorView(QPointF position, QGraphicsItem *parent = 0);

public slots:
    void actuatorUpdate(QList<qreal> actuatorNeurons);

private slots:
    void timeout();

private:
    void setShape(qreal thrusterValue);

    QTimer fadeOutTimer_;
    qreal fadeOutThrusterValue_;

};

#endif // ACTUATORVIEW_H
