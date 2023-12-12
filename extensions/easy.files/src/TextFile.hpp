#pragma once

#include <QtCore/QObject>
#include <QtCore/QProperty>
#include <QtCore/QString>
#include <QtQml/QQmlEngine>

#include "Path.hpp"

namespace easy::files
{
	class TextFile: public QObject
	{
		Q_OBJECT
		QML_NAMED_ELEMENT(TextFile)
		Q_PROPERTY(easy::files::Path source READ source WRITE setSource BINDABLE bindableSource)
		Q_PROPERTY(QString text READ text BINDABLE bindableText)

	public:
		explicit TextFile(QObject * parent = nullptr);
		~TextFile() override = default;

	public:
		QString text() const;
		QBindable<QString> bindableText() const;

		easy::files::Path source() const;
		Q_INVOKABLE void setSource(const easy::files::Path & source);
		QBindable<easy::files::Path> bindableSource();

	signals:
		void sourceChanged(const easy::files::Path & source);
		void textChanged(const QString & text);

	private:
		Q_OBJECT_BINDABLE_PROPERTY(TextFile, easy::files::Path, _source, &TextFile::sourceChanged);
		Q_OBJECT_BINDABLE_PROPERTY(TextFile, QString, _text, &TextFile::textChanged);
	};
}  // namespace easy::files
