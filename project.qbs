Project {
	name: 'easy.files'

	minimumQbsVersion: '2.0.0'
	qbsSearchPaths: [
		'3rdparty/easy.qmldir.qbs',
		'qbs',
	]

	references: [
		'extensions/extensions.qbs',
	]
}
