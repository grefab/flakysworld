#ifndef THING_H
#define THING_H

#include <QObject>
#include <QPointF>
#include <QTransform>

class Thing : public QObject
{
	Q_OBJECT

public:
	explicit Thing(QPointF position, qreal rotation, QObject *parent = 0);

	void setId(QString newId) { id_ = newId; };
	const QString& id() const { return id_; };

	const QPointF& position() const { return position_; };
	const qreal& rotation() const { return rotation_; };

	const QTransform& getWorldMap() const { return mapToWorld_; }

protected:
	void update(QPointF position, qreal rotation);

private:
	QString id_;

	QPointF position_;
	qreal rotation_;

	void updateMapToWorld();
	QTransform mapToWorld_;

};

#endif // THING_H
