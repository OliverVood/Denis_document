<?php

	namespace Base\DB;

	use Base\DB;

	class FieldIDMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('id', $name, $table);
		}

		static protected function DataToCreationFormat($date): string {
			$pieces = [];
			$pieces['name'] = "`{$date['Field']}`";
			$pieces['type'] = $date['Type'];
			$pieces['null'] = ($date['Null'] === 'YES') ? 'NULL' : 'NOT NULL';
			if (strripos($date['Extra'], 'auto_increment') !== false) $pieces['ai'] =  'AUTO_INCREMENT';

			return implode(' ', $pieces);
		}

		protected function CreationFormat(): string { return "`{$this->name}` int unsigned NOT NULL AUTO_INCREMENT"; }

	}