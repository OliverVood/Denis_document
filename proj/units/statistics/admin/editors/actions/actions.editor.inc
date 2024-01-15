<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'statistics/admin/editors/actions/actions.editor.model.inc';

	use Base\Access;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins\Browse;
	use Proj\Admin\Editor\Model;

	class Actions extends Editor {
		public function __construct(int $id, string $name, Table $table, string $title = '') {

			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Статистика действий клиентов';

			$this->model = new Model\Actions($table, $this->params);
		}

		protected function RegAccess() {
			$this->AddCollection();
			$this->AddRight(self::ACCESS_SETTING, 'setting', 'Назначение прав');
			$this->AddRight(self::ACCESS_SELECT, 'select', 'Выборка');
		}

		protected function ManageSelect(): array {
			return [];
		}

		protected function FieldsSelect(): array {
			return [
				'datecr'	=> new Browse\DateFormat( 'Дата', 'd.m.Y H:i'),
				'cid' 		=> new Browse\Text( 'ID Клиента'),
				'object'	=> new Browse\Text( 'Объект'),
				'action'	=> new Browse\Text( 'Действие'),
				'params'	=> new Browse\Text( 'Параметры')
			];
		}

	}