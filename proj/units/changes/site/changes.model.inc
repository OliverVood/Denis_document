<?php

	namespace Proj\Site\Model;

	use Base\Model;
	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DBQuery;

	class Changes extends Model {
		use Instance;

		private DBQuery $db;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->db = DBQuery::instance();
		}

		public function GetLatestChanges(?int $count = null): array {
			$state = Consts\Changes::STATES['active'];

			$result = $this->db->Select(Consts\Changes::TABLES['changes'], ['id', 'header'], "(`state` = {$state}) AND (`datepb` < NOW())", '`datepb` DESC, `id`', $count);
			return $this->db->FetchAll($result);
		}

		public function GetChanges(int $id): array | null {
			$state = Consts\Changes::STATES['active'];

			return $this->db->SelectOne(Consts\Changes::TABLES['changes'], ['id', 'header', 'datepb'], "(`state` = {$state}) AND (`datepb` < NOW()) AND (`id` = {$id})");
		}

		public function GetListChange(int $id): array {
			$state = Consts\Changes::STATES['active'];

			$result = $this->db->Select(Consts\Changes::TABLES['change'], ['header', 'content'], "(`state` = {$state}) AND (`cid` = {$id})", '`id`', null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);
			return $this->db->FetchAll($result);
		}

	}

	Changes::init();