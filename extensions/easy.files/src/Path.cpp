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

	QStringList fileNameParts(const QString & fileName)
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

QStringList Path::parts() const
{
	auto path = _url.path();
	if (path.endsWith("/"))
		path.chop(1);

	QStringList result;
	result << _url.adjusted(QUrl::RemovePath | QUrl::RemoveQuery | QUrl::RemoveFragment | QUrl::StripTrailingSlash)
				  .toString();

	auto s = path.split('/');
	if (s.first().isEmpty())
		s.removeFirst();
	result += s;

	if (_url.hasQuery())
		result << _url.query();

	if (_url.hasFragment())
		result << _url.fragment();

	return result;
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

QStringList Path::suffixes() const
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

QDateTime Path::born() const
{
	const auto path = details::urlToPath(_url);
	return QFileInfo{path}.birthTime();
}

QDateTime Path::lastModified() const
{
	const auto path = details::urlToPath(_url);
	return QFileInfo{path}.lastModified();
}

QDateTime Path::lastRead() const
{
	const auto path = details::urlToPath(_url);
	return QFileInfo{path}.lastRead();
}

QDateTime Path::metadataModified() const
{
	const auto path = details::urlToPath(_url);
	return QFileInfo{path}.metadataChangeTime();
}

Owner Path::group() const
{
	const auto path = details::urlToPath(_url);
	QFileInfo fi{path};
	return Owner{fi.group(), fi.groupId()};
}

Owner Path::owner() const
{
	const auto path = details::urlToPath(_url);
	QFileInfo fi{path};
	return Owner{fi.owner(), fi.ownerId()};
}

Path Path::absolute() const
{
	auto path = _url.isLocalFile() ? _url.toLocalFile() : _url.path();
	if (_url.scheme() == "qrc")
		path.prepend(':');

	QUrl newUrl = _url;
	auto absPath = QFileInfo{path}.absoluteFilePath();
	if (_url.scheme() == "qrc")
		absPath.removeFirst();
	newUrl.setPath(absPath);
	return Path{newUrl};
}

Path Path::normalized() const
{
	return Path{_url.adjusted(QUrl::NormalizePathSegments | QUrl::PreferLocalFile)};
}

Path Path::linkTarget() const
{
	const auto path = details::urlToPath(_url);
	QFileInfo fi{path};

	QUrl newUrl = _url;
	if (fi.isJunction())
		newUrl.setPath(fi.junctionTarget());
	else if (fi.isSymbolicLink())
		newUrl.setPath(fi.symLinkTarget());
	else
		newUrl = QUrl{};

	return Path{newUrl};
}

Path Path::join(const QString & rhs) const
{
	const auto str = toString();
	if (str == "/")
		return Path{QUrl{str + rhs}};
	else
		return Path{QUrl{str + '/' + rhs}};
}

Path Path::join(const QStringList & rhs) const
{
	return join(rhs.join('/'));
}

Path Path::withName(const QString & name) const
{
	return parent().join(name);
}

Path Path::withStem(const QString & stem) const
{
	return parent().join(stem + suffix());
}

Path Path::withBareStem(const QString & bareStem) const
{
	return parent().join(bareStem + suffixes().join(""));
}

Path Path::withSuffix(const QString & suffix) const
{
	return parent().join(stem() + suffix);
}
