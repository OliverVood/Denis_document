<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'news/admin/news.actions.inc';

	use Base\DB\TableMySQLi;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class News extends Actions\News {
		private DBObject $db;

		protected TableMySQLi $table_news;

		protected function __construct() {
			parent::__construct();
			$this->db = DBObject::instance();

			$this->table_news = new TableMySQLi(self::TABLES['news'], $this->db);
			$this->table_news->id('id');
			$this->table_news->uint8('state');
			$this->table_news->timestamp('datecr');
			$this->table_news->timestamp('datemd', true);
			$this->table_news->timestamp('datepb');
			$this->table_news->string('header', 255);
			$this->table_news->text('content');
			$this->table_news->string('hash', 32);
			$this->table_news->string('ext', 6);

			$this->db->PushTables($this->table_news);
		}

	}