<?php

	namespace Base\Editor\HTML;

	require DIR_BASE . 'editor/editor.html.inc';

	use Base\DB\TableMySQLi;
	use Base\DB\MySQLiQuery;

	abstract class EditorMySQLi extends Editor {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->querySelect = MySQLiQuery::select();
		}

	}