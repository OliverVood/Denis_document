<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\Select;
	use Base\DB\TableMySQLi;
	use Base\EditorMySQLi\Model;

	class Actions extends Model {
		public function __construct(TableMySQLi $table, array $params = []) {
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc('*')
				->table($this->table->GetName())
				->order('datecr', 'DESC')
				->order('id', 'DESC');
		}

	}