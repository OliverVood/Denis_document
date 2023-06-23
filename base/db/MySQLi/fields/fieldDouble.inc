<?php

	namespace Base\DB\MySQLi;

	class FieldDouble extends Field {
		public function __construct(string $name, Table $table) {
			parent::__construct('double', $name, $table);
		}

		private function GetFormat(): string { return "`{$this->name}` double NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}