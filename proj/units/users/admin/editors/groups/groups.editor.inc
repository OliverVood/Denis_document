<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'users/admin/editors/groups/groups.editor.model.inc';

	use Base\Editor\MySQLi\Editor;
	use Base\DB\MySQLi\Table;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Units;
	use Base\Editor\Skins\Browse;
	use Base\Editor\Skins\Edit;
	use Proj\Units\Consts;

	class Groups extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список групп';
			$this->titleCreate = 'Добавить группу';
			$this->titleUpdate = 'Редактирование группы';
			$this->titleDelete = 'Удалить группу?';
			$this->titleDoCreate = 'Группа добавлена';
			$this->titleDoUpdate = 'Группа изменена';
			$this->titleDoDelete = 'Группа удалена';

			$this->model = new Model\Groups($table, $this->params);
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLinkHrefAllow(self::ACCESS_UPDATE, 'Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return Units\Users::instance()->editor_access_groups->update->GetLinkHrefAllow(Units\Users::instance()->editor_access_groups::ACCESS_UPDATE, 'Установить права', array_merge(['gid' => $item['id']], $this->params)); },
				function (array $item) { return $this->do_delete->GetLinkHrefAllow(self::ACCESS_DELETE, 'Удалить', array_merge(['id' => $item['id']], $this->params)); },
			];
		}

		protected function FieldsSelect(): array {
			return [
				'id'		=> new Browse\Text('#'),
				'state' 	=> new Browse\ValueFromArray('Состояние', Consts\Users::STATES_GROUPS_VIEW),
				'name'		=> new Browse\Text('Наименование')
			];
		}

		protected function FieldsCreate(): array {
			return [
				'state'		=> new Edit\Hidden('Состояние', 'form[state]', Consts\Users::STATE_GROUP_ACTIVE),
				'name'		=> new Edit\Text('Название', 'form[name]')
			];
		}

		protected function FieldsUpdate(): array {
			return [
				'state'		=> new Edit\Select('Состояние', 'form[state]', [
					Consts\Users::STATE_GROUP_ACTIVE	=> 'Активная',
					Consts\Users::STATE_GROUP_INACTIVE	=> 'Не активная',
				]),
				'name'	=> new Edit\Text('Наименование', 'form[name]')
			];
		}

	}