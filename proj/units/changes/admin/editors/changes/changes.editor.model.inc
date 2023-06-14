<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\Select;
	use Base\DB\TableMySQLi;
	use Base\EditorMySQLi\Model;
	use Proj\Units\Consts;

	class Changes extends Model {
		public function __construct(TableMySQLi $table) {
			parent::__construct($table);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc('*')
				->table($this->table->GetName())
				->where('`state` != ' . Consts\Changes::STATE_DELETE)
				->order('datecr', 'DESC')
				->order('id');
		}

	}