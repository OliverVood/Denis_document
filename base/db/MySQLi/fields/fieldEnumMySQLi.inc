<?php

	namespace Base\DB;

	use Base\DB;

	class FieldEnumMySQLi extends DB\FieldMySQLi {
		private array $enum;

		public function __construct(string $name, array $enum, TableMySQLi $table) {
			parent::__construct('enum', $name, $table);

			$this->enum = $enum;
		}

		protected function CreationFormat(): string { return "`{$this->name}` enum('" . implode("','", $this->enum) . "') NOT NULL"; }

	}