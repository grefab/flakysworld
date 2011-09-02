#ifndef ACTUATORVIEW_H
#define ACTUATORVIEW_H

#include <QObject>
#include <QGraphicsPolygonItem>
#include <QString>
#include <QPointF>
#include <QList>

class ActuatorView : public QObject, public QGraphicsPolygonItem
{
	Q_OBJECT

public:
	explicit ActuatorView(QString id, QPointF position, QGraphicsItem *parent = 0);
	const QString& id() const { return id_; }

public slots:
	void actuatorUpdate(QList<qreal> actuatorNeurons);

protected:
	QString id_;

private:
	void setShape(qreal thrusterValue);
};

#endif // ACTUATORVIEW_H
