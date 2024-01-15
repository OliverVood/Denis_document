<?php

	namespace Proj\Site\Model;

	use Base\Model;
	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DBQuery;

	class Users extends Model {
		use Instance;

		private DBQuery $db;

		private static string | null $cid = null;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->db = DBQuery::instance();

			$this->Identification();
		}

		private function Identification(): void {
			switch (isset($_SESSION['CLIENT']['CID'])) {
				case true:
					self::$cid = $_SESSION['CLIENT']['CID'];
					break;
				case false:
					if (isset($_COOKIE['CLIENT_HASH'])) {
						$client_hash = $this->db->Escaping($_COOKIE['CLIENT_HASH']);
						$client = $this->db->SelectOne(Consts\Users::TABLES['clients'], ['hash', 'id'], "`hash` = '$client_hash'");
						if ($client && $_COOKIE['CLIENT_HASH'] === $client['hash']) {
							self::$cid = $client['id'];
						}
					}
					break;
			}

			$hash = bin2hex(random_bytes(32));

			if (self::$cid) $this->db->Update(Consts\Users::TABLES['clients'], ['hash' => $hash], '`id` = ' . self::$cid);
			else self::$cid = $this->db->Insert(Consts\Users::TABLES['clients'], ['hash' => $hash]);

			$_SESSION['CLIENT']['CID'] = self::$cid;
			setcookie('CLIENT_HASH', $hash, time() + 86400000, '/');
		}

		public static function GetCID(): int {
			return self::$cid;
		}

	}

	Users::init();