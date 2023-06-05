<?php

	namespace Proj\Admin\Units\XHR;

	require DIR_UNITS . 'users/admin/users.actions.inc';
	require DIR_UNITS . 'users/admin/users.model.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Controller;
	use Base\Instance;
	use Proj\Admin\Actions;
	use Proj\Admin\Model;
	use Response;

	class Users extends Actions\Users {
		use Instance;

		private function __construct() {
			parent::__construct();

			self::$init->Push(self::$auth, [$this, 'Auth']);
			self::$init->Push(self::$exit, [$this, 'Exit']);
		}

		public function IsPossible(): void {
			if (Model\Users::instance()->IsLogin() || ((Controller::$area == self::NAME) && (Controller::$part == 'auth'))) return;

			Response::PushNoticeError('Пожалуйста, авторизуйтесь');
			Response::SendJSON();
		}


		#[NoReturn] public function Auth(): void {
			$login = GetParam('login', '');
			$password = GetParam('password', '');
			$hash = Model\Users::instance()->PasswordHash($password);

			if (($login != USER_LOGIN) || ($hash != USER_PASSWORD)) {
				Response::PushNoticeError('Ошибка доступа');
				Response::SendJSON();
			}

			Model\Users::instance()->Login();

			Response::PushData([]);
			Response::SendJSON();
		}

		#[NoReturn] public function Exit(): void {
			Model\Users::instance()->Logout();

			Response::PushData([]);
			Response::SendJSON();
		}

	}

	Users::init();