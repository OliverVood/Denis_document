<?php

	namespace Base\Editor;

	use Base\DB\TableMySQLi;

	abstract class EditorMySQLi extends Editor {

		public function __construct(string $name, TableMySQLi $table, array $params = []) {
			parent::__construct($name, $table, $params);
		}

	}