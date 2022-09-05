<?php

	require 'index.consts.inc';

	require DIR_BASE . 'base.inc';
	require DIR_PROJ . 'proj.inc';

	$db = Base\DB\MySQLi::Connect('localhost', 'admin', '123', 'documents');
	if (!$db->State()) die('MySQLi database connection error! Code: ' . $db->GetErrorCode());
//	$id = $db->Insert(['name' => 'fdf'], 'test');
	$id = $db->Update(['name' => 'WWW'], '`id` = 3', 'test');
	Debug($id);
//	Base\Units\Units::GetById(1)->test();