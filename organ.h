#ifndef ORGAN_H
#define ORGAN_H

#include <QObject>
#include <QTransform>
#include "being.h"

class Organ : public QObject
{
	Q_OBJECT

public:
	explicit Organ(const Being& being, const QPointF position, qreal rotation, QString id = "", QObject *parent = 0);

	QString id() const;

	const QTransform& mapToWorld() const;

signals:
	void positionChanged(QTransform mapToWorld);

public slots:
	void setMapParentToWorld(const QTransform& mapParentToWorld);

protected:
	const Being& being_;

private:
	QString id_;

	QPointF position_;
	qreal rotation_;

	QTransform mapToParent_;
	QTransform mapParentToWorld_;
	void updateMapToWorld();
	QTransform mapToWorld_;

};

#endif // ORGAN_H
