<?php

	namespace Base\DB\MySQLi;

	class FieldTimestamp extends Field {
		private bool $update;

		public function __construct(string $name, bool $update, Table $table) {
			parent::__construct('timestamp', $name, $table);

			$this->update = $update;
		}

		protected static function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';
			$pieces['default'] = 'DEFAULT CURRENT_TIMESTAMP';
			if (strripos($data['EXTRA'], 'on update CURRENT_TIMESTAMP') !== false) $pieces['ai'] =  'ON UPDATE CURRENT_TIMESTAMP';

			return implode(' ', $pieces);
		}

		private function GetFormat(): string { return "`{$this->name}` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP" . ($this->update ? ' ON UPDATE CURRENT_TIMESTAMP' : ''); }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}