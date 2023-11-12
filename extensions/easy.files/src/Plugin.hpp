#pragma once

#include <QtQml/QQmlEngineExtensionPlugin>

namespace easy::files
{
	class Plugin: public QQmlEngineExtensionPlugin
	{
		Q_OBJECT
		Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)

	public:
		Plugin()
			: QQmlEngineExtensionPlugin{}
		{}
	};
}  // namespace easy::files
