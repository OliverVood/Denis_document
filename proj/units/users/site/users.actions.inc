<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'users/users.consts.inc';

	use Base\Unit;
	use Proj\Units\Consts;

	abstract class Users extends Unit implements Consts\Users {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Users::RegActions();