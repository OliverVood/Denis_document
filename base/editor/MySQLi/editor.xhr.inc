<?php

	namespace Base\EditorMySQLi\XHR;

	require DIR_BASE . 'editor/editor.xhr.inc';

	use Base\DB\TableMySQLi;
	use Base\DB\MySQLiQuery;

	abstract class Editor extends \Base\Editor\XHR\Editor {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->querySelect = MySQLiQuery::select();
		}

	}