<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'feedback/consts.inc';

	use Base\Units;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DBObject;

	class Feedback extends Units implements Consts\Feedback {
		private DBObject $db;

		protected TableMySQLi $table_feedback;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_feedback = new TableMySQLi(self::TABLES['feedback'], $this->db);
			$this->table_feedback->id('id');
			$this->table_feedback->uint8('state');
			$this->table_feedback->timestamp('datecr');
			$this->table_feedback->timestamp('datemd', true);
			$this->table_feedback->string('name', 255);
			$this->table_feedback->string('contacts', 255);
			$this->table_feedback->string('letter', 255);
			$this->table_feedback->text('content');

			$this->db->PushTables($this->table_feedback);
		}

	}