<?php

	namespace Base\DB\MySQLi;

	class FieldUInt16 extends Field {
		protected int $size = 5;

		public function __construct(string $name, Table $table, string $description) {
			parent::__construct('uint16', $name, $table, $description);

			$this->_type = ['smallint unsigned', "smallint({$this->size}) unsigned"];
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = '0';
			$this->_extra = [''];
		}

		private function GetFormat(): string { return "`{$this->name}` smallint unsigned NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}