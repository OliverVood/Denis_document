<?php

	require 'index.consts.inc';

	require DIR_BASE . 'base.inc';
	require DIR_PROJ . 'proj.inc';

	$db = Base\DB\DBMySQLi::Connect('localhost', 'admin', '123', 'documents');
	if (!$db->State()) die('MySQLi database connection error! Code: ' . $db->GetErrorCode());
//	$id = $db->Insert('test', ['name' => 'fdf"/s\'dfd']);
//	$id = $db->Update('test', ['name' => 'asda"/s\'dfdsdasd'], '`id` = 4');
//	$result = $db->Select('test', ['id', 'name'], '`id` < 10', '`name` DESC', '3, 5', ['NOW() as `a`', 'NOW() as `b`']);
//	$response = $db->Fetch();
//	$response2 = $db->Fetch();
//	$response3 = $db->Fetch();
//	$response4 = $db->Fetch();
//	$response5 = $db->Fetch();
//	$response6 = $db->Fetch();
//	$response6 = $db->FetchAll();
//	Debug($id);
//	PROJ\Units\Users::instance()->test();
//	PROJ\Units\Users::instance()->test();
//	PROJ\Units\Catalogs::instance()->test();
//	Base\Units\Users::instance->test();
//Debug($result);
//Debug($response);
//Debug($response2);
//Debug($response3);
//Debug($response4);
//Debug($response5);
//$t = $db->GetQueryList();
//Debug($t);