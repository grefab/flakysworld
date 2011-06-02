#ifndef THING_H
#define THING_H

#include <QObject>
#include <QPointF>
#include <QPolygonF>
#include <QTransform>
#include <QVariant>

class Thing : public QObject
{
	Q_OBJECT

public:
	explicit Thing(QPolygonF shape, QPointF position, qreal rotation, QString id = "", QObject *parent = 0);

	/* getter */
	const QString& id() const { return id_; }

	const QPolygonF& shape() const { return shape_; }
	const QPointF& position() const { return position_; }
	const qreal& rotation() const { return rotation_; }

	const QTransform& getWorldMap() const { return mapToWorld_; }

	/* serializer */
	QVariantMap getSerialized(bool onlyUpdate = false);
	void fromVariant(QVariant serialized);

protected:
	void setPosRot(const QPointF& position, qreal rotation);
	void setPosition(const QPointF& position);
	void setRotation(qreal rotation);

signals:
	/* a view can connect to this to take care for updates */
	void changedPosition(QTransform transformation) const;
	void changedPosition(QPointF position, qreal rotation) const;

private:
	QString id_;

	QPolygonF shape_;
	QPointF position_;
	qreal rotation_;

	void update();
	void updateMapToWorld();
	QTransform mapToWorld_;

};

#endif // THING_H
