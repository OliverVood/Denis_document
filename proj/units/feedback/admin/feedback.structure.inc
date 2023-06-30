<?php

	namespace Proj\Admin\Structure;

	require DIR_UNITS . 'feedback/admin/feedback.actions.inc';

	use Base\DB\MySQLi\Table;
	use Proj\Admin\Actions;
	use Proj\DBObject;

	class Feedback extends Actions\Feedback {
		private DBObject $db;

		protected Table $table_feedback;

		protected function __construct() {
			parent::__construct();
			$this->db = DBObject::instance();

			$this->table_feedback = new Table(self::TABLES['feedback'], $this->db, 'Обратная связь');
			$this->table_feedback->id('id', 'Идентификатор');
			$this->table_feedback->uint8('state', 'Состояние');
			$this->table_feedback->timestamp('datecr', false, 'Дата создания');
			$this->table_feedback->timestamp('datemd', true, 'Дата изменения');
			$this->table_feedback->string('name', 255, 'Имя');
			$this->table_feedback->string('contacts', 255, 'Контакты');
			$this->table_feedback->string('letter', 255, 'Тема');
			$this->table_feedback->text('content', 'Содержимое');

			$this->db->PushTables($this->table_feedback);
		}

	}