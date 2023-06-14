<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'news/admin/editors/news/news.editor.common.inc';
	require DIR_UNITS . 'news/admin/editors/news/news.editor.model.inc';

	use Base\EditorMySQLi\HTML\Editor;;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Common;
	use Proj\Admin\Editor\Model;

	class News extends Editor {
		use Common\News;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name);

			$this->Init();

			$this->model = new Model\News($table, $this->params);
		}

	}