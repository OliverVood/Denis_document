<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'users/consts.inc';

	use Base\Units;
	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DB;

	class Users extends Units implements Consts\Users {
		use Instance;

		private DB $db;

		private static string | null $uid = null;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DB::instance();

			$this->Identification();
		}

		private function Identification() {
			if (!isset($_SESSION['USERS']['UID'])) $_SESSION['USERS']['UID'] = $this->db->Insert(self::TABLES['users'], ['fic' => 1]);
			self::$uid = $_SESSION['USERS']['UID'];
		}

		public static function GetUID(): int {
			return self::$uid;
		}

	}

	Users::init();