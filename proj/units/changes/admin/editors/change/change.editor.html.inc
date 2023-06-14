<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'changes/admin/editors/change/change.editor.common.inc';
	require DIR_UNITS . 'changes/admin/editors/change/change.editor.model.inc';

	use Base\EditorMySQLi\HTML\Editor;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Common;
	use Proj\Admin\Editor\Model;

	class Change extends Editor {
		use Common\Change;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name);

			$this->Init();

			$this->model = new Model\Change($table, $this->params);
		}

	}