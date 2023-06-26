<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'users/admin/users.actions.inc';

	use Base\DB\MySQLi\Table;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class Users extends Actions\Users {
		private DBObject $db;

		protected Table $table_users;

		protected function __construct() {
			parent::__construct();
			$this->db = DBObject::instance();

			$this->table_users = new Table(self::TABLES['users'], $this->db);
			$this->table_users->id('id');
			$this->table_users->timestamp('datecr');
			$this->table_users->timestamp('datemd', true);
			$this->table_users->string('hash', 64);
			$this->table_users->bool('fic');

			$test = new Table('test', $this->db);
			$test->id('id');
			$test->string('str', 30);
			$test->uint32('uint16');
			$test->int32('int16');
			$test->uint16('uintq');
			$test->int16('intw');

			$test2 = new Table('test2', $this->db);
			$test2->id('id');
			$test2->uint8('uint8');
			$test2->string('str', 30);
			$test2->uint8('uint16');
			$test2->int32('int16');
			$test2->uint32('uintq');
			$test2->int16('intw');

			$test3 = new Table('test3', $this->db);
			$test3->id('id');
			$test3->bool('bool');
			$test3->int8('int8');
			$test3->int16('int16');
			$test3->int24('int24');
			$test3->int32('int32');
			$test3->int64('int64');
			$test3->uint8('uint8');
			$test3->uint16('uint16');
			$test3->uint24('uint24');
			$test3->uint32('uint32');
			$test3->uint64('uint64');
			$test3->float('float');
			$test3->double('double');
			$test3->timestamp('timestamp');
			$test3->timestamp('timestamp_update', true);
			$test3->enum('enum', ['a', 'b', 'c']);
			$test3->set('set', ['a', 'b', 'c']);
			$test3->string('string', 20);
			$test3->string('string_30', 20);
			$test3->text('text');

			$this->db->PushTables($this->table_users, $test, $test2, $test3);
		}

	}