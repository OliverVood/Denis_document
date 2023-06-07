<?php

	namespace Proj\Site\Units\HTML;

	require DIR_UNITS . 'users/users.consts.inc';
	require DIR_UNITS . 'users/site/users.model.inc';

	use Base\Units;
	use Base\Instance;
	use Proj\Units\Consts;

	class Users extends Units implements Consts\Users {
		use Instance;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
		}

	}

	Users::init();