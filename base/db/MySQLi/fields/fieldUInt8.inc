<?php

	namespace Base\DB\MySQLi;

	class FieldUInt8 extends Field {
		protected int $size = 3;

		public function __construct(string $name, Table $table, string $description) {
			parent::__construct('uint8', $name, $table, $description);

			$this->_type = ['tinyint unsigned', "tinyint({$this->size}) unsigned"];
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = '0';
			$this->_extra = [''];
		}

		private function GetFormat(): string { return "`{$this->name}` tinyint(3) unsigned NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}