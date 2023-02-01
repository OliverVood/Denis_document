<?php

	namespace Proj\Admin\Editor;

	use Base\Editor\EditorMySQLi;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;

	class Changes extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			$params = [
				'where' => [
					'state != 100'
				],
				'order' => [
					'`datecr` DESC',
					'`id` ASC'
				],
				'select' => [
					'id' => '#',
					'state' => 'Состояние',
					'datecr' => 'Дата создания',
					'header' => 'Заголовок',
					'datepb' => 'Дата публикации'
				],
				'create' => [
					'state' => ['skin' => 'hidden', 'name' => 'Состояние', 'default' => Consts\Changes::STATES['draft']],
					'header' => ['skin' => 'text', 'name' => 'Заголовок', 'default' => ''],
					'datepb' => ['skin' => 'datetime', 'name' => 'Дата публикации']
				],
				'update' => [
					'state' => ['skin' => 'select', 'name' => 'Состояние'],
					'header' => ['skin' => 'text', 'name' => 'Заголовок'],
					'datepb' => ['skin' => 'datetime', 'name' => 'Дата публикации']
				],
				'manage' => [
					function ($item) { return $this->update->GetLink('Изменить', ['id' => $item['id']]); },
					function ($item) { return $this->do_delete->GetLink('Удалить', ['id' => $item['id']]); },
					function ($item) { return \Proj\Admin\Units\Changes::instance()->editor_change->select->GetLink('Список', ['cid' => $item['id']]); }
				]
			];

			parent::__construct($name, $table, $params);

			$this->titleSelect = 'Списки изменений';
			$this->titleCreate = 'Добавить новый список';
			$this->titleUpdate = 'Редактировать список';

			$this->titleDoCreate = 'Список изменений добавлен';
			$this->titleDoUpdate = 'Список изменений изменён';
		}

		public function PrepareOnUpdate(int $id, array & $item, array &$data): void {
			$data['state'] = [
				Consts\Changes::STATE_DRAFT		=> 'Черновик',
				Consts\Changes::STATE_ACTIVE	=> 'Активная',
				Consts\Changes::STATE_INACTIVE	=> 'Не активная',
			];
		}

	}