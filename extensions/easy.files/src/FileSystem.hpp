#pragma once

#include <QtCore/QObject>
#include <QtQml/QQmlEngine>

#include "Path.hpp"

namespace easy::files
{
	class FileSystem: public QObject
	{
		Q_OBJECT
		QML_SINGLETON
		QML_NAMED_ELEMENT(File)

	public:
		explicit FileSystem(QObject * parent = nullptr);
		~FileSystem() = default;

	public:
		Q_INVOKABLE bool create(const Path & path, const QString & initialText = "") const;
		Q_INVOKABLE bool isEmpty(const Path & path) const;
	};
}  // namespace easy::files
