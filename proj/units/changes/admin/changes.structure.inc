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

		protected function __construct($file) {
			parent::__construct($file);
			$this->db = DBObject::instance();

			$this->table_changes = new Table(self::TABLES['changes'], $this->db, 'Список актуального');
			$this->table_changes->id('id', 'Идентификатор');
			$this->table_changes->uint8('state', 'Состояние');
			$this->table_changes->timestamp('datecr', false, 'Дата создания');
			$this->table_changes->timestamp('datemd', true, 'Дата изменения');
			$this->table_changes->timestamp('datepb', false, 'Дата публикации');
			$this->table_changes->string('work_header', 255, 'Рабочий заголовок');
			$this->table_changes->string('header', 255, 'Заголовок');

			$this->table_change = new Table(self::TABLES['change'], $this->db, 'Актуальное');
			$this->table_change->id('id', 'Идентификатор');
			$this->table_change->uint32('cid', 'ID списка актуального');
			$this->table_change->uint8('state', 'Состояние');
			$this->table_change->timestamp('datecr', false, 'Дата создания');
			$this->table_change->timestamp('datemd', true, 'Дата изменения');
			$this->table_change->string('header', 255, 'Заголовок');
			$this->table_change->text('content', 'Содержимое');
			$this->table_change->string('hash', 32, 'Хэш файла');
			$this->table_change->string('ext', 6, 'Расширение файла');
			$this->table_change->AddForeign('foreign', ['cid'], self::TABLES['changes'], ['id']);

			$this->db->PushTables($this->table_changes, $this->table_change);
		}

	}