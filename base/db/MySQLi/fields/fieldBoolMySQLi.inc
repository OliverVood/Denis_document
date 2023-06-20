<?php

	namespace Base\DB;

	use Base\DB;

	class FieldBoolMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('bool', $name, $table);
		}

		private function GetFormat(): string { return "`{$this->name}` tinyint(1) NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}