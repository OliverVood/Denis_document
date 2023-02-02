<?php

	namespace Proj\Admin\Editor;

	use Base\Editor\EditorMySQLi;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;

	class Changes extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->where = [
				'state != ' . Consts\Changes::STATES['delete']
			];
			$this->order = [
				'`datecr` DESC',
				'`id` ASC'
			];

			$this->fieldsSelect = [
				'id' => '#',
				'state' => 'Состояние',
				'datepb' => 'Дата публикации',
				'header' => 'Заголовок',
			];
			$this->fieldsCreate = [
				'state' => ['skin' => 'hidden', 'name' => 'Состояние', 'default' => Consts\Changes::STATES['draft']],
				'header' => ['skin' => 'text', 'name' => 'Заголовок', 'default' => ''],
				'datepb' => ['skin' => 'datetime', 'name' => 'Дата публикации']
			];
			$this->fieldsUpdate = [
				'state' => ['skin' => 'select', 'name' => 'Состояние'],
				'header' => ['skin' => 'text', 'name' => 'Заголовок'],
				'datepb' => ['skin' => 'datetime', 'name' => 'Дата публикации']
			];

			$this->navigateCreate = [ function ($items) { return $this->select->GetLink("<< {$this->titleSelect}"); } ];
			$this->navigateUpdate = [ function ($items) { return $this->select->GetLink("<< {$this->titleSelect}"); } ];

			$this->manage = [
				function ($item) { return $this->update->GetLink('Изменить', ['id' => $item['id']]); },
				function ($item) { return $this->do_delete->GetLink('Удалить', ['id' => $item['id']]); },
				function ($item) { return \Proj\Admin\Units\Changes::instance()->editor_change->select->GetLink('Список', ['cid' => $item['id']]); }
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

		public function PrepareOnUpdate(int $id, array & $item, array &$data): void {
			$data['state'] = [
				Consts\Changes::STATE_DRAFT		=> 'Черновик',
				Consts\Changes::STATE_ACTIVE	=> 'Активная',
				Consts\Changes::STATE_INACTIVE	=> 'Не активная',
			];
		}

	}