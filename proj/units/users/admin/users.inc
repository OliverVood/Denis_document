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
	use Proj\Site\Params;

	class Users extends Structure\Users {
		use Instance;

		public Action $auth;
		public Action $exit;

		private string | null $uid = null;
		private static bool $login = false;

		private function __construct() { // unset($_SESSION['USERS']['LOGIN']); die;
			parent::__construct();

			$this->CheckSession();

			$this->auth = new Action(self::NAME, 'auth', 'default', /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this, () => location.reload()); return false;");
			$this->exit = new Action(self::NAME, 'exit', 'default', /* @lang JavaScript */ "Base.Common.Query.Send('/users/exit', () => location.reload()); return false;");

			Controller::instance()->init->Push($this->auth, [$this, 'Auth']);
			Controller::instance()->init->Push($this->exit, [$this, 'Exit']);
		}

		public function IsLogin(): bool {
			return self::$login;
		}

		public function IsPossible(): void {
			if (!$this->IsLogin() && ((Controller::$area != self::NAME) || (Controller::$part != 'auth'))) $this->GetForm();
		}

		#[NoReturn] public function Auth(): void {
			$login = GetParam('login', '');
			$password = GetParam('password', '');
			$hash = $this->PasswordHash($password);

			if (($login != USER_LOGIN) || ($hash != USER_PASSWORD)) SendNoticeError('Ошибка доступа');

			$this->Login();

			SendJSONSuccess([]);
		}

		#[NoReturn] public function Exit(): void {
			$this->Logout();

			SendJSONSuccess([]);
		}

		private function Login(): void {
			$_SESSION['USERS']['LOGIN'] = true;
		}

		private function Logout(): void {
			$_SESSION['USERS']['LOGIN'] = false;
		}

		private function CheckSession(): void {
			if (isset($_SESSION['USERS'])) {
				self::$login = $_SESSION['USERS']['LOGIN'] ?? false;
			}
		}

		private function PasswordHash($pass): string {
			return md5($pass);
		}

		#[NoReturn] private function GetForm(): void {
			require DIR_PROJ . 'templates/admin/layoutAuthorization.inc';
			require DIR_PROJ . 'templates/admin/templateAuthorization.tpl';

			LayoutAuthorization::instance()->header->Push('Вход в систему');
			LayoutAuthorization::instance()->main->Push(FormAuthorization::object()->ToVar());
			LayoutAuthorization::instance()->footer->Push('© ' . Params::$site_name);

			TemplateAuthorization::object()->Render();

			die;
		}

	}

	Users::init();