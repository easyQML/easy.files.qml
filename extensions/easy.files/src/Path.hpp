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
		Q_PROPERTY(bool isAlias READ isAlias FINAL)
		Q_PROPERTY(bool isBundle READ isBundle FINAL)
		Q_PROPERTY(bool isDir READ isDir FINAL)
		Q_PROPERTY(bool isExecutable READ isExecutable FINAL)
		Q_PROPERTY(bool isFile READ isFile FINAL)
		Q_PROPERTY(bool isHidden READ isHidden FINAL)
		Q_PROPERTY(bool isJunction READ isJunction FINAL)
		Q_PROPERTY(bool isLink READ isLink FINAL)
		Q_PROPERTY(bool isLocal READ isLocal FINAL)
		Q_PROPERTY(bool isNative READ isNative FINAL)
		Q_PROPERTY(bool isReadable READ isReadable FINAL)
		Q_PROPERTY(bool isRelative READ isRelative FINAL)
		Q_PROPERTY(bool isResource READ isResource FINAL)
		Q_PROPERTY(bool isRoot READ isRoot FINAL)
		Q_PROPERTY(bool isShortcut READ isShortcut FINAL)
		Q_PROPERTY(bool isSymbolicLink READ isSymbolicLink FINAL)
		Q_PROPERTY(bool isWritable READ isWritable FINAL)
		Q_PROPERTY(bool exists READ exists FINAL)
		Q_PROPERTY(bool valid READ valid FINAL)

		Q_PROPERTY(QString asString READ asString FINAL)
		Q_PROPERTY(QUrl asUrl READ asUrl FINAL)

		Q_PROPERTY(easy::files::Path parent READ parent FINAL)
		Q_PROPERTY(QString name READ name FINAL)
		Q_PROPERTY(QString bareStem READ bareStem FINAL)
		Q_PROPERTY(QString stem READ stem FINAL)
		Q_PROPERTY(QString suffix READ suffix FINAL)
		Q_PROPERTY(QList<QString> suffixes READ suffixes FINAL)

		Q_PROPERTY(QString scheme READ scheme WRITE setScheme FINAL)
		Q_PROPERTY(QString user READ user WRITE setUser FINAL)
		Q_PROPERTY(QString password READ password WRITE setPassword FINAL)
		Q_PROPERTY(QString host READ host WRITE setHost FINAL)
		Q_PROPERTY(int port READ port WRITE setPort FINAL)
		Q_PROPERTY(QString path READ path WRITE setPath FINAL)
		Q_PROPERTY(QString query READ query WRITE setQuery FINAL)
		Q_PROPERTY(QString fragment READ fragment WRITE setFragment FINAL)

		QML_VALUE_TYPE(path)
		// QML_EXTENDED(easy::files::Path)
		QML_CONSTRUCTIBLE_VALUE

	public:
		Q_INVOKABLE Path(const QUrl & url = {});

		QString type() const;

		bool isAbsolute() const;
		bool isAlias() const;
		bool isBundle() const;
		bool isDir() const;
		bool isExecutable() const;
		bool isFile() const;
		bool isHidden() const;
		bool isJunction() const;
		bool isLink() const;
		bool isLocal() const;
		bool isNative() const;
		bool isReadable() const;
		bool isRelative() const;
		bool isResource() const;
		bool isRoot() const;
		bool isShortcut() const;
		bool isSymbolicLink() const;
		bool isWritable() const;

		bool exists() const;
		bool valid() const;

		QUrl asUrl() const;
		QString asString() const;

		Path parent() const;
		QString name() const;
		QString bareStem() const;
		QString stem() const;
		QString suffix() const;
		QList<QString> suffixes() const;

		Q_INVOKABLE QString toString() const;

		QString scheme() const;
		void setScheme(const QString & scheme);

		QString user() const;
		void setUser(const QString & user);

		QString password() const;
		void setPassword(const QString & password);

		QString host() const;
		void setHost(const QString & host);

		int port() const;
		void setPort(const int & port);

		QString path() const;
		void setPath(const QString & path);

		QString query() const;
		void setQuery(const QString & query);

		QString fragment() const;
		void setFragment(const QString & fragment);

	private:
		QUrl _url;
	};
}  // namespace easy::files
