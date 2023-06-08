<?php

	namespace Proj\Admin\Editor\XHR;

	require DIR_UNITS . 'statistics/admin/editors/actions/actions.editor.model.inc';

	use Base\EditorMySQLi\XHR\Editor;;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Model;

	class Actions extends Editor {
		use Model\Actions;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();
		}

	}