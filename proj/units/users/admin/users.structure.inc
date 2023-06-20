<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'users/admin/users.actions.inc';

	use Base\DB\TableMySQLi;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class Users extends Actions\Users {
		private DBObject $db;

		protected TableMySQLi $table_users;

		protected function __construct() {
			parent::__construct();
			$this->db = DBObject::instance();

			$this->table_users = new TableMySQLi(self::TABLES['users'], $this->db);
			$this->table_users->id('id');
			$this->table_users->timestamp('datecr');
			$this->table_users->timestamp('datemd', true);
			$this->table_users->string('hash', 64);
			$this->table_users->bool('fic');

			$test = new TableMySQLi('test', $this->db);
			$test->id('id');
			$test->string('str', 30);
			$test->uint32('uint16');
			$test->int32('int16');
			$test->uint32('uintq');
			$test->int16('intw');

			$test2 = new TableMySQLi('test2', $this->db);
			$test2->id('id');
			$test2->string('str', 30);
			$test2->uint32('uint16');
			$test2->int32('int16');
			$test2->uint32('uintq');
			$test2->int16('intw');

			$this->db->PushTables($this->table_users, $test);
		}

	}