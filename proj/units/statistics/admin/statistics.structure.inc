<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'statistics/admin/statistics.actions.inc';

	use Base\DB\MySQLi\Table;
	use Proj\Units\Consts;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class Statistics extends Actions\Statistics {
		private DBObject $db;

		protected Table $table_ip;
		protected Table $table_act;

		protected function __construct($file) {
			parent::__construct($file);
			$this->db = DBObject::instance();

			$this->table_ip = new Table(self::TABLES['ip'], $this->db, 'Статистика посещений');
			$this->table_ip->id('id', 'Идентификатор');
			$this->table_ip->timestamp('datecr', false, 'Дата создания');
			$this->table_ip->uint32('ip', 'IP адрес');
			$this->table_ip->uint32('cid', 'ID клиента');
			$this->table_ip->string('path', 255, 'Путь');
			$this->table_ip->string('params', 255, 'Параметры');
			$this->table_ip->AddForeign('foreign', ['cid'], Consts\Users::TABLES['clients'], ['id']);

			$this->table_act = new Table(self::TABLES['act'], $this->db, '');
			$this->table_act->id('id', 'Идентификатор');
			$this->table_act->timestamp('datecr', false, 'Дата создания');
			$this->table_act->uint32('cid', 'ID клиента');
			$this->table_act->string('object', 30, 'Объект');
			$this->table_act->string('action', 30, 'Действие');
			$this->table_act->string('params', 500, 'Параметры');
			$this->table_act->AddForeign('foreign', ['cid'], Consts\Users::TABLES['clients'], ['id']);

			$this->db->PushTables(
				$this->table_ip,
				$this->table_act
			);
		}

	}