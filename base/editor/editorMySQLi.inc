<?php

	namespace Proj\Admin\Editors;

	use Base\Editor;
	use Base\DB\TableMySQLi;

	class EditorMySQLi extends Editor {

		public function __construct(string $name, TableMySQLi $table, array $params = []) {
			parent::__construct($name, $table, $params);
		}

	}