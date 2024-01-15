<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'news/admin/news.structure.inc';

	require DIR_UNITS . 'news/admin/editors/news/news.editor.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor;
	use Proj\Editor\Consts as EditorConsts;

	class News extends Structure\News {
		use Instance;

		public Editor\News $editor_news;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->editor_news = new Editor\News(EditorConsts\ID_NEWS, self::NAME, $this->table_news, 'Новости (редактор)');
		}

		public function GetMenu(): array {
			$out = [];
			if ($this->editor_news->Allow($this->editor_news::ACCESS_SELECT)) $out[] =  $this->editor_news->select->GetLinkHref('Список новостей', ['page' => 1]);
			if ($this->editor_news->Allow($this->editor_news::ACCESS_CREATE)) $out[] = $this->editor_news->create->GetLinkHref('Добавить новость');

			return $out;
		}

	}

	News::init();