<?php

	namespace Proj\Site\Model;

	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DBQuery;

	class Users {
		use Instance;

		private DBQuery $db;

		private static string | null $uid = null;

		private function __construct() {
			$this->db = DBQuery::instance();

			$this->Identification();
		}

		private function Identification(): void {//TODO запомнить пользователя
//			$hash = bin2hex(random_bytes(16));
			if (!isset($_SESSION['USERS']['UID'])) $_SESSION['USERS']['UID'] = $this->db->Insert(Consts\Users::TABLES['users'], ['fic' => 1]);
			self::$uid = $_SESSION['USERS']['UID'];
		}

		public static function GetUID(): int {
			return self::$uid;
		}

	}

	Users::init();