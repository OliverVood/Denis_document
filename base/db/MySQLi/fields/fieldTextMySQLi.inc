<?php

	namespace Base\DB;

	use Base\DB;

	class FieldTextMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('text', $name, $table);
		}

		static protected function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';

			return implode(' ', $pieces);
		}

		public function CreationFormat(): string { return "`{$this->name}` text NOT NULL"; }

	}