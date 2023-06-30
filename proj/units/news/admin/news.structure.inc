<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'news/admin/news.actions.inc';

	use Base\DB\MySQLi\Table;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class News extends Actions\News {
		private DBObject $db;

		protected Table $table_news;

		protected function __construct() {
			parent::__construct();
			$this->db = DBObject::instance();

			$this->table_news = new Table(self::TABLES['news'], $this->db, 'Новости');
			$this->table_news->id('id', 'Идентификатор');
			$this->table_news->uint8('state', 'Состояние');
			$this->table_news->timestamp('datecr', false, 'Дата создания');
			$this->table_news->timestamp('datemd', true, 'Дата изменения');
			$this->table_news->timestamp('datepb', false, 'Дата публикации');
			$this->table_news->string('header', 255, 'Заголовок');
			$this->table_news->text('content', 'Содержимое');
			$this->table_news->string('hash', 32, 'Хэш файла');
			$this->table_news->string('ext', 6, 'Расширение файла');

			$this->db->PushTables($this->table_news);
		}

	}