<?php

	namespace Base\DB;

	require DIR_BASE . 'db/MySQLi/query/query.inc';
	require DIR_BASE . 'db/MySQLi/query/select.inc';

	class MySQLiQuery {
		public static function select(): Select { return new Select(); }
//		public static function insert(): Select { return new Insert(); }
//		public static function update(): Select { return new Update(); }
//		public static function delete(): Select { return new Delete(); }

	}