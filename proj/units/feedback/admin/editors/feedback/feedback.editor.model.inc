<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\Select;
	use Base\EditorMySQLi\Model;
	use Proj\Units\Consts;

	class Feedback extends Model {
		public function __construct(Table $table) {
			parent::__construct($table);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc('*')
				->table($this->table->GetName())
				->where('`state` != '. Consts\Feedback::STATES['delete'])
				->order('datecr', 'DESC')
				->order('id');

			$this->states = [
				Consts\Feedback::STATE_NEW => [
					Consts\Feedback::STATE_DONE
				]
			];
		}

	}