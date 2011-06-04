#include "variantbinaryconverter.h"

#include <QDebug>

VariantBinaryConverter::VariantBinaryConverter(QObject *parent) :
	QObject(parent)
{
}

QVariant VariantBinaryConverter::toVariant(const QByteArray& binaryData)
{
	/* perform some consistency checks first to ignore HTTP stuff. */
	if ( !looksLikeJSON(binaryData) ) {
		/* we have a problem. */
		qDebug() << "Error parsing raw data. Assumed JSON. Returning empty QVariant.";
		return QVariant();
	}

	/* convert JSON to something we can handle */
	bool ok;
	QVariant parsedData = parser_.parse(binaryData, &ok);

	if ( !ok ) {
		/* we have a problem. */
		qDebug() << "Error parsing data even though it looked like JSON. Returning empty QVariant.";
		return QVariant();
	}

	return parsedData;
}

QByteArray VariantBinaryConverter::toByteArray(const QVariant& variantData)
{
	/* perform serialization */
	return serializer_.serialize(variantData);
}

bool VariantBinaryConverter::looksLikeJSON(const QByteArray& data)
{
	/* no data? no json. */
	if ( data.size() <= 0 ) {
		return false;
	}

	/* let's hope there's nothing except json that is included in curly brackets. */
	if (data.at(0) != '{' || data.at(data.size()-1) != '}') {
		return false;
	}

	/* if we reach this point, it seems we have a JSON object. */
	return true;
}
