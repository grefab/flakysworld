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
	struct Model
	{
	public:
		explicit Model(QPolygonF shape, QPointF position, qreal rotation, QString id = "");

		QString id_;

		QPolygonF shape_;
		QPointF position_;
		qreal rotation_;
	};


	explicit Thing(QPolygonF shape, QPointF position, qreal rotation, QString id = "", QObject *parent = 0);
	explicit Thing(const Model model, QObject *parent = 0);

	/* getter */
	const QString& id() const { return model_.id_; }

	const QPolygonF& shape() const { return model_.shape_; }
	const QPointF& position() const { return model_.position_; }
	const qreal& rotation() const { return model_.rotation_; }

	const Model& getModel() const { return model_; }

	const QTransform& getWorldMap() const { return mapToWorld_; }

	/* setter */
	void setPosRot(const QPointF& position, qreal rotation);
	void setPosition(const QPointF& position);
	void setRotation(qreal rotation);

signals:
	/* a view can connect to this to take care for updates */
	void changedPosition(QTransform transformation) const;
	void updated(QPointF position, qreal rotation) const;

private:
	Model model_;

	void update();
	void updateMapToWorld();
	QTransform mapToWorld_;

};

#endif // THING_H
