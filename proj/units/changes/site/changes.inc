<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'changes/consts.inc';
	require DIR_UNITS . 'changes/site/views/Last.tpl';
	require DIR_UNITS . 'changes/site/views/All.tpl';
	require DIR_UNITS . 'changes/site/views/Show.tpl';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Changes\Last;
	use Proj\Site\Templates\Changes\Show;
	use Proj\Site\Templates\Changes\All;

	class Changes extends Units implements Consts\Changes {
		use Instance;

		private DBQuery $db;

		public Action $last;
		public Action $list;
		public Action $show;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->last = new Action('null', 'null');
			$this->list = new Action(self::NAME, 'null', 'default');
			$this->show = new Action(self::NAME, 'show', "/changes/show?id=%id%");

			Controller::instance()->view->Push($this->last, [$this, 'OnViewLast']);
			Controller::instance()->view->Push($this->list, [$this, 'OnViewList']);
			Controller::instance()->view->Push($this->show, [$this, 'OnViewShow']);
		}

		public function OnViewShow() {
			Layout::instance()->main->Push($this->ViewShow(GetInt('id')));
		}

		public function OnViewLast() {
			$limit = 4;

			Layout::instance()->main->Push($this->ViewLast($limit, 'Последние изменения на сайте'));
		}

		public function OnViewList() {
			$limit = null;

			Layout::instance()->main->Push($this->ViewList($limit, 'Все изменения'));
		}

		private function ViewLast(?int $limit, $title): string {
			$state = self::STATES['active'];

			$result = $this->db->Select(self::TABLES['changes'], ['id', 'header'], "(`state` = {$state}) AND (`datepb` < NOW())", '`datepb` DESC, `id`', $limit);
			$items = $this->db->FetchAll($result);

			return Last::object()->ToVar($items, $title);
		}

		private function ViewList(?int $limit, $title): string {
			$state = self::STATES['active'];

			$result = $this->db->Select(self::TABLES['changes'], ['id', 'header'], "(`state` = {$state}) AND (`datepb` < NOW())", '`datepb` DESC, `id`', $limit);
			$items = $this->db->FetchAll($result);

			return All::object()->ToVar($items, $title);
		}

		private function ViewShow(int $id): string {
			$state = self::STATES['active'];

			$data = $this->db->SelectOne(self::TABLES['changes'], ['id', 'header', 'datepb'], "(`state` = {$state}) AND (`datepb` < NOW()) AND (`id` = {$id})");
			if (!$data) return '';
			$result = $this->db->Select(self::TABLES['change'], ['header', 'content'], "(`state` = {$state}) AND (`cid` = {$id})", '`id`', null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);
			$list_change = $this->db->FetchAll($result);
			return Show::object()->ToVar($data, $list_change);
		}

	}

	Changes::init();