#ifndef VARIANTBINARYCONVERTER_H
#define VARIANTBINARYCONVERTER_H

#include <QObject>
#include <QVariant>
#include <QByteArray>

#include "external/qjson/src/serializer.h"
#include "external/qjson/src/parser.h"

class VariantBinaryConverter : public QObject
{
	Q_OBJECT
public:
	explicit VariantBinaryConverter(QObject *parent = 0);

	QVariant toVariant(const QByteArray& binaryData);
	QByteArray toByteArray(const QVariant& variantData);

private:
	bool looksLikeJSON(const QByteArray& data);

};

#endif // VARIANTBINARYCONVERTER_H
