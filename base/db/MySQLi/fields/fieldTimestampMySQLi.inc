<?php

	namespace Base\DB;

	use Base\DB;

	class FieldTimestampMySQLi extends DB\FieldMySQLi {
		private bool $update;

		public function __construct(string $name, bool $update, TableMySQLi $table) {
			parent::__construct('timestamp', $name, $table);

			$this->update = $update;
		}

		static protected function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';
			if (strripos($data['EXTRA'], 'on update CURRENT_TIMESTAMP') !== false) $pieces['ai'] =  'ON UPDATE CURRENT_TIMESTAMP';

			return implode(' ', $pieces);
		}

		protected function CreationFormat(): string { return "`{$this->name}` timestamp NOT NULL" . ($this->update ? ' ON UPDATE CURRENT_TIMESTAMP' : ''); }

	}