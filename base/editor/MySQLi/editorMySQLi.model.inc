<?php

	namespace Base\EditorMySQLi;

	use Base\DB\TableMySQLi;

	class Model extends \Base\Editor\Model {

		public function __construct(TableMySQLi $table) {
			parent::__construct($table);
		}

	}