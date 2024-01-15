<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'statistics/admin/editors/ip/ip.editor.model.inc';

	use Base\Access;
	use Base\DB\MySQLi\Table;
	use Base\Editor\Skins\Browse;
	use Base\Editor\MySQLi\Editor;
	use Proj\Admin\Editor\Model;

	class Ip extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Статистика запросов к серверу';

			$this->model = new Model\Ip($table, $this->params);
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
				'datecr'	=> new Browse\DateFormat('Дата', 'd.m.Y H:i'),
				'cid'		=> new Browse\Text('ID Клиента'),
				'ip'		=> new Browse\Int2IP('IP адрес'),
				'path'		=> new Browse\Text('Путь'),
				'params'	=> new Browse\Text('Параметры')
			];
		}

	}