<?php

	namespace Base\DB;

	require DIR_BASE . 'db/select.inc';

	interface Query {
		public static function select();
//		public static function insert();
//		public static function update();
//		public static function delete();

	}