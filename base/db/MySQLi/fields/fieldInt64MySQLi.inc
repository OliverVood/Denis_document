<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt64MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('int64', $name, $table);
		}

		private function GetFormat(): string { return "`{$this->name}` bigint NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}