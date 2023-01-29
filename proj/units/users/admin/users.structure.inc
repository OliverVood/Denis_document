<?php

	namespace Proj\Site\Structure;

	require DIR_UNITS . 'users/consts.inc';

	use Base\Units;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class Users extends Units implements Consts\Users {
		private DBObject $db;

		protected TableMySQLi $table_users;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_users = new TableMySQLi(self::TABLES['users'], $this->db);
			$this->table_users->id('id');
			$this->table_users->timestamp('datecr');
			$this->table_users->timestamp('datemd', true);
			$this->table_users->bool('fic');

			$this->db->PushTables($this->table_users);
		}

	}