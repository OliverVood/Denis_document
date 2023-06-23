<?php

	namespace Base\DB\MySQLi;

	require DIR_BASE . 'db/MySQLi/query/query.inc';
	require DIR_BASE . 'db/MySQLi/query/select.inc';

	class Query {
		public static function select(): \Base\DB\Select { return new \Base\DB\Select(); }
//		public static function insert(): Select { return new Insert(); }
//		public static function update(): Select { return new Update(); }
//		public static function delete(): Select { return new Delete(); }

	}