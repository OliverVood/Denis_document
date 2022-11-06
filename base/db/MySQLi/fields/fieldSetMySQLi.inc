<?php

	namespace Base\DB;

	use Base\DB;

	class FieldSetMySQLi extends DB\FieldMySQLi {
		private array $set;

		public function __construct(string $name, array $set, TableMySQLi $table) {
			parent::__construct('set', $name, $table);

			$this->set = $set;
		}

		static protected function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';

			return implode(' ', $pieces);
		}

		public function CreationFormat(): string { return "`{$this->name}` set('" . implode("','", $this->set) . "') NOT NULL"; }

	}