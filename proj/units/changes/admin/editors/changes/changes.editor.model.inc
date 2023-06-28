<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;
	use Base\Editor\MySQLi\Model;
	use Proj\Units\Consts;

	class Changes extends Model {
		public function __construct(Table $table) {
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