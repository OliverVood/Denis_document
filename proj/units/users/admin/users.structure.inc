<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'users/admin/users.actions.inc';

	use Base\DB\MySQLi\Table;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class Users extends Actions\Users {
		private DBObject $db;

		protected Table $table_clients;
		protected Table $table_groups;
		protected Table $table_users;
		protected Table $table_access_groups;
		protected Table $table_access_users;

		protected function __construct($file) {
			parent::__construct($file);
			$this->db = DBObject::instance();

			$this->table_clients = new Table(self::TABLES['clients'], $this->db, 'Клиенты');
			$this->table_clients->id('id', 'Идентификатор');
			$this->table_clients->timestamp('datecr', false, 'Дата создания');
			$this->table_clients->timestamp('datemd', true, 'Дата изменения');
			$this->table_clients->string('hash', 64, 'Хэш');

			$this->table_groups = new Table(self::TABLES['groups'], $this->db, 'Группы');
			$this->table_groups->id('id', 'Идентификатор');
			$this->table_groups->uint8('state', 'Состояние');
			$this->table_groups->timestamp('datecr', false, 'Дата создания');
			$this->table_groups->timestamp('datemd', true, 'Дата изменения');
			$this->table_groups->string('name', 50, 'Наименование');

			$this->table_users = new Table(self::TABLES['users'], $this->db, 'Пользователи');
			$this->table_users->id('id', 'Идентификатор');
			$this->table_users->uint8('state', 'Состояние');
			$this->table_users->timestamp('datecr', false, 'Дата создания');
			$this->table_users->timestamp('datemd', true, 'Дата изменения');
			$this->table_users->uint32('gid', 'ID Группы');
			$this->table_users->string('login', 50, 'Логин');
			$this->table_users->string('password', 32, 'Пароль');
			$this->table_users->string('first_name', 50, 'Имя');
			$this->table_users->string('last_name', 50, 'Фамилия');
			$this->table_users->string('father_name', 50, 'Отчество');
			$this->table_users->AddForeign('foreign', ['gid'], self::TABLES['groups'], ['id']);

			$this->table_access_groups = new Table(self::TABLES['access_groups'], $this->db, 'Безопасность групп');
			$this->table_access_groups->uint32('gid', 'ID группы');
			$this->table_access_groups->uint16('collection', 'Коллекция');
			$this->table_access_groups->uint32('instance', 'Экземпляр ');
			$this->table_access_groups->uint16('right', 'Право');
			$this->table_access_groups->enum('permission', self::PERMISSIONS, 'Разрешение');

			$this->table_access_users = new Table(self::TABLES['access_users'], $this->db, 'Безопасность пользователей');
			$this->table_access_users->uint32('uid', 'ID пользователя');
			$this->table_access_users->uint16('collection', 'Экземпляр');
			$this->table_access_users->uint32('instance', 'Элемент');
			$this->table_access_users->uint16('right', 'Право');
			$this->table_access_users->enum('permission', self::PERMISSIONS, 'Разрешение');

			$this->db->PushTables(
				$this->table_clients,
				$this->table_groups,
				$this->table_users,
				$this->table_access_groups,
				$this->table_access_users
			);
		}

	}