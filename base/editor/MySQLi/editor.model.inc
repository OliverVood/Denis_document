<?php

	namespace Base\EditorMySQLi;

	use Base\DB\TableMySQLi;

	class Model extends \Base\Editor\Model {
		public function __construct(TableMySQLi $table, array $params = []) {
			parent::__construct($table, $params);
		}

	}