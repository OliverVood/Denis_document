<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'changes/admin/editors/changes/changes.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins\Browse;
	use Base\Editor\Skins\Edit;
	use Proj\Admin\Units;
	use Proj\Admin\Editor\Model;
	use Proj\Units\Consts;

	class Changes extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Списки актуального';
			$this->titleCreate = 'Добавить список актуального';
			$this->titleUpdate = 'Редактировать список актуального';
			$this->titleDelete = 'Удалить список актуального?';

			$this->titleDoCreate = 'Список актуального добавлен';
			$this->titleDoUpdate = 'Список актуального изменён';
			$this->titleDoDelete = 'Список актуального удалён';

			$this->model = new Model\Changes($table);
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLinkHrefAllow(self::ACCESS_UPDATE, 'Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->do_delete->GetLinkHrefAllow(self::ACCESS_DELETE, 'Удалить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return Units\Changes::instance()->editor_change->select->GetLinkHrefAllow(Units\Changes::instance()->editor_change::ACCESS_SELECT, 'Список', array_merge(['cid' => $item['id'], 'page' => 1], $this->params)); }
			];
		}

		protected function FieldsSelect(): array {
			return [
				'id'			=> new Browse\Text('#'),
				'state'			=> new Browse\ValueFromArray('Состояние', Consts\Changes::STATES_VIEW),
				'datepb'		=> new Browse\DateFormat('Дата публикации', 'd.m.Y H:i'),
				'work_header'	=> new Browse\Text('Рабочий заголовок'),
				'header'		=> new Browse\Text('Заголовок'),
			];
		}

		protected function FieldsCreate(): array {
			return [
				'state'			=> new Edit\Hidden('Состояние', 'form[state]', Consts\Changes::STATES['draft']),
				'work_header'	=> new Edit\Text('Рабочий заголовок', 'form[work_header]'),
				'header'		=> new Edit\Text('Заголовок', 'form[header]'),
				'datepb'		=> new Edit\DateTime('Дата публикации', 'form[datepb]')
			];
		}

		protected function FieldsUpdate(): array {
			return [
				'state'			=> new Edit\Select('Состояние', 'form[state]', [
					Consts\Changes::STATE_DRAFT	=> 'Черновик',
					Consts\Changes::STATE_ACTIVE	=> 'Активный',
					Consts\Changes::STATE_INACTIVE	=> 'Не активный',
				]),
				'work_header'	=> new Edit\Text('Рабочий заголовок', 'form[work_header]'),
				'header'		=> new Edit\Text('Заголовок', 'form[header]'),
				'datepb'		=> new Edit\DateTime('Дата публикации', 'form[datepb]')
			];
		}

	}