<?php

	namespace Proj\Admin\Units;

	require 'news.structure.inc';
	require 'news.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;
	use Base\Editor\EditorMySQLi;

	class News extends Structure\News {
		use Instance;

		private EditorMySQLi $editor_news;

		private Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_news = new \Proj\Admin\Editor\News(self::NAME, $this->table_news);

			$this->out_menu = new Action();

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::object()->ToVar('Новости', [
					$this->editor_news->select->GetLink('Список новостей'),
					$this->editor_news->create->GetLink('Добавить новость'),
				])
			);
		}

	}

	News::init();