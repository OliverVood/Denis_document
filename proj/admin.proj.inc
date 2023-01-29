<?php

	require DIR_BASE . 'db\DBObject.inc';
	require DIR_BASE . 'db\table.inc';
	require DIR_BASE . 'db\field.inc';

	require DIR_BASE . 'db\MySQLi\DBMySQLi.inc';
	require DIR_BASE . 'db\MySQLi\DBObjectMySQLi.inc';
	require DIR_BASE . 'db\MySQLi\tableMySQLi.inc';
	require DIR_BASE . 'db\MySQLi\fieldMySQLi.inc';

	require 'DBObject.inc';

	require DIR_BASE . 'editor/editor.inc';
	require DIR_BASE . 'editor/editorMySQLi.inc';

	require DIR_BASE . 'html/elements.inc';

	require 'units/consts.inc';

	require 'units/admin.units.inc';

	require 'templates/admin/layout.inc';
	require 'templates/admin/index.tpl';