<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'statistics/admin/editors/actions/actions.editor.common.inc';
	require DIR_UNITS . 'statistics/admin/editors/actions/actions.editor.model.inc';

	use Base\EditorMySQLi\HTML\Editor;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Common;
	use Proj\Admin\Editor\Model;

	class Actions extends Editor {
		use Common\Actions;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name);

			$this->Init();

			$this->model = new Model\Actions($table, $this->params);
		}

	}