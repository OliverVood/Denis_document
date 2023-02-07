<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'news/consts.inc';
	require DIR_UNITS . 'news/site/views/Last.inc';
	require DIR_UNITS . 'news/site/views/Show.inc';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\News\Last;
	use Proj\Site\Templates\News\Show;

	class News extends Units implements Consts\News {
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
			$this->show = new Action(self::NAME, 'show', "/news/show?id=%id%");

			Controller::instance()->view->Push($this->last, [$this, 'OnViewLast']);
			Controller::instance()->view->Push($this->list, [$this, 'OnViewList']);
			Controller::instance()->view->Push($this->show, [$this, 'OnViewShow']);
		}

		public function OnViewShow() {
			Layout::instance()->main->Push($this->ViewShow(GetInt('id')));
		}

		public function OnViewLast() {
			$limit = 3;

			Layout::instance()->main->Push($this->ViewLast($limit, 'Последние новости'));
		}

		public function OnViewList() {
			$limit = null;

			Layout::instance()->main->Push($this->ViewLast($limit, 'Все новости'));
		}

		private function ViewLast(?int $limit, $title): string {
			$state = self::STATES['active'];

			$result = $this->db->Select(self::TABLES['news'], ['id', 'datecr', 'header', 'content'], "(`state` = {$state}) AND (`datepb` < NOW())", '`datepb` DESC, `id`', $limit, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);
			$items = $this->db->FetchAll($result);

			return Last::object()->ToVar($items, $title);
		}

		private function ViewShow(int $id): string {
			$data = $this->db->SelectOne(self::TABLES['news'], ['id', 'datecr', 'header', 'content', 'datepb'], "`id` = {$id}", null, null, ["CONCAT(`hash`, '.', `id`, '.', `ext`) AS `cover`"]);

			return Show::object()->ToVar($data);
		}

	}

	News::init();