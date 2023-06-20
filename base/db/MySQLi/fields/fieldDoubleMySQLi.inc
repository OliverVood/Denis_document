<?php

	namespace Base\DB;

	use Base\DB;

	class FieldDoubleMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('double', $name, $table);
		}

		private function GetFormat(): string { return "`{$this->name}` double NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}