<?php

	namespace Base\DB;

	use Base\DB;

	class FieldSetMySQLi extends DB\FieldMySQLi {
		private array $set;

		public function __construct(string $name, array $set, TableMySQLi $table) {
			parent::__construct('set', $name, $table);

			$this->set = $set;
		}

		public function Check(?array $old) { echo "Проверка поля <b>`{$this->name}`</b><br>"; }
		public function Make() { echo "Make field $this->type<br>"; }

	}