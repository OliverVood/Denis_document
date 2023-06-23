<?php

	namespace Base\EditorMySQLi;

	use Base\DB\MySQLi\Table;

	class Model extends \Base\Editor\Model {
		public function __construct(Table $table, array $params = []) {
			parent::__construct($table, $params);
		}

	}