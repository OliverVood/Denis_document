<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'users/admin/users.structure.inc';
	require DIR_UNITS . 'users/admin/users.model.inc';

	require DIR_UNITS . 'users/admin/editors/groups/groups.editor.inc';
	require DIR_UNITS . 'users/admin/editors/users/users.editor.inc';
	require DIR_UNITS . 'users/admin/editors/accessGroups/accessGroups.editor.inc';
	require DIR_UNITS . 'users/admin/editors/accessUsers/accessUsers.editor.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Helper\Response;
	use Proj\Admin\Structure;
	use Proj\Admin\Model;
	use Proj\Admin\Editor;
	use Proj\Admin\Templates\LayoutAuthorization;
	use Proj\Admin\Templates\TemplateAuthorization;
	use Proj\Admin\Templates\Users\FormAuthorization;
	use Proj\Editor\Consts as EditorConsts;
	use Proj\Params;
	use Closure;

	class Users extends Structure\Users {
		use Instance;

		private Model\Users $model;

		public Editor\Groups $editor_groups;
		public Editor\Users $editor_users;
		public Editor\AccessGroups $editor_access_groups;
		public Editor\AccessUsers $editor_access_users;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\Users::instance();

			$this->editor_groups = new Editor\Groups(EditorConsts\ID_USER_GROUPS, 'groups', $this->table_groups, 'Группы (редактор)');
			$this->editor_users = new Editor\Users(EditorConsts\ID_USER_USERS,'users', $this->table_users, 'Пользователи (редактор)');
			$this->editor_access_groups = new Editor\AccessGroups(EditorConsts\ID_USER_ACCESS_GROUPS, 'access_groups', $this->table_access_groups, 'Права групп (редактор)');
			$this->editor_access_users = new Editor\AccessUsers(EditorConsts\ID_USER_ACCESS_USERS, 'access_users', $this->table_access_users, 'Права пользователей (редактор)');

			self::$init->Push([self::ENTRY_XHR], self::$auth, Closure::fromCallable([$this, 'Auth']));
			self::$init->Push([self::ENTRY_XHR], self::$exit, Closure::fromCallable([$this, 'Exit']));
		}

		#region HTML

		public function IsPossibleHTML(): void {
			if ($this->model->IsLogin()) return;

			require DIR_PROJ . 'templates/admin/layoutAuthorization.inc';
			require DIR_PROJ . 'templates/admin/templateAuthorization.tpl';
			require DIR_UNITS . 'users/admin/views/FormAuthorization.tpl';

			LayoutAuthorization::instance()->header->Push('Вход в систему');
			LayoutAuthorization::instance()->main->Push(FormAuthorization::ToVar());
			LayoutAuthorization::instance()->footer->Push('© ' . Params::$site_name);

			TemplateAuthorization::Render();

			die;
		}

		public function GetMenuGroup(): array {
			$out = [];
			if ($this->editor_groups->Allow($this->editor_groups::ACCESS_SELECT)) $out[] = $this->editor_groups->select->GetLinkHref('Список групп', ['page' => 1]);
			if ($this->editor_groups->Allow($this->editor_groups::ACCESS_CREATE)) $out[] = $this->editor_groups->create->GetLinkHref('Добавить группу');

			return $out;
		}

		#endregion HTML

		public function GetMenuUser(): array {
			$out = [];
			if ($this->editor_users->Allow($this->editor_users::ACCESS_SELECT)) $out[] = $this->editor_users->select->GetLinkHref('Список пользователей', ['page' => 1]);
			if ($this->editor_users->Allow($this->editor_users::ACCESS_CREATE)) $out[] = $this->editor_users->create->GetLinkHref('Добавить пользователя');

			return $out;
		}

		#region XHR

		public function IsPossibleXHR(): void {
			if ($this->model->IsLogin() || ((self::$area == self::NAME) && (self::$part == 'auth'))) return;

			Response::PushNoticeError('Пожалуйста, авторизуйтесь');
			Response::SendJSON();
		}

		#[NoReturn] private function Auth(): void {
			$login = GetParam('login', '');
			$password = GetParam('password', '');

			if (!$this->model->Auth($login, $password)) {
				Response::PushNoticeError('Ошибка доступа');
				Response::SendJSON();
			}

			Response::PushData([]);
			Response::SendJSON();
		}

		#[NoReturn] private function Exit(): void {
			$this->model->Logout();

			Response::PushData([]);
			Response::SendJSON();
		}

		#endregion XHR

	}

	Users::init();