#include "Path.hpp"

#include <QtCore/QFileInfo>

using namespace easy::files;

namespace easy::files::details
{
	QString urlToPath(const QUrl & url)
	{
		if (url.scheme() == "qrc")
			return url.path().prepend(":");
		else if (url.isLocalFile())
			return url.toLocalFile();
		else
			return url.toString();
	}

	QString fileName(const QUrl & url)
	{
		auto path = url.path();
		if (path.endsWith("/"))
			path.chop(1);

		return QFileInfo{path}.fileName();
	}

	QList<QString> fileNameParts(const QString & fileName)
	{
		auto parts = fileName.split(".");
		if (parts.first() == "")
			parts.removeFirst();
		return parts;
	}

	int countLeadingDots(const QString & str)
	{
		int leadingDots = 0;
		for (const auto & ch: str)
			if (ch == '.')
				leadingDots++;
			else
				break;
		return leadingDots;
	}

	int countTrailingDots(const QString & str)
	{
		int trailingDots = 0;
		for (auto it = str.crbegin(); it != str.crend(); it++)
			if (*it == '.')
				trailingDots++;
			else
				break;
		return trailingDots;
	}
}  // namespace easy::files::details

Path::Path(const QUrl & url)
	: _url{url}
{}

QString Path::type() const
{
	return "easy.files.path";
}

bool Path::isLocal() const
{
	return _url.isLocalFile();
}

bool Path::isResource() const
{
	return _url.scheme() == "qrc";
}

bool Path::isAbsolute() const
{
	const auto path = details::urlToPath(_url);
	return QFileInfo{path}.isAbsolute();
}

bool Path::isDir() const
{
	const auto path = details::urlToPath(_url);
	qDebug() << path;
	return QFileInfo{path}.isDir();
}

bool Path::isFile() const
{
	const auto path = details::urlToPath(_url);
	return QFileInfo{path}.isFile();
}

bool Path::exists() const
{
	const auto path = details::urlToPath(_url);
	return QFileInfo{path}.exists();
}

QString Path::toString() const
{
	return _url.toString();
}

QString Path::asString() const
{
	return details::urlToPath(_url);
}

QUrl Path::asUrl() const
{
	return _url;
}

Path Path::parent() const
{
	auto path = _url.path();
	if (path.endsWith("/"))
		path.chop(1);

	QUrl newUrl = _url;
	newUrl.setPath(QFileInfo{path}.path());
	return Path{newUrl};
}

QString Path::name() const
{
	return details::fileName(_url);
}

QString Path::bareStem() const
{
	using namespace Qt::Literals;

	auto fileName = details::fileName(_url);

	if (fileName.endsWith('.'))
	{
		return fileName;
	}
	else
	{
		int theDot = fileName.indexOf('.', details::countLeadingDots(fileName));
		return theDot != -1 ? fileName.first(theDot) : fileName;
	}
}

QString Path::stem() const
{
	auto fileName = details::fileName(_url);

	if (fileName.endsWith('.'))
	{
		return fileName;
	}
	else
	{
		int leadingDots = details::countLeadingDots(fileName);
		int theDot = fileName.sliced(leadingDots).lastIndexOf('.');
		return theDot != -1 ? fileName.first(leadingDots + theDot) : fileName;
	}
}

QString Path::suffix() const
{
	return details::fileName(_url).sliced(stem().size());
}

QList<QString> Path::suffixes() const
{
	auto fileName = details::fileName(_url);
	const auto bStem = bareStem();

	Q_ASSERT(fileName.startsWith(bStem));
	Q_ASSERT(fileName.size() >= bStem.size());

	if (bStem.size() >= fileName.size())
		return {};

	fileName = fileName.sliced(bStem.size() + 1);

	auto parts = fileName.split('.');
	for (auto & part: parts)
		part.prepend(".");

	return parts;
}
