<?php

	namespace Base\DB;

	use Base\DB;

	class FieldBoolMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('bool', $name, $table);
		}

		static protected function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['Field']}`";
			$pieces['type'] = $data['Type'];
			$pieces['null'] = ($data['Null'] === 'YES') ? 'NULL' : 'NOT NULL';
			$pieces['default'] = "DEFAULT '{$data['Default']}'";

			return implode(' ', $pieces);
		}

		protected function CreationFormat(): string { return "`{$this->name}` tinyint(1) NOT NULL DEFAULT '0'"; }

	}