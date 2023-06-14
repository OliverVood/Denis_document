<?php

	namespace Proj\Admin\Editor\XHR;

	require DIR_UNITS . 'news/admin/editors/news/news.editor.common.inc';
	require DIR_UNITS . 'news/admin/editors/news/news.editor.model.inc';

	use Base\EditorMySQLi\XHR\Editor;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Common;
	use Proj\Admin\Editor\Model;

	class News extends Editor {
		use Common\News;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name);

			$this->Init();

			$this->titleDoCreate = 'Новость добавлена';
			$this->titleDoUpdate = 'Новость изменена';
			$this->titleDoDelete = 'Новость удалена';

			$this->model = new Model\News($table, $this->params);
		}

	}