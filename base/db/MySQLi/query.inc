<?php

	namespace Base\DB\MySQLi;

	require DIR_BASE . 'db/MySQLi/select.inc';

	class Query implements \Base\DB\Query {
		public static function select(): Select { return new Select(); }
//		public static function insert(): Select { return new Insert(); }
//		public static function update(): Select { return new Update(); }
//		public static function delete(): Select { return new Delete(); }

	}