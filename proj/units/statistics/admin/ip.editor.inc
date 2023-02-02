<?php

	namespace Proj\Admin\Editor;

	use Base\Editor\EditorMySQLi;
	use Base\DB\TableMySQLi;

	class Ip extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->order = [
				'datecr DESC',
				'id DESC'
			];

			$this->fieldsSelect = [
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

	}