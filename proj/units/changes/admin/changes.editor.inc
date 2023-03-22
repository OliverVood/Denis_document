<?php

	namespace Proj\Admin\Editor;

	use Base\DB\TableMySQLi;
	use Base\Editor\EditorMySQLi;
	use Base\Editor\Skins;
	use Proj\Units\Consts;

	class Changes extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\Changes::STATES['delete']
			];
		}

		protected function Order(): array {
			return [
				'`datecr` DESC',
				'`id` ASC'
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Списки актуального';
			$this->titleCreate = 'Добавить список актуального';
			$this->titleUpdate = 'Редактировать список актуального';
			$this->titleDelete = 'Удалить список актуального?';

			$this->titleDoCreate = 'Список актуального добавлен';
			$this->titleDoUpdate = 'Список актуального изменён';
			$this->titleDoDelete = 'Список актуального удалён';
		}

		protected function Manage(): array {
			return [
				function (array $params, array $item) { return $this->update->GetLink('Изменить', ['id' => $item['id']]); },
				function (array $params, array $item) { return $this->do_delete->GetLink('Удалить', ['id' => $item['id']]); },
				function (array $params, array $item) { return \Proj\Admin\Units\Changes::instance()->editor_change->select->GetLink('Список', ['cid' => $item['id']]); }
			];
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id'			=> new Skins\Text('#'),
				'state'			=> new Skins\Text('Состояние'),
				'datepb'		=> new Skins\Text('Дата публикации'),
				'work_header'	=> new Skins\Text('Рабочий заголовок'),
				'header'		=> new Skins\Text('Заголовок'),
			];
		}

		protected function FieldsCreate(array $params): array {
			return [
				'state' => ['skin' => 'hidden', 'name' => 'Состояние', 'default' => Consts\Changes::STATES['draft']],
				'work_header' => ['skin' => 'text', 'name' => 'Рабочий заголовок', 'default' => ''],
				'header' => ['skin' => 'text', 'name' => 'Заголовок', 'default' => ''],
				'datepb' => ['skin' => 'datetime', 'name' => 'Дата публикации']
			];
		}

		protected function FieldsUpdate(array $params): array {
			return [
				'state' => ['skin' => 'select', 'name' => 'Состояние'],
				'work_header' => ['skin' => 'text', 'name' => 'Рабочий заголовок'],
				'header' => ['skin' => 'text', 'name' => 'Заголовок'],
				'datepb' => ['skin' => 'datetime', 'name' => 'Дата публикации']
			];
		}

		public function PrepareOnUpdate(int $id, array & $item, array &$data): void {
			$data['state'] = [
				Consts\Changes::STATE_DRAFT		=> 'Черновик',
				Consts\Changes::STATE_ACTIVE	=> 'Активная',
				Consts\Changes::STATE_INACTIVE	=> 'Не активная',
			];
		}

	}