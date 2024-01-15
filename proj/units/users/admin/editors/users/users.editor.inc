<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'users/admin/editors/users/users.editor.model.inc';

	use Base\Editor\MySQLi\Editor;
	use Base\DB\MySQLi\Table;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Model as UnitModel;
	use Proj\Admin\Units;
	use Base\Editor\Skins\Browse;
	use Base\Editor\Skins\Edit;
	use Proj\Units\Consts;

	class Users extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список пользователей';
			$this->titleCreate = 'Добавить пользователя';
			$this->titleUpdate = 'Редактирование пользователя';
			$this->titleDelete = 'Удалить пользователя?';
			$this->titleDoCreate = 'Пользователь добавлен';
			$this->titleDoUpdate = 'Пользователь изменён';
			$this->titleDoDelete = 'Пользователь удалён';

			$this->model = new Model\Users($table, $this->params);
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLinkHrefAllow(self::ACCESS_UPDATE, 'Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return Units\Users::instance()->editor_access_users->update->GetLinkHrefAllow(Units\Users::instance()->editor_access_users::ACCESS_UPDATE, 'Установить права', array_merge(['uid' => $item['id']], $this->params)); },
				function (array $item) { return $this->do_delete->GetLinkHrefAllow(self::ACCESS_DELETE, 'Удалить', array_merge(['id' => $item['id']], $this->params)); },
			];
		}

		protected function PrepareOnUpdate(int $id, array & $item): void {
			$item['password'] = '';
		}

		protected function FieldsSelect(): array {
			return [
				'id'			=> new Browse\Text('#'),
				'state' 		=> new Browse\ValueFromArray('Состояние', Consts\Users::STATES_USERS_VIEW),
				'gid'			=> new Browse\ValueFromArray('ID Группы', UnitModel\Users::instance()->GetListGroups()),
				'login'			=> new Browse\Text('Логин'),
				'first_name'	=> new Browse\Text('Имя'),
				'last_name'		=> new Browse\Text('Фамилия'),
				'father_name'	=> new Browse\Text('Отчество'),
			];
		}

		protected function FieldsCreate(): array {
			return [
				'state'			=> new Edit\Hidden('Состояние', 'form[state]', Consts\Users::STATE_USER_ACTIVE),
				'gid'			=> new Edit\Select('ID Группы', 'form[gid]', UnitModel\Users::instance()->GetListGroups()),
				'login'			=> new Edit\Text('Логин', 'form[login]'),
				'password'		=> new Edit\Input('Пароль', 'form[password]', 'password'),
				'first_name'	=> new Edit\Text('Имя', 'form[first_name]'),
				'last_name'		=> new Edit\Text('Фамилия', 'form[last_name]'),
				'father_name'	=> new Edit\Text('Отчество', 'form[father_name]')
			];
		}

		protected function FieldsUpdate(): array {
			return [
				'state'			=> new Edit\Select('Состояние', 'form[state]', [
					Consts\Users::STATE_USER_ACTIVE		=> 'Активный',
					Consts\Users::STATE_USER_INACTIVE	=> 'Не активный',
					Consts\Users::STATE_USER_BLOCK		=> 'Заблокированный'
				]),
				'gid'			=> new Edit\Select('ID Группы', 'form[gid]', UnitModel\Users::instance()->GetListGroups()),
				'login'			=> new Edit\Text('Логин', 'form[login]'),
				'password'		=> new Edit\Input('Пароль', 'form[password]', 'password'),
				'first_name'	=> new Edit\Text('Имя', 'form[first_name]'),
				'last_name'		=> new Edit\Text('Фамилия', 'form[last_name]'),
				'father_name'	=> new Edit\Text('Отчество', 'form[father_name]')
			];
		}

	}