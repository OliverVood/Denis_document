<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins\Browse;
	use Proj\Admin\Editor\Model;
	use Proj\Units\Consts;

	class Feedback extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список обратной связи';
			$this->titleBrowse = 'Обратная связь';
			$this->titleDelete = 'Удалить запись?';

			$this->titleDoDelete = 'Запись удалена';

			$this->model = new Model\Feedback($table);
		}

		protected function RegAccess() {
			$this->AddCollection();
			$this->AddRight(self::ACCESS_SETTING, 'setting', 'Назначение прав');
			$this->AddRight(self::ACCESS_SELECT, 'select', 'Выборка');
			$this->AddRight(self::ACCESS_BROWSE, 'browse', 'Вывод');
			$this->AddRight(self::ACCESS_DELETE, 'delete', 'Удаление');
			$this->AddRight(self::ACCESS_STATE, 'state', 'Изменение состояния');
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->browse->GetLinkHrefAllow(self::ACCESS_BROWSE, 'Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return ($item['state'] == Consts\Feedback::STATE_NEW) ? $this->set_state->GetLinkHrefAllow(self::ACCESS_STATE, 'Проверена', array_merge(['id' => $item['id'], 'state' => Consts\Feedback::STATE_DONE], $this->params)) : ''; },
				function (array $item) { return $this->do_delete->GetLinkHrefAllow(self::ACCESS_DELETE, 'Удалить', array_merge(['id' => $item['id']], $this->params)); }
			];
		}

		protected function FieldsSelect(): array {
			return [
				'id' 		=> new Browse\Text('#'),
				'state' 	=> new Browse\ValueFromArray('Состояние', Consts\Feedback::STATES_VIEW),
				'datecr'	=> new Browse\DateFormat('Дата', 'd.m.Y H:i'),
				'name'		=> new Browse\Text('Имя'),
				'contacts'	=> new Browse\Text('Контакт'),
				'letter'	=> new Browse\Text('Тема сообщения')
			];
		}

		protected function FieldsBrowse(): array {
			return [
				'state' 	=> new Browse\ValueFromArray('Состояние', Consts\Feedback::STATES_VIEW),
				'datecr'	=> new Browse\DateFormat('Дата', 'd.m.Y H:i'),
				'name'		=> new Browse\Text('Имя'),
				'contacts'	=> new Browse\Text('Контакт'),
				'letter'	=> new Browse\Text('Тема сообщения'),
				'content'	=> new Browse\Text('Содержание')
			];
		}

	}