<?php

	namespace Proj\Admin\Editor;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Units\Consts;

	class Feedback extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\Feedback::STATES['delete']
			];
		}

		protected function Order(): array {
			return [
				'`datecr` DESC',
				'`id` ASC'
			];
		}

		protected function RegTitles(): void {//TODO d Editor добавить изменение состояния, тут в done
			$this->titleSelect = 'Список обратной связи';
			$this->titleBrowse = 'Обратная связь';
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id'		=> new Skins\Text('#'),
				'state'		=> new Skins\Text('Состояние'),
				'datecr'	=> new Skins\Text('Дата'),
				'name'		=> new Skins\Text('Имя'),
				'contacts'	=> new Skins\Text('Контакт'),
				'letter'	=> new Skins\Text('Тема сообщения')
			];
		}

		protected function FieldsBrowse(array $params): array {
			return [
				'state' => ['name' => 'Состояние'],
				'datecr' => ['name' => 'Дата'],
				'name' => ['name' => 'Имя'],
				'contacts' => ['name' => 'Контакты'],
				'letter' => ['name' => 'Тема'],
				'content' => ['name' => 'Содержание']
			];
		}

		protected function Manage(): array {
			return [
				function (array $params, array $item) { return $this->do_delete->GetLink('Удалить', ['id' => $item['id']]); },
				function (array $params, array $item) { return $this->browse->GetLink('Просмотреть', ['id' => $item['id']]); }
			];
		}

	}