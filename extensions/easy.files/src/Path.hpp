#pragma once

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtQml/QQmlEngine>

namespace easy::files
{
	class Path
	{
		Q_GADGET
		Q_PROPERTY(QString type READ type CONSTANT FINAL)

		Q_PROPERTY(bool isAbsolute READ isAbsolute FINAL)
		Q_PROPERTY(bool isDir READ isDir FINAL)
		Q_PROPERTY(bool isFile READ isFile FINAL)
		Q_PROPERTY(bool isLocal READ isLocal FINAL)
		Q_PROPERTY(bool isResource READ isResource FINAL)
		Q_PROPERTY(bool exists READ exists FINAL)

		Q_PROPERTY(QString asString READ asString FINAL)
		Q_PROPERTY(QUrl asUrl READ asUrl FINAL)

		Q_PROPERTY(Path parent READ parent FINAL)
		Q_PROPERTY(QString name READ name FINAL)
		Q_PROPERTY(QString bareStem READ bareStem FINAL)
		Q_PROPERTY(QString stem READ stem FINAL)
		Q_PROPERTY(QString suffix READ suffix FINAL)
		Q_PROPERTY(QList<QString> suffixes READ suffixes FINAL)

		QML_VALUE_TYPE(path)
		// QML_EXTENDED(easy::files::Path)
		QML_CONSTRUCTIBLE_VALUE

	public:
		Q_INVOKABLE Path(const QUrl & url = {});

		QString type() const;

		bool isLocal() const;
		bool isResource() const;
		bool isAbsolute() const;
		bool isDir() const;
		bool isFile() const;
		bool exists() const;

		QUrl asUrl() const;
		QString asString() const;

		Path parent() const;
		QString name() const;
		QString bareStem() const;
		QString stem() const;
		QString suffix() const;
		QList<QString> suffixes() const;

		Q_INVOKABLE QString toString() const;

	private:
		QUrl _url;
	};
}  // namespace easy::files
