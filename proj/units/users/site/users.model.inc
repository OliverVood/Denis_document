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

		private function Identification(): void {
			switch (isset($_SESSION['USERS']['UID'])) {
				case true:
					self::$uid = $_SESSION['USERS']['UID'];
					break;
				case false:
					if (isset($_COOKIE['USERS_HASH'])) {
						$user_hash = $this->db->Escaping($_COOKIE['USERS_HASH']);
						$user = $this->db->SelectOne(Consts\Users::TABLES['users'], ['hash', 'id'], "`hash` = '$user_hash'");
						if ($user && $_COOKIE['USERS_HASH'] === $user['hash']) {
							self::$uid = $user['id'];
						}
					}
					break;
			}

			$hash = bin2hex(random_bytes(32));

			if (self::$uid) $this->db->Update(Consts\Users::TABLES['users'], ['hash' => $hash], '`id` = ' . self::$uid);
			else self::$uid = $this->db->Insert(Consts\Users::TABLES['users'], ['fic' => 1, 'hash' => $hash]);

			$_SESSION['USERS']['UID'] = self::$uid;
			setcookie('USERS_HASH', $hash, time() + 86400000, '/');
		}

		public static function GetUID(): int {
			return self::$uid;
		}

	}

	Users::init();