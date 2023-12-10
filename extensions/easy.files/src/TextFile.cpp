#include "TextFile.hpp"

#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include "Path.hpp"

using namespace easy::files;

TextFile::TextFile(QObject * parent)
	: QObject{parent}
{
	_text.setBinding(
		[this]
		{
			QString result;
			if (auto path = _source.value().asString(); !path.isEmpty())
			{
				if (QFile file{path}; file.open(QFile::ReadOnly | QFile::Text))
				{
					QTextStream content{&file};
					result = content.readAll();
				}
			}
			return result;
		}
	);
}

Path TextFile::source() const
{
	return _source.value();
}

QBindable<Path> TextFile::bindableSource() const
{
	return &_source;
}

void TextFile::setSource(const Path & source)
{
	_source = source;
}

QString TextFile::text() const
{
	return _text.value();
}

QBindable<QString> TextFile::bindableText() const
{
	return &_text;
}
