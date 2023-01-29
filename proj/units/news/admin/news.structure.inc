<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'news/const.inc';

	use Base\Units;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DBObject;


	class News extends Units implements Consts\News {
		private DBObject $db;

		protected TableMySQLi $table_news;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBObject::instance();

			$this->table_news = new TableMySQLi(self::TABLES['news'], $this->db);
			$this->table_news->id('id');
			$this->table_news->uint8('state');
			$this->table_news->timestamp('datecr');
			$this->table_news->timestamp('datemd', true);
			$this->table_news->string('header', 255);
			$this->table_news->text('content');
			$this->table_news->string('cover', 30);

			$this->db->PushTables($this->table_news);
		}

	}