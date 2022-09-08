<?php

	require 'index.consts.inc';

	require DIR_BASE . 'base.inc';
	require DIR_PROJ . 'proj.inc';

	$db = Base\DB\MySQLi::Connect('localhost', 'admin', '123', 'documents');
	if (!$db->State()) die('MySQLi database connection error! Code: ' . $db->GetErrorCode());
//	$id = $db->Insert('test', ['name' => 'fdf']);
//	$id = $db->Update('test', ['name' => 'sdsd'], '`id` = 3');
//	Debug($id);
//	PROJ\Units\Users::instance()->test();
	PROJ\Units\Users::instance()->test();
	PROJ\Units\Catalogs::instance()->test();
//	Base\Units\Users::instance->test();