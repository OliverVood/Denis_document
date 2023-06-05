<?php

	namespace Proj\Admin\Units\XHR;

	require DIR_UNITS . 'news/admin/news.structure.inc';
	require DIR_UNITS . 'news/admin/editors/news/news.editor.xhr.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor\XHR as Editor;

	class News extends Structure\News {
		use Instance;

		public Editor\News $editor_news;

		private function __construct() {
			parent::__construct();

			$this->editor_news = new Editor\News(self::NAME, $this->table_news);
		}

	}

	News::init();