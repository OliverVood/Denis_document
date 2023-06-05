<?php

	require DIR_BASE . 'db/DBObject.inc';
	require DIR_BASE . 'db/table.inc';
	require DIR_BASE . 'db/field.inc';

	require DIR_BASE . 'db/MySQLi/DBMySQLi.inc';
	require DIR_BASE . 'db/MySQLi/DBObjectMySQLi.inc';
	require DIR_BASE . 'db/MySQLi/MySQLiQuery.inc';
	require DIR_BASE . 'db/MySQLi/tableMySQLi.inc';
	require DIR_BASE . 'db/MySQLi/fieldMySQLi.inc';

	require DIR_PROJ . 'DBObject.inc';

	require DIR_BASE . 'pages.inc';
	require DIR_BASE . 'editor/editorMySQLi.html.inc';

	require DIR_BASE . 'html/elements.inc';

	require DIR_UNITS . 'consts.inc';

	require DIR_UNITS . 'admin.units.html.inc';

	\Proj\Admin\Units\HTML\Users::instance()->IsPossible();

	require DIR_PROJ . 'templates/admin/layout.inc';
	require DIR_PROJ . 'templates/admin/template.tpl';