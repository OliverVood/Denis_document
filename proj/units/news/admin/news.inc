<?php

	namespace Proj\Admin\Units;

	require 'news.structure.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;
	use Proj\Admin\Editors\EditorMySQLi;

	class News extends Structure\News {
		use Instance;

		private EditorMySQLi $editor_news;

		private Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_news = new EditorMySQLi(self::NAME, $this->table_news, [
				'titles' => [
					'select' => 'Список новостей',
					'create' => 'Добавить новость'
				],
				'order' => [
					'`datecr` DESC',
					'`id` ASC'
				],
				'select' => [
					'id' => '#',
					'state' => 'Состояние',
					'datecr' => 'Дата создания',
					'header' => 'Заголовок'
				],
				'create' => [
					'state' => [
						'skin' => 'hidden',
						'name' => 'Состояние',
						'value' => self::STATES['draft']
					],
					'header' => [
						'skin' => 'text',
						'name' => 'Заголовок',
						'value' => ''
					],
					'content' => [
						'skin' => 'textarea',
						'name' => 'Текст',
						'value' => ''
					]
				],
				'update' => [
					'state' => [
						'skin' => 'select',
						'name' => 'Состояние',
						'value' => self::STATES['draft']
					],
					'header' => [
						'skin' => 'text',
						'name' => 'Заголовок',
						'value' => ''
					],
					'content' => [
						'skin' => 'textarea',
						'name' => 'Текст',
						'value' => ''
					]
				]
			]);

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