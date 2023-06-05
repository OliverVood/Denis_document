<?php

	namespace Proj\Admin\Units\HTML;

	require DIR_UNITS . 'users/admin/users.actions.inc';
	require DIR_UNITS . 'users/admin/users.model.inc';
	require DIR_UNITS . 'users/admin/views/FormAuthorization.tpl';

	use Base\Instance;
	use Proj\Admin\Actions;
	use Proj\Admin\Model;
	use Proj\Admin\Templates\LayoutAuthorization;
	use Proj\Admin\Templates\TemplateAuthorization;
	use Proj\Admin\Templates\Users\FormAuthorization;
	use Proj\Params;

	class Users extends Actions\Users {
		use Instance;

		private function __construct() {
			parent::__construct();
		}

		public function IsPossible(): void {
			if (Model\Users::instance()->IsLogin()) return;

			require DIR_PROJ . 'templates/admin/layoutAuthorization.inc';
			require DIR_PROJ . 'templates/admin/templateAuthorization.tpl';

			LayoutAuthorization::instance()->header->Push('Вход в систему');
			LayoutAuthorization::instance()->main->Push(FormAuthorization::ToVar());
			LayoutAuthorization::instance()->footer->Push('© ' . Params::$site_name);

			TemplateAuthorization::Render();

			die;
		}

	}

	Users::init();