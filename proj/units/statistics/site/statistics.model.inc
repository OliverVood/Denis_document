<?php

	namespace Proj\Site\Model;

	use Base\Model;
	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DBQuery;

	class Statistics extends Model {
		use Instance;

		private DBQuery $db;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->db = DBQuery::instance();
		}

		public function Collect(): void {
			$ip = GetUserIP();
			$ipv6 = ip2long($ip);
			$uri = explode('?', $_SERVER['REQUEST_URI']);

			$this->db->Insert(Consts\Statistics::TABLES['ip'], [
				'cid' 			=> Users::GetCID(),
				'ip'			=> $ipv6,
				'path' 			=> $uri[0],
				'params' 		=> $uri[1] ?? '',
			]);
		}

		public function InsertAct($uid, $object, $action, $params): void {
			$this->db->Insert(Consts\Statistics::TABLES['act'], [
				'cid' => $uid,
				'object' => $object,
				'action' => $action,
				'params' => $params ? json_encode($params, JSON_UNESCAPED_UNICODE) : ''
			]);
		}

	}

	Statistics::init();