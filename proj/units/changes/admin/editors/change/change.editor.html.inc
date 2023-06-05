<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'changes/admin/editors/change/change.editor.model.inc';

	use Base\Editor\HTML\EditorMySQLi;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Model;

	class Change extends EditorMySQLi {
		use Model\Change;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();
		}

	}