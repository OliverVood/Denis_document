<?php

	namespace PROJ\Units;

	use Base\Units\Units;
	use Base\Units\Objects;

	require DIR_UNITS . 'users/consts.inc';

	class Users extends Units implements Consts\Users {
		use Objects;

		public function __construct() {
			parent::__construct(self::ID, self::NAME);
			self::$object = $this;
		}

		public function test() {
			echo '1234 ';
		}

	}

	Users::init();