<?php

	namespace Base\DB;

	use Base\DB;

	class FieldStringMySQLi extends DB\FieldMySQLi {
		private int $length;

		public function __construct(string $name, int $length, TableMySQLi $table) {
			parent::__construct('enum', $name, $table);

			$this->length = $length;
		}

		private function GetFormat(): string { return "`{$this->name}` varchar({$this->length}) NOT NULL DEFAULT ''"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}