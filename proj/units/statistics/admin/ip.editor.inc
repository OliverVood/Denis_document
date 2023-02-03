<?php

	namespace Proj\Admin\Editor;

	use Base\Editor\EditorMySQLi;
	use Base\DB\TableMySQLi;

	class Ip extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function Order(): array {
			return [
				'`datecr` DESC',
				'`id` DESC'
			];
		}

		protected function FieldsSelect(): array {
			return [
				'datecr' => 'Дата',
				'uid' => 'Пользователь',
				'ip_part_I' => 'IP часть I',
				'ip_part_II' => 'IP часть II',
				'ip_part_III' => 'IP часть III',
				'ip_part_IV' => 'IP часть IV',
				'path' => 'Основной путь',
				'params' => 'Параметры'
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Статистика запросов к серверу';
		}

		protected function Manage(): array { return  []; }

	}