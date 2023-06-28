<?php

	namespace Base\DB\MySQLi;

	class FieldBool extends Field {
		protected int $size = 1;

		public function __construct(string $name, Table $table) {
			parent::__construct('bool', $name, $table);

			$this->_type = ["tinyint({$this->size})"];
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = '0';
			$this->_extra = [''];
		}

		private function GetFormat(): string { return "`{$this->name}` tinyint(1) NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}