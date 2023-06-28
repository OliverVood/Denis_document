<?php

	namespace Proj\Admin\Editor\XHR;

	require DIR_UNITS . 'changes/admin/editors/change/change.editor.common.inc';
	require DIR_UNITS . 'changes/admin/editors/change/change.editor.model.inc';

	use Base\Editor\MySQLi\XHR\Editor;
	use Base\DB\MySQLi\Table;
	use Proj\Admin\Editor\Common;
	use Proj\Admin\Editor\Model;

	class Change extends Editor {
		use Common\Change;

		public function __construct(string $name, Table $table) {
			parent::__construct($name);

			$this->Init();

			$this->titleDoCreate = 'Актуальное добавлено';
			$this->titleDoUpdate = 'Актуальное изменено';
			$this->titleDoDelete = 'Актуальное удалено';

			$this->model = new Model\Change($table, $this->params);
		}

	}