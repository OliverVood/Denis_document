<?php

	namespace Base\DB;

	use Base\DB;

	class FieldEnumMySQLi extends DB\FieldMySQLi {
		private array $enum;

		public function __construct(string $name, array $enum, TableMySQLi $table) {
			parent::__construct('enum', $name, $table);

			$this->enum = $enum;
		}

		public function Check(?array $old) { echo "Проверка поля <b>`{$this->name}`</b><br>"; }
		public function Make() { echo "Make field $this->type<br>"; }

	}