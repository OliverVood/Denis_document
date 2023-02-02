<?php

	namespace Proj\Admin\Editor;

	use Base\Editor\EditorMySQLi;
	use Base\DB\TableMySQLi;

	class Actions extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->order = [
				'datecr DESC',
				'id DESC'
			];

			$this->fieldsSelect = [
				'datecr' => 'Дата',
				'uid' => 'Пользователь',
				'object' => 'Объект',
				'action' => 'Действие',
				'params' => 'Параметры'
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Статистика действий пользователя';
		}

	}