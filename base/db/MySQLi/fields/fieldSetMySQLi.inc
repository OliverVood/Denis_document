<?php

	namespace Base\DB;

	use Base\DB;

	class FieldSetMySQLi extends DB\FieldMySQLi {
		private array $set;

		public function __construct(string $name, array $set, TableMySQLi $table) {
			parent::__construct('set', $name, $table);

			$this->set = $set;
		}

		protected static function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';

			return implode(' ', $pieces);
		}

		private function GetFormat(): string { return "`{$this->name}` set('" . implode("','", $this->set) . "') NOT NULL"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}