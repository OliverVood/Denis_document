<?php

	namespace Base\Editor\XHR;

	require DIR_BASE . 'editor/editor.xhr.inc';

	use Base\DB\TableMySQLi;
	use Base\DB\MySQLiQuery;

	abstract class EditorMySQLi extends Editor {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->querySelect = MySQLiQuery::select();
		}

	}