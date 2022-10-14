<?php

	namespace PROJ\Units;

	use Base\Units\Units;
	use Base\Instance;

	require DIR_UNITS . 'users/consts.inc';

	class Users extends Units implements Consts\Users {
		use Instance;

		public function __construct() {
			parent::__construct(self::ID, self::NAME);
		}

		public function test() {
			echo '1234 ';
		}

	}

	Users::init();