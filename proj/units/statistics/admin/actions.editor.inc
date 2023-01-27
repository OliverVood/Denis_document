<?php

	namespace Proj\Admin\Editor;

	use Base\Editor\EditorMySQLi;
	use Base\DB\TableMySQLi;

	class Actions extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			$params = [
				'order' => [
					'datecr DESC',
					'id DESC'
				],
				'select' => [
					'datecr' => 'Дата',
					'uid' => 'Пользователь',
					'object' => 'Объект',
					'action' => 'Действие',
					'params' => 'Параметры'
				]
			];

			parent::__construct($name, $table, $params);

			$this->controlUpdate = false;
			$this->controlDelete = false;

			$this->titleSelect = 'Статистика действий пользователя';
		}

	}