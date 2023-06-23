<?php

	namespace Base\DB\MySQLi;

	class FieldInt64 extends Field {
		public function __construct(string $name, Table $table) {
			parent::__construct('int64', $name, $table);
		}

		private function GetFormat(): string { return "`{$this->name}` bigint NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}