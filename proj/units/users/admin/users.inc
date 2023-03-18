<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'users/admin/users.structure.inc';
	require DIR_UNITS . 'news/admin/views/Form.tpl';

	use Base\Instance;
//	use Base\Controller;
//	use Base\Action;
	use JetBrains\PhpStorm\NoReturn;
	use Proj\Site\Structure;
	use Proj\Admin\Templates\LayoutAuthorization;
	use Proj\Admin\Templates\Users\Form;

	class Users extends Structure\Users {
		use Instance;

//		public Action $ident;

		private static bool $login = false;

		private string | null $uid = null;

		private function __construct() {
			parent::__construct();

//			$this->ident = new Action('null', 'null');

			$this->IsSession();
			if (!$this->CheckLogin()) $this->GetForm();

//			Controller::instance()->init->Push($this->ident, [$this, 'Ident']);
		}

		public function IsSession(): void {
			if (isset($_SESSION['USERS'])) {
				self::$login = $_SESSION['USERS']['LOGIN'] ?? false;
			}
		}

		public function CheckLogin(): bool {
			return self::$login;
		}

		#[NoReturn] public function GetForm():void {
			require DIR_PROJ . 'templates/authorization/layout.inc';
			require DIR_PROJ . 'templates/authorization/index.tpl';

			LayoutAuthorization::instance()->main->Push(Form::object()->ToVar());

			\Proj\Admin\Templates\TemplateAuthorization::object()->Render();
			die;
		}

//		private function CheckPassword() {
//
//		}

	}

	Users::init();