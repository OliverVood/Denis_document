<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'statistics/admin/statistics.actions.inc';

	use Base\DB\TableMySQLi;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class Statistics extends Actions\Statistics {
		private DBObject $db;

		protected TableMySQLi $table_ip;
		protected TableMySQLi $table_act;

		protected function __construct() {
			parent::__construct();
			$this->db = DBObject::instance();

			$this->table_ip = new TableMySQLi(self::TABLES['ip'], $this->db);
			$this->table_ip->id('id');
			$this->table_ip->timestamp('datecr');
			$this->table_ip->uint32('ip');
			$this->table_ip->uint32('uid');
			$this->table_ip->string('path', 255);
			$this->table_ip->string('params', 255);

			$this->table_act = new TableMySQLi(self::TABLES['act'], $this->db);
			$this->table_act->id('id');
			$this->table_act->timestamp('datecr');
			$this->table_act->uint32('uid');
			$this->table_act->string('object', 30);
			$this->table_act->string('action', 30);
			$this->table_act->string('params', 500);

			$this->db->PushTables(
				$this->table_ip,
				$this->table_act
			);
		}

	}