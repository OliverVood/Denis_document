<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'users/admin/users.structure.inc';
	require DIR_UNITS . 'users/admin/views/FormAuthorization.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\TemplateAuthorization;
	use Proj\Admin\Templates\LayoutAuthorization;
	use Proj\Admin\Templates\Users\FormAuthorization;

	class Users extends Structure\Users {
		use Instance;

		public Action $auth;

		private string | null $uid = null;
		private static bool $login = false;

		private function __construct() {//unset($_SESSION['USERS']['LOGIN']);die;
			parent::__construct();

			$this->CheckSession();

			$this->auth = new Action(self::NAME, 'auth', 'default', /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this, () => { console.log(1); }/*Admin.Login.Do*/); return false;");

			Controller::instance()->init->Push($this->auth, [$this, 'Auth']);
		}

		public function IsPossible() {
			if (!$this->IsLogin() && ((Controller::$area != self::NAME) || (Controller::$part != 'auth'))) $this->GetForm();
		}

		public function CheckSession(): void {
			if (isset($_SESSION['USERS'])) {
				self::$login = $_SESSION['USERS']['LOGIN'] ?? false;
			}
		}

		public function IsLogin(): bool {
			return self::$login;
		}

		#[NoReturn] public function GetForm():void {
			require DIR_PROJ . 'templates/authorization/layout.inc';
			require DIR_PROJ . 'templates/authorization/index.tpl';

			LayoutAuthorization::instance()->main->Push(FormAuthorization::object()->ToVar());
			TemplateAuthorization::object()->Render();

			die;
		}

		#[NoReturn] public function Auth(): void {
			$login = GetParam('login', '');
			$password = GetParam('password', '');
			$hash = $this->PasswordHash($password);

			if (($login != USER_LOGIN) || ($hash != USER_PASSWORD)) SendNoticeError('Ошибка доступа');

			$this->Login();

			SendJSONSuccess([]);
		}

		private function Login() {
			$_SESSION['USERS']['LOGIN'] = true;
		}

		private function PasswordHash($pass) {
			return $pass;
		}

	}

	Users::init();