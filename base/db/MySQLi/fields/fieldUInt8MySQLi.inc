<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt8MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('uint8', $name, $table);
		}

		public function Check(?array $old) { echo "Проверка поля <b>`{$this->name}`</b><br>"; }
		public function Make() { echo "Make field $this->type<br>"; }

	}