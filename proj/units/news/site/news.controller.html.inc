<?php

	namespace Proj\Site\Units\HTML;

	require DIR_UNITS . 'news/site/news.actions.inc';
	require DIR_UNITS . 'news/site/news.model.inc';
	require DIR_UNITS . 'news/site/views/Last.tpl';
	require DIR_UNITS . 'news/site/views/Show.tpl';
	require DIR_UNITS . 'news/site/views/All.tpl';

	use Base\Instance;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\News as TPL;

	class News extends Actions\News {
		use Instance;

		private Model\News $model;

		private function __construct() {
			parent::__construct();

			$this->model = Model\News::instance();

			self::$view->Push(self::$last, [$this, 'OnViewLast']);
			self::$view->Push(self::$all, [$this, 'OnViewAll']);
			self::$view->Push(self::$show, [$this, 'OnViewShow']);
		}

		public function OnViewShow() {
			$id = GetInt('id');
			Layout::instance()->main->Push(TPL\Show::ToVar($this->model->GetNews($id)));
		}

		public function OnViewLast() {
			Layout::instance()->main->Push(TPL\Last::ToVar($this->model->GetLastNews(3), 'Последние новости'));
		}

		public function OnViewAll() {
			Layout::instance()->main->Push(TPL\All::ToVar($this->model->GetLastNews(null), 'Все новости'));
		}

	}

	News::init();