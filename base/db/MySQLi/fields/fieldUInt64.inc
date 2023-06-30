<?php

	namespace Base\DB\MySQLi;

	class FieldUInt64 extends Field {
		protected int $size = 20;

		public function __construct(string $name, Table $table, string $description) {
			parent::__construct('uint64', $name, $table, $description);

			$this->_type = ['bigint unsigned', "bigint({$this->size}) unsigned"];
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = '0';
			$this->_extra = [''];
		}

		private function GetFormat(): string { return "`{$this->name}` bigint unsigned NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}