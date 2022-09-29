<?php

	namespace Base\DB;

	use Base\DB;

	class FieldStringMySQLi extends DB\FieldMySQLi {
		private int $length;

		public function __construct(string $name, int $length, TableMySQLi $table) {
			parent::__construct('enum', $name, $table);

			$this->length = $length;
		}

		public function Check(?array $old) { echo "Проверка поля <b>`{$this->name}`</b><br>"; }
		public function Make() { echo "Make field $this->type<br>"; }

	}