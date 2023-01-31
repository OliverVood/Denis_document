<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'opportunities/consts.inc';

	use Base\Units;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class Opportunities extends Units implements Consts\Opportunities {
		private DBObject $db;

		protected TableMySQLi $table_opportunities;
		protected TableMySQLi $table_opportunity;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_opportunities = new TableMySQLi(self::TABLES['opportunities'], $this->db);
			$this->table_opportunities->id('id');
			$this->table_opportunities->uint8('state');
			$this->table_opportunities->timestamp('datecr');
			$this->table_opportunities->timestamp('datemd', true);
			$this->table_opportunities->string('header', 255);

			$this->table_opportunity = new TableMySQLi(self::TABLES['opportunity'], $this->db);
			$this->table_opportunity->id('id');
			$this->table_opportunity->uint8('state');
			$this->table_opportunity->timestamp('datecr');
			$this->table_opportunity->timestamp('datemd', true);
			$this->table_opportunity->string('header', 255);
			$this->table_opportunity->text('content');
			$this->table_opportunity->string('cover', 30);

			$this->db->PushTables($this->table_opportunities, $this->table_opportunity);
		}

	}