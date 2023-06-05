<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'news/admin/editors/news/news.editor.model.inc';

	use Base\Editor\HTML\EditorMySQLi;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Model;

	class News extends EditorMySQLi {
		use Model\News;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();
		}

	}