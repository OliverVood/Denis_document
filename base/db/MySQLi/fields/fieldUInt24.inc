<?php

	namespace Base\DB\MySQLi;

	class FieldUInt24 extends Field {
		public function __construct(string $name, Table $table) {
			parent::__construct('uint124', $name, $table);
		}

		private function GetFormat(): string { return "`{$this->name}` mediumint unsigned NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}