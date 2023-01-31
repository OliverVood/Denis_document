<?php

	namespace Proj\Admin\Editor;

//	use JetBrains\PhpStorm\NoReturn;

	use Base\Editor\EditorMySQLi;
	use Base\DB\TableMySQLi;
//	use Proj\Units\Consts;

	class Opportunities extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			$params = [
				'where' => [
					'state != 100'
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
			];

			parent::__construct($name, $table, $params);

			$this->titleSelect = 'Список новых возможностей';
			$this->titleCreate = 'Добавить новую возможность';
			$this->titleUpdate = 'Редактирование новой возможности';

			$this->titleDoCreate = 'Новая возможность добавлена';
			$this->titleDoUpdate = 'Новая возможность изменена';
		}

	}