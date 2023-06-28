<?php

	require DIR_BASE . 'db/DBObject.inc';
	require DIR_BASE . 'db/table.inc';
	require DIR_BASE . 'db/field.inc';
	require DIR_BASE . 'db/query.inc';

	require DIR_BASE . 'db/MySQLi/DB.inc';
	require DIR_BASE . 'db/MySQLi/DBObject.inc';
	require DIR_BASE . 'db/MySQLi/table.inc';
	require DIR_BASE . 'db/MySQLi/field.inc';
	require DIR_BASE . 'db/MySQLi/key.inc';
	require DIR_BASE . 'db/MySQLi/query.inc';

	require DIR_PROJ . 'DBObject.inc';

	require DIR_BASE . 'pages.inc';
	require DIR_BASE . 'editor/MySQLi/editor.html.inc';

	require DIR_BASE . 'html/elements.inc';

	require DIR_UNITS . 'consts.inc';

	require DIR_UNITS . 'admin.units.html.inc';

	\Proj\Admin\Units\HTML\Users::instance()->IsPossible();

	require DIR_PROJ . 'templates/admin/layout.inc';
	require DIR_PROJ . 'templates/admin/template.tpl';