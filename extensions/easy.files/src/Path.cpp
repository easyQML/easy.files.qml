#include "Path.hpp"

#include <QtCore/QFileInfo>

using namespace easy::files;

namespace easy::files::details
{
	QString urlToPath(const QUrl & url)
	{
		if (url.scheme() == "qrc")
			return url.path().prepend(':');
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
	return valid() && (_url.isLocalFile() || _url.scheme().isEmpty());
}

bool Path::isResource() const
{
	return valid() && _url.scheme() == "qrc";
}

bool Path::isAbsolute() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isAbsolute();
}

bool Path::isAlias() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isAlias();
}

bool Path::isBundle() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isBundle();
}

bool Path::isDir() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isDir();
}

bool Path::isExecutable() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isExecutable();
}

bool Path::isFile() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isFile();
}

bool Path::isHidden() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isHidden();
}

bool Path::isJunction() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isJunction();
}

bool Path::isLink() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isSymLink();
}

bool Path::isNative() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isNativePath();
}

bool Path::isReadable() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isReadable();
}

bool Path::isRelative() const
{
	return valid() && !isAbsolute();
}

bool Path::isRoot() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isRoot();
}

bool Path::isShortcut() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isShortcut();
}

bool Path::isSymbolicLink() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isSymbolicLink();
}

bool Path::isWritable() const
{
	const auto path = details::urlToPath(_url);
	return valid() && QFileInfo{path}.isWritable();
}

bool Path::exists() const
{
	const auto path = details::urlToPath(_url);
	return QFileInfo{path}.exists();
}

bool Path::valid() const
{
	return _url.isValid();
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

	const auto fileName = details::fileName(_url);

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
	const auto fileName = details::fileName(_url);

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

QString Path::scheme() const
{
	return _url.scheme();
}

void Path::setScheme(const QString & scheme)
{
	_url.setScheme(scheme);
}

QString Path::user() const
{
	return _url.userName();
}

void Path::setUser(const QString & user)
{
	_url.setUserName(user);
}

QString Path::password() const
{
	return _url.password();
}

void Path::setPassword(const QString & password)
{
	_url.setPassword(password);
}

QString Path::host() const
{
	return _url.host();
}

void Path::setHost(const QString & host)
{
	_url.setHost(host);
}

int Path::port() const
{
	return _url.port();
}

void Path::setPort(const int & port)
{
	if (port >= -1 && port <= 65535)
	{
		_url.setPort(port);
	}
}

QString Path::path() const
{
	return _url.path();
}

void Path::setPath(const QString & path)
{
	_url.setPath(path);
}

QString Path::query() const
{
	return _url.query();
}

void Path::setQuery(const QString & query)
{
	_url.setQuery(query);
}

QString Path::fragment() const
{
	return _url.fragment();
}

void Path::setFragment(const QString & fragment)
{
	_url.setFragment(fragment);
}
