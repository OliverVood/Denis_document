<?php

	namespace Proj\Admin\Editor\XHR;

	require DIR_UNITS . 'changes/admin/editors/change/change.editor.common.inc';
	require DIR_UNITS . 'changes/admin/editors/change/change.editor.model.inc';

	use Base\EditorMySQLi\XHR\Editor;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Common;
	use Proj\Admin\Editor\Model;

	class Change extends Editor {
		use Common\Change;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name);

			$this->Init();

			$this->titleDoCreate = 'Актуальное добавлено';
			$this->titleDoUpdate = 'Актуальное изменено';
			$this->titleDoDelete = 'Актуальное удалено';

			$this->model = new Model\Change($table, $this->params);
		}

	}