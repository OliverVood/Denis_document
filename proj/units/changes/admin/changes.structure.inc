<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'changes/admin/changes.actions.inc';

	use Base\DB\MySQLi\Table;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class Changes extends Actions\Changes {
		private DBObject $db;

		protected Table $table_changes;
		protected Table $table_change;

		protected function __construct() {
			parent::__construct();
			$this->db = DBObject::instance();

			$this->table_changes = new Table(self::TABLES['changes'], $this->db);
			$this->table_changes->id('id');
			$this->table_changes->uint8('state');
			$this->table_changes->timestamp('datecr');
			$this->table_changes->timestamp('datemd', true);
			$this->table_changes->timestamp('datepb');
			$this->table_changes->string('work_header', 255);
			$this->table_changes->string('header', 255);

			$this->table_change = new Table(self::TABLES['change'], $this->db);
			$this->table_change->id('id');
			$this->table_change->uint32('cid');
			$this->table_change->uint8('state');
			$this->table_change->timestamp('datecr');
			$this->table_change->timestamp('datemd', true);
			$this->table_change->string('header', 255);
			$this->table_change->text('content');
			$this->table_change->string('hash', 32);
			$this->table_change->string('ext', 6);

			$this->db->PushTables($this->table_changes, $this->table_change);
		}

	}