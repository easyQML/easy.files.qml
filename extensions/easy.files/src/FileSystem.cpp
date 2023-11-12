#include "FileSystem.hpp"

#include <QtCore/QDir>

using namespace easy::files;

FileSystem::FileSystem(QObject * parent)
	: QObject{parent}
{}

bool FileSystem::create(const Path & path, const QString & initialText) const
{
	if (path.exists())
		return true;

	if (!path.isLocal())
		return false;

	if (QDir dir; !dir.mkpath(path.parent().asString())) [[unlikely]]
		return false;

	QFile file{path.asString()};
	bool opened = file.open(QIODevice::WriteOnly | QIODevice::Text);
	if (opened) [[likely]]
	{
		QTextStream out{&file};
		out << initialText;
		file.close();
	}
	return opened;
}

bool FileSystem::isEmpty(const Path & path) const
{
	return path.size() == 0;
}
