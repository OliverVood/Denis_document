<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'users/admin/users.actions.inc';

	use Base\DB\MySQLi\Table;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class Users extends Actions\Users {
		private DBObject $db;

		protected Table $table_users;

		protected function __construct($file) {
			parent::__construct($file);
			$this->db = DBObject::instance();

			$this->table_users = new Table(self::TABLES['users'], $this->db, 'Пользователи');
			$this->table_users->id('id', 'Идентификатор');
			$this->table_users->timestamp('datecr', false, 'Дата создания');
			$this->table_users->timestamp('datemd', true, 'Дата изменения');
			$this->table_users->string('hash', 64, 'Хэш');
			$this->table_users->bool('fic', 'Фиктивность');

			$this->db->PushTables($this->table_users);
		}

	}