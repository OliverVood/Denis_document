<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'news/news.consts.inc';
	require DIR_UNITS . 'news/site/views/Last.tpl';
	require DIR_UNITS . 'news/site/views/Show.tpl';
	require DIR_UNITS . 'news/site/views/All.tpl';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\News\Last;
	use Proj\Site\Templates\News\Show;
	use Proj\Site\Templates\News\All;

	class News extends Units implements Consts\News {
		use Instance;

		private DBQuery $db;

		public Action $last;
		public Action $all;
		public Action $show;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->last = new Action('null', 'null');
			$this->all = new Action(self::NAME, 'null', 'default');
			$this->show = new Action(self::NAME, 'show', "/news/show?id=%id%");

			self::$view->Push($this->last, [$this, 'OnViewLast']);
			self::$view->Push($this->all, [$this, 'OnViewAll']);
			self::$view->Push($this->show, [$this, 'OnViewShow']);
		}

		public function OnViewShow() {
			Layout::instance()->main->Push($this->ViewShow(GetInt('id')));
		}

		public function OnViewLast() {
			$limit = 3;

			Layout::instance()->main->Push($this->ViewLast($limit, 'Последние новости'));
		}

		public function OnViewAll() {
			$limit = null;

			Layout::instance()->main->Push($this->ViewAll($limit, 'Все новости'));
		}

		private function ViewLast(?int $limit, $title): string {
			$state = self::STATES['active'];

			$result = $this->db->Select(self::TABLES['news'], ['id', 'datecr', 'header', 'content'], "(`state` = {$state}) AND (`datepb` < NOW())", '`datepb` DESC, `id`', $limit, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);
			$items = $this->db->FetchAll($result);

			return Last::ToVar($items, $title);
		}

		private function ViewAll(?int $limit, $title): string {
			$state = self::STATES['active'];

			$result = $this->db->Select(self::TABLES['news'], ['id', 'datecr', 'header', 'content'], "(`state` = {$state}) AND (`datepb` < NOW())", '`datepb` DESC, `id`', $limit, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);
			$items = $this->db->FetchAll($result);

			return All::ToVar($items, $title);
		}

		private function ViewShow(int $id): string {
			$state = self::STATES['active'];

			$data = $this->db->SelectOne(self::TABLES['news'], ['id', 'datecr', 'header', 'content', 'datepb'], "(`state` = {$state}) AND (`datepb` < NOW()) AND (`id` = {$id})", null, null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);

			return Show::ToVar($data);
		}

	}

	News::init();