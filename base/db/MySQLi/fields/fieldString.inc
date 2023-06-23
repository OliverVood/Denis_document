<?php

	namespace Base\DB\MySQLi;

	class FieldString extends Field {
		private int $length;

		public function __construct(string $name, int $length, Table $table) {
			parent::__construct('enum', $name, $table);

			$this->length = $length;
		}

		private function GetFormat(): string { return "`{$this->name}` varchar({$this->length}) NOT NULL DEFAULT ''"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}