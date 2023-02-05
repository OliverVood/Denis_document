<?php

	namespace Proj\Admin\Editor;

	use Base\Editor\EditorMySQLi;
	use Base\DB\TableMySQLi;

	class Actions extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function Order(): array {
			return [
				'`datecr` DESC',
				'`id` DESC'
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Статистика действий пользователя';
		}

		protected function Manage(): array { return  []; }

		protected function FieldsSelect(array $params): array {
			return [
				'datecr' => 'Дата',
				'uid' => 'Пользователь',
				'object' => 'Объект',
				'action' => 'Действие',
				'params' => 'Параметры'
			];
		}

	}