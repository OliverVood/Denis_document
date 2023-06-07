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
			$this->table_users->bool('fic');

			$this->db->PushTables($this->table_users);
		}

	}