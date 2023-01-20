<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'statistics/consts.inc';

	use Base\Units;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DB;

	class Statistics extends Units implements Consts\Statistics {
		private DB $db;

		protected TableMySQLi $table_ip;
		protected TableMySQLi $table_act;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DB::instance();

			$this->table_ip = new TableMySQLi(self::TABLES['ip'], $this->db);
			$this->table_ip->id('id');
			$this->table_ip->timestamp('datecr');
			$this->table_ip->uint32('uid');
			$this->table_ip->uint8('ip_part_I');
			$this->table_ip->uint8('ip_part_II');
			$this->table_ip->uint8('ip_part_III');
			$this->table_ip->uint8('ip_part_IV');
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