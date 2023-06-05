<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'statistics/admin/editors/actions/actions.editor.model.inc';

	use Base\Editor\HTML\EditorMySQLi;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Model;

	class Actions extends EditorMySQLi {
		use Model\Actions;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();
		}

	}