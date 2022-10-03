<?php

	namespace Base\DB;

	use Base\DB;

	class FieldTimestampMySQLi extends DB\FieldMySQLi {
		private bool $update;

		public function __construct(string $name, bool $update, TableMySQLi $table) {
			parent::__construct('timestamp', $name, $table);

			$this->update = $update;
		}

		protected function CreationFormat(): string { return "`{$this->name}` timestamp NOT NULL" . ($this->update ? ' ON UPDATE CURRENT_TIMESTAMP' : ''); }

	}