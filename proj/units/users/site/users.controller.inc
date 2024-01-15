<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'users/site/users.actions.inc';
	require DIR_UNITS . 'users/site/users.model.inc';

	use Base\Instance;
	use Proj\Site\Actions;

	class Users extends Actions\Users {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

	}

	Users::init();