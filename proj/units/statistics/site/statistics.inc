<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'statistics/consts.inc';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use JetBrains\PhpStorm\NoReturn;
	use Proj\Units\Consts;
	use Proj\DBQuery;

	class Statistics extends Units implements Consts\Statistics {
		use Instance;

		public Action $collect;
		public Action $act;

		private DBQuery $db;

		private static string | null $uid = null;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->collect = new Action('always', 'always');
			$this->act = new Action(self::NAME, 'act', 'default');

			Controller::instance()->void->Push($this->collect, [$this, 'Collect']);
			Controller::instance()->view->Push($this->act, [$this, 'DoAct']);
		}

		public function Collect(): void {
			if (Controller::$area == 'statistics') return;

			$ip = GetUserIP();
			$ipv6 = ip2long($ip);
			$parts = explode('.', $ip);
			$uri = explode('?', $_SERVER['REQUEST_URI']);

			$this->db->Insert(self::TABLES['ip'], [
				'uid' 			=> Users::GetUID(),
				'ip'			=> $ipv6,
				'ip_part_I' 	=> $parts[0] ?? 0,
				'ip_part_II' 	=> $parts[1] ?? 0,
				'ip_part_III' 	=> $parts[2] ?? 0,
				'ip_part_IV' 	=> $parts[3] ?? 0,
				'path' 			=> $uri[0],
				'params' 		=> $uri[1] ?? '',
			]);
		}

		#[NoReturn] public function DoAct(): void {
			$uid = Users::GetUID();
			$object = GetParam('object', '');
			$action = GetParam('action', '');
			$params = GetParam('params', '');

			$this->db->Insert(self::TABLES['act'], [
				'uid' => $uid,
				'object' => $object,
				'action' => $action,
				'params' => $params ? json_encode($params, JSON_UNESCAPED_UNICODE) : ''
			]);

			SendJSONSuccess(null);
		}

	}

	Statistics::init();