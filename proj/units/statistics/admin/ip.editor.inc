<?php

	namespace Proj\Admin\Editor;

	use Base\Editor\Skins;
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

		protected function RegTitles(): void {
			$this->titleSelect = 'Статистика запросов к серверу';
		}

		protected function FieldsSelect(array $params): array {
			return [
				'datecr'	=> new Skins\Text('Дата'),
				'uid'		=> new Skins\Text('Пользователь'),
				'ip'		=> new Skins\Int2IP('IP aдрес'),
				'path'		=> new Skins\Text('Путь'),
				'params'	=> new Skins\Text('Параметры')
			];
		}

		protected function Manage(): array { return  []; }

	}