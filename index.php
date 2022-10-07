<?php

	require 'index.consts.inc';

	require DIR_BASE . 'base.inc';
	require DIR_PROJ . 'proj.inc';

	use Base\DB;

	$db = DB\DBMySQLi::Connect('localhost', 'admin', '123', 'documents');
	if (!$db->State()) die('MySQLi database connection error! Code: ' . $db->GetErrorCode());
	$table = new DB\TableMySQLi('test2', $db);
	$table->id('id');
	$table->bool('bool');
	$table->int8('int8');
	$table->int16('int16');
	$table->int24('int24');
	$table->int32('int32');
	$table->int64('int64');
	$table->uint8('uint8');
	$table->uint16('uint16');
	$table->uint24('uint24');
	$table->uint32('uint32');
	$table->uint64('uint64');
	$table->float('float');
	$table->double('double');
	$table->timestamp('tsupd', true);
	$table->timestamp('ts');
	$table->enum('enum', ['one', 'two', 'three']);
	$table->set('set', ['one', 'two', 'three']);
	$table->string('str10', 10);
	$table->string('str50', 50);
	$table->text('text');

//	$table2 = new DB\TableMySQLi('test3', $db);
//	$table2->id('id');
//	$table2->bool('bool');
//	$table2->int8('int8');
//	$table2->int16('int16');
//	$table2->int24('int24');
//	$table2->int32('int32');
//	$table2->int64('int64');
//	$table2->uint8('uint8');
//	$table2->uint16('uint16');
//	$table2->uint24('uint24');
//	$table2->uint32('uint32');
//	$table2->uint64('uint64');
//	$table2->float('float');
//	$table2->double('double');

	$db->PushTables(/*$table, */$table);
//	$db->Check();
//	$db->Make();
//	$res = $db->Query("SHOW CREATE TABLE `test2`");
//	Debug($db->FetchAll($res));
//	PROJ\Units\Users::instance()->test();
//	PROJ\Units\Users::instance()->test();
//	PROJ\Units\Catalogs::instance()->test();
//	Base\Units\Users::instance->test();