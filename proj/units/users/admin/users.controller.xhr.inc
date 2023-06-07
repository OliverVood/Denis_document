<?php

	namespace Proj\Admin\Units\XHR;

	require DIR_UNITS . 'users/admin/users.structure.inc';
	require DIR_UNITS . 'users/admin/users.model.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Controller;
	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Model;
	use Response;

	class Users extends Structure\Users {
		use Instance;

		private Model\Users $model;

		private function __construct() {
			parent::__construct();

			$this->model = Model\Users::instance();

			self::$init->Push(self::$auth, [$this, 'Auth']);
			self::$init->Push(self::$exit, [$this, 'Exit']);
		}

		public function IsPossible(): void {
			if ($this->model->IsLogin() || ((Controller::$area == self::NAME) && (Controller::$part == 'auth'))) return;

			Response::PushNoticeError('Пожалуйста, авторизуйтесь');
			Response::SendJSON();
		}


		#[NoReturn] public function Auth(): void {
			$login = GetParam('login', '');
			$password = GetParam('password', '');
			$hash = $this->model->PasswordHash($password);

			if (($login != USER_LOGIN) || ($hash != USER_PASSWORD)) {
				Response::PushNoticeError('Ошибка доступа');
				Response::SendJSON();
			}

			$this->model->Login();

			Response::PushData([]);
			Response::SendJSON();
		}

		#[NoReturn] public function Exit(): void {
			$this->model->Logout();

			Response::PushData([]);
			Response::SendJSON();
		}

	}

	Users::init();