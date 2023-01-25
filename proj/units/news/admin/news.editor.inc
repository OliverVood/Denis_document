<?php

	namespace Proj\Admin\Editor;

	use Base\Editor\EditorMySQLi;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;

	class News extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			$params = [
				'titles' => [
					'select' => 'Список новостей',
					'create' => 'Добавить новость',
					'update' => 'Редактирование новости'
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
					'state' => ['skin' => 'hidden', 'name' => 'Состояние', 'default' => Consts\News::STATES['draft']],
					'header' => ['skin' => 'text', 'name' => 'Заголовок', 'default' => ''],
					'content' => ['skin' => 'textarea', 'name' => 'Текст', 'default' => '']
				],
				'update' => [
					'state' => ['skin' => 'select', 'name' => 'Состояние'],
					'header' => ['skin' => 'text', 'name' => 'Заголовок'],
					'content' => ['skin' => 'textarea', 'name' => 'Текст']
				]
			];

			parent::__construct($name, $table, $params);
		}

		public function PrepareOnUpdate(int $id, array &$item, array &$data) : void {
			$data['state'] = [
				Consts\News::STATE_DRAFT	=> 'Черновик',
				Consts\News::STATE_ACTIVE	=> 'Активная',
				Consts\News::STATE_INACTIVE	=> 'Не активная',
			];
		}

	}