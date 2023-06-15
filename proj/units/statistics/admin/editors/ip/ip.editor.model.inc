<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\Select;
	use Base\DB\Table;
	use Base\EditorMySQLi\Model;

	class Ip extends Model {
		public function __construct(Table $table, array $params = []) {
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