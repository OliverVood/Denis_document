<?php

	namespace Proj\Site\Units;

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
			parent::__construct(__FILE__);

			$this->model = Model\News::instance();
		}

		#region HTML

		public function OnViewShow() {
			$id = GetInt('id');
			Layout::instance()->main->Push(TPL\Show::ToVar($this->model->GetNews($id)));
		}

		public function OnViewAll() {
			Layout::instance()->main->Push(TPL\All::ToVar($this->model->GetLastNews(), 'Все новости'));
		}

		#endregion HTML

		public function GetViewLast(?int $count = null): string {
			return TPL\Last::ToVar($this->model->GetLastNews($count), 'Последние новости');
		}

	}

	News::init();