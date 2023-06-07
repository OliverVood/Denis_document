<?php

	namespace Proj\Admin\Units\HTML;

	require DIR_UNITS . 'news/admin/news.structure.inc';
	require DIR_UNITS . 'news/admin/editors/news/news.editor.html.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;
	use Proj\Admin\Editor\HTML as Editor;
	use Closure;

	class News extends Structure\News {
		use Instance;

		public Editor\News $editor_news;

		private function __construct() {
			parent::__construct();

			self::$view->Push(self::$out_menu, Closure::fromCallable([$this, 'OutMenu']));

			$this->editor_news = new Editor\News(self::NAME, $this->table_news);
		}

		private function OutMenu() {
			Layout::instance()->menu->Push(
				Group::ToVar('Новости', [
					$this->editor_news->select->GetLinkHref('Список новостей', ['page' => 1]),
					$this->editor_news->create->GetLinkHref('Добавить новость')
				])
			);
		}

	}

	News::init();