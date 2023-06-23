<?php

	namespace Base\DB\MySQLi;

	class FieldFloat extends Field {
		public function __construct(string $name, Table $table) {
			parent::__construct('float', $name, $table);
		}

		private function GetFormat(): string { return "`{$this->name}` float NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}