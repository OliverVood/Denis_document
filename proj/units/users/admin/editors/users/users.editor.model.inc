<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;
	use Base\Editor\MySQLi\Model;
	use Proj\Units\Consts;

	class Users extends Model {
		public function __construct(Table $table, array $params = []) {
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc('*')
				->table($this->table->GetName())
				->where('`state` != '. Consts\Users::STATE_USER_DELETE)
				->order('datecr', 'DESC')
				->order('id', 'DESC');
		}

		protected function PrepareCreate(array & $data, array & $params = []): void {
			$data['password'] = \Proj\Admin\Model\Users::instance()->PasswordHash($data['password']);
		}

		protected function PrepareUpdate(array & $data, int $id): void {
			$data['password'] = \Proj\Admin\Model\Users::instance()->PasswordHash($data['password']);
		}

	}