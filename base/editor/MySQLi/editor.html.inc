<?php

	namespace Base\EditorMySQLi\HTML;

	require DIR_BASE . 'editor/editor.html.inc';

	use Base\DB\TableMySQLi;
	use Base\DB\MySQLiQuery;

	abstract class Editor extends \Base\Editor\HTML\Editor {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->querySelect = MySQLiQuery::select();
		}

	}