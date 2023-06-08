<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'news/admin/editors/news/news.editor.model.inc';

	use Base\EditorMySQLi\HTML\Editor;;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Model;

	class News extends Editor {
		use Model\News;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();
		}

	}