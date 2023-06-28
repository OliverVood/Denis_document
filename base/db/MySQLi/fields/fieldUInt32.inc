<?php

	namespace Base\DB\MySQLi;

	class FieldUInt32 extends Field {
		protected int $size = 10;

		public function __construct(string $name, Table $table) {
			parent::__construct('uint32', $name, $table);

			$this->_type = ['int unsigned', "int({$this->size}) unsigned"];
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = '0';
			$this->_extra = [''];
		}

		private function GetFormat(): string { return "`{$this->name}` int unsigned NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}