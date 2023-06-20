<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt24MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('int124', $name, $table);
		}

		private function GetFormat(): string { return "`{$this->name}` mediumint NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}