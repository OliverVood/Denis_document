<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'users/users.consts.inc';

	use Base\UnitAccess;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class Users extends UnitAccess implements Consts\Users {
		public static Action $auth;
		public static Action $exit;

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {
			self::$auth			= new Action(Consts\Users::NAME, 'auth', 'default', /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this, () => location.reload()); return false;");
			self::$exit			= new Action(Consts\Users::NAME, 'exit', 'default', /* @lang JavaScript */ "Base.Common.Query.Send('/users/exit', () => location.reload()); return false;");
		}

	}

	Users::RegActions();