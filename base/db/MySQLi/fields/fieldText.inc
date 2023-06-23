<?php

	namespace Base\DB\MySQLi;

	class FieldText extends Field {
		public function __construct(string $name, Table $table) {
			parent::__construct('text', $name, $table);
		}

		protected static function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';

			return implode(' ', $pieces);
		}

		private function GetFormat(): string { return "`{$this->name}` text NOT NULL"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}