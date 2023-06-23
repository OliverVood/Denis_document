<?php

	namespace Base\DB\MySQLi;

	class FieldEnum extends Field {
		private array $enum;

		public function __construct(string $name, array $enum, Table $table) {
			parent::__construct('enum', $name, $table);

			$this->enum = $enum;
		}

		protected static function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';

			return implode(' ', $pieces);
		}

		private function GetFormat(): string { return "`{$this->name}` enum('" . implode("','", $this->enum) . "') NOT NULL"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}