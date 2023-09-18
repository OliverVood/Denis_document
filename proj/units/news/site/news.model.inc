<?php

	namespace Proj\Site\Model;

	use Base\Model;
	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\DBQuery;

	class News extends Model {
		use Instance;

		private DBQuery $db;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->db = DBQuery::instance();
		}

		public function GetLastNews(?int $count): array {
			$state = Consts\News::STATES['active'];

			$result = $this->db->Select(Consts\News::TABLES['news'], ['id', 'datecr', 'header', 'content'], "(`state` = {$state}) AND (`datepb` < NOW())", '`datepb` DESC, `id`', $count, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);
			return $this->db->FetchAll($result);
		}

		public function GetNews(int $id): array | null {
			$state = Consts\News::STATES['active'];

			return $this->db->SelectOne(Consts\News::TABLES['news'], ['id', 'datecr', 'header', 'content', 'datepb'], "(`state` = {$state}) AND (`datepb` < NOW()) AND (`id` = {$id})", null, null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);
		}

	}

	News::init();