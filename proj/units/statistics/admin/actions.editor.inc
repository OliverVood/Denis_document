<?php

	namespace Proj\Admin\Editor;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;

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
				'datecr'	=> new Skins\Text( 'Дата'),
				'uid' 		=> new Skins\Text( 'Пользователь'),
				'object'	=> new Skins\Text( 'Объект'),
				'action'	=> new Skins\Text( 'Действие'),
				'params'	=> new Skins\Text( 'Параметры')
			];
		}

	}