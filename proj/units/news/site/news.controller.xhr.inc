<?php

	namespace Proj\Site\Units\XHR;

	require DIR_UNITS . 'news/site/news.actions.inc';

	use Base\Instance;
	use Proj\Site\Actions;

	class News extends Actions\News {
		use Instance;

		private function __construct() {
			parent::__construct();
		}

	}

	News::init();