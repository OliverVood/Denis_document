<?php

	namespace Base\DB;

	use Base\DB;

	class FieldEnumMySQLi extends DB\FieldMySQLi {
		private array $enum;

		public function __construct(string $name, array $enum, TableMySQLi $table) {
			parent::__construct('enum', $name, $table);

			$this->enum = $enum;
		}

		static protected function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';

			return implode(' ', $pieces);
		}

		public function CreationFormat(): string { return "`{$this->name}` enum('" . implode("','", $this->enum) . "') NOT NULL"; }

	}