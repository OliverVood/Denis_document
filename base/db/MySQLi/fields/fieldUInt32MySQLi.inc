<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt32MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('uint32', $name, $table);
		}

		private function GetFormat(): string { return "`{$this->name}` int unsigned NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}