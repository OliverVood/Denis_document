<?php

	namespace Base\DB\MySQLi;

	class FieldID extends Field {
		public function __construct(string $name, Table $table) {
			parent::__construct('id', $name, $table);
		}

		protected static function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';
			if (strripos($data['EXTRA'], 'auto_increment') !== false) $pieces['ai'] =  'AUTO_INCREMENT';

			return implode(' ', $pieces);
		}

		private function GetFormat(): string { return "`{$this->name}` int unsigned NOT NULL AUTO_INCREMENT"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}