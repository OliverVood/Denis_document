<?php

	namespace Base\Editor\MySQLi;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;

	class Model extends \Base\Editor\Model {
		protected Select $querySelect;

		public function __construct(Table $table, array $params = []) {
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			parent::Init();

			$this->querySelect = new Select();
			$this->querySelect->calc('*')->table($this->table->GetName());
		}

	}