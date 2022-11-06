<?php

	namespace Base\DB;

	use Base\DB;

	class FieldIDMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('id', $name, $table);
		}

		static protected function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';
			if (strripos($data['EXTRA'], 'auto_increment') !== false) $pieces['ai'] =  'AUTO_INCREMENT';

			return implode(' ', $pieces);
		}

		public function CreationFormat(): string { return "`{$this->name}` int unsigned NOT NULL AUTO_INCREMENT"; }
		public function UpdateFormat(): string { return "`{$this->name}` int unsigned PRIMARY KEY NOT NULL AUTO_INCREMENT"; }

	}